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

#include "gst/gnl/Composition.h"
#include "gst/gnl/FileSource.h"


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
		//wxSafeShowMessage( _("Derp"), dataObject->GetData() );

		FileSource *audioSource, *videoSource;
		audioSource = m_audioPreviewComposition->addSource();
		videoSource = m_videoPreviewComposition->addSource();

		//if ( (audioSource = dataObject->GetAudioSource()) )
		{		
			audioSource->setStart( 0 );

			audioSource->setDuration( 5 );
			audioSource->setFilename( "file:///C:/zelda.mp4" );

			m_audioPreviewComposition->update();
		}

		//if ( (videoSource = dataObject->GetAudioSource()) )
		{
			videoSource->setStart( 0 );

			videoSource->setDuration( 5 );
			videoSource->setFilename( "file:///C:/zelda.mp4" );

			m_videoPreviewComposition->update();
		}

		SampleComponent *component = new SampleComponent( m_parent, dataObject->GetSampleName(), NULL, NULL );

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
	//wxWindow *container = new wxWindow( parent, wxID_ANY, wxDefaultPosition, wxSize( 200, 100 ) );
	//container->SetOwnBackgroundColour( wxColour( "red" ) );

	//sizer->Add( container, 1, wxEXPAND|wxALL );
}


	}