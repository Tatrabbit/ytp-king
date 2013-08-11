/*  YTP King - Easy to use sentence mixer
 *  Copyright (C) 2013  Alex "rainChu" Haddad et al.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ytpking/TimelineWindow.h"

#include <wx/wx.h>

#include "SampleDataObject.h"
#include "SampleComponent.h"

#include "smp/TapeManager.h"
#include "smp/Sample.h"

#include "gst/gnl/PreviewTapes.h"


	namespace ytpking
	{


TimelineWindow::
TimelineDropTarget::TimelineDropTarget( wxWindow *parent, wxSizer *sizer ) :
	wxDropTarget( new SampleDataObject ),
	m_parent( parent ),
	m_sizer( sizer )
{
}


wxDragResult
TimelineWindow::
TimelineDropTarget::OnData( wxCoord, wxCoord, wxDragResult defResult )
{
	using gst::gnl::FileSource;

	if ( GetData() )
	{
		SampleDataObject *dataObject = (SampleDataObject *)GetDataObject();

		FileSource *audioSource, *videoSource;
		dataObject->m_sample->addToPreviewTapes( audioSource, videoSource );

		SampleComponent *component = new SampleComponent( m_parent, dataObject->GetSampleName(), audioSource, videoSource );

		m_sizer->Add( component, 0 );
		m_sizer->Layout();

		return defResult;
	}
	else
		return wxDragNone;
}



TimelineWindow::TimelineWindow( wxWindow *parent ) :
	wxWindow( parent, wxID_ANY, wxDefaultPosition, wxSize( 200, 150 ) ),
	smp::TapeUser( smp::tapeManager )
{
	wxSizer *sizer = new wxStaticBoxSizer( wxHORIZONTAL, this, "Tape Mixer" );
	SetDropTarget( new TimelineDropTarget( this, sizer ) );
	SetSizer( sizer );
}


void
TimelineWindow::onUpdate( wxUpdateUIEvent& event )
{
	Layout();
}


void
TimelineWindow::onAddTape( smp::Tape &addedTape )
{
}


void
TimelineWindow::onSelectTape( smp::Tape *selectedTape )
{
	wxSizer *sizer = GetContainingSizer();

	assert( sizer != NULL );

	if ( selectedTape != NULL )
		sizer->Show( this );
	else
		sizer->Hide( this );

	sizer->Layout();
}


void
TimelineWindow::onDeleteTape( smp::Tape &deletedTape )
{
}


BEGIN_EVENT_TABLE( TimelineWindow, wxWindow )

	EVT_UPDATE_UI( wxID_ANY, onUpdate )

END_EVENT_TABLE()

	}