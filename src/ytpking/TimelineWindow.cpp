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
#include "smp/Tape.h"
#include "smp/Sample.h"

#include "gst/gnl/PreviewTapes.h"


	namespace ytpking
	{


TimelineWindow::
TimelineDropTarget::TimelineDropTarget( TimelineWindow *parent ) :
	wxDropTarget( new SampleDataObject ),
	m_parent( parent )
{
}


wxDragResult
TimelineWindow::
TimelineDropTarget::OnData( wxCoord, wxCoord, wxDragResult defResult )
{
	if ( smp::tapeManager.getSelectedTape() == NULL )
		return wxDragNone;

	using gst::gnl::FileSource;

	if ( GetDataObject() )
	{
		SampleDataObject *dataObject = (SampleDataObject *)GetDataObject();
		smp::Tape::SampleInstance *sampleInstance;
		sampleInstance = smp::tapeManager.getSelectedTape()->appendSample( *dataObject->m_sample );

		m_parent->appendComponent( *smp::tapeManager.getSelectedTape(), *sampleInstance );
		m_parent->GetSizer()->Layout();
		/*
		SampleComponent *component = new SampleComponent( m_parent, dataObject->GetSampleName(), smp::tapeManager.getSelectedTape(), sampleInstance );

		m_parent->m_components.push_back( component );

		wxSizer *sizer = m_parent->GetSizer();
		sizer->Add( component, 0 );
		sizer->Layout();
		*/

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
	SetDropTarget( new TimelineDropTarget( this ) );
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
	{
		clearAllComponents();
		useTape( *selectedTape );
		sizer->Show( this );
	}
	else
		sizer->Hide( this );

	sizer->Layout();
}


void
TimelineWindow::onDeleteTape( smp::Tape &deletedTape )
{
}


void
TimelineWindow::clearAllComponents( void )
{
	for ( ComponentList::const_iterator it = m_components.begin(); it != m_components.end(); ++it )
			(*it)->Destroy();

	m_components.clear();
}


void
TimelineWindow::useTape( smp::Tape &tape )
{
	const smp::Tape::InstanceSet *instances = &tape.getInstances();

	for ( smp::Tape::InstanceSet::const_iterator it = instances->begin(); it != instances->end(); ++it )
		appendComponent( tape, **it );

	GetSizer()->Layout();
}


void
TimelineWindow::appendComponent( smp::Tape &tape, const smp::Tape::SampleInstance &sampleInstance )
{
	SampleComponent *component = new SampleComponent( this, "sample name", &tape, &sampleInstance );

	m_components.push_back( component );

	GetSizer()->Add( component, 0 );
}


BEGIN_EVENT_TABLE( TimelineWindow, wxWindow )

	EVT_UPDATE_UI( wxID_ANY, onUpdate )

END_EVENT_TABLE()

	}