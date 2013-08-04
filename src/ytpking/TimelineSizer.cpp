/*  YTP King - Easy to use sentence mixer
 *  Copyright (C) 2013  Alex "rainChu" Haddad
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
#include "ytpking/TimelineSizer.h"

#include <wx/wx.h>

#include "SampleDataObject.h"
#include "SampleComponent.h"

#include "Sample.h"


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

		const FileSource *audioSource, *videoSource;
		audioSource = dataObject->m_sample->addToComposition( m_audioPreviewComposition );
		videoSource = dataObject->m_sample->addToComposition( m_videoPreviewComposition );

		SampleComponent *component = new SampleComponent( m_parent, dataObject->GetSampleName(), audioSource, videoSource );

		m_sizer->Add( component, 0 );
		m_sizer->Layout();

		return defResult;
	}
	else
		return wxDragNone;
}



TimelineWindow::TimelineWindow( wxWindow *parent ) :
	wxWindow( parent, wxID_ANY, wxDefaultPosition, wxSize( 200, 150 ) )
{
	wxSizer *sizer = new wxStaticBoxSizer( wxHORIZONTAL, this, "Tape Mixer" );
	SetDropTarget( new TimelineDropTarget( this, sizer ) );
	SetSizer( sizer );
}


	}