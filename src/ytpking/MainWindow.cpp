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
#include "ytpking/MainWindow.h"

#include <gst/gst.h>

#include "gst/GstreamerThread.h"
#include "gst/Pipeline.h"
#include "gst/gnl/AudioComposition.h"
#include "gst/gnl/FileSource.h"

#include "lnb/LibrarySizer.h"
#include "TimelineSizer.h"
#include "SamplePropertiesSizer.h"


	namespace ytpking
	{


unsigned int
	MainWindow::m_nSamples( 0u );


MainWindow::MainWindow( void ) :
	wxFrame( NULL, -1, "YTP King", getStartupPosition( wxPoint(50, 50) ), getStartupSize( wxSize( 800, 600 ) ) ),
	m_gstThread( new gst::GstreamerThread ),
	m_previewAudioComposition( new gst::gnl::AudioComposition )
{
	// Remove the ugly grey tinge on Windows
	SetBackgroundColour( wxNullColour );

	m_sourcesSizer          = new lnb::LibrarySizer( this );
	m_timelineSizer         = new TimelineSizer( this );
	m_samplePropertiesSizer = new SamplePropertiesSizer( this );

	wxMenu *menuFile = new wxMenu;

	menuFile->Append( EventId::About, _("&Play") );
	menuFile->AppendSeparator();
	menuFile->Append( EventId::Quit, _("&Quit") );

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, _("&File") );

	SetMenuBar( menuBar );

	wxSizer *mainSizer = new wxBoxSizer( wxHORIZONTAL );

	mainSizer->Add( m_sourcesSizer, 1, wxEXPAND );

	wxSizer *sampleAndMovieSizer = new wxBoxSizer( wxHORIZONTAL );

	wxSizer *movieSizer = new wxBoxSizer( wxVERTICAL );

	wxSizer *entrySizer = new wxBoxSizer( wxHORIZONTAL );

	m_textControl = new wxTextCtrl( this, -1 );

	entrySizer->Add( m_textControl, 1, wxALL|wxEXPAND );

	movieSizer->Add( entrySizer, 0, wxALL|wxEXPAND );

	m_moviePanel = new wxWindow( this, wxID_ANY );
	m_moviePanel->SetOwnBackgroundColour( wxColour( "black" ) );

	movieSizer->Add( m_moviePanel, 1, wxALL|wxEXPAND );
	movieSizer->Add( m_timelineSizer, 0, wxALL|wxEXPAND );

	sampleAndMovieSizer->Add( m_samplePropertiesSizer );
	sampleAndMovieSizer->Add( movieSizer, 1, wxALL|wxEXPAND );

	mainSizer->Add( sampleAndMovieSizer, 3, wxEXPAND );

	this->SetSizer( mainSizer );

	CreateStatusBar();
	SetStatusText( "Roll your cursor over something and look here for help." );

	m_pipeline                = new gst::Pipeline( m_moviePanel );

	m_previewAudioComposition->addTo( *m_pipeline );

	//GstElement *audioQueue = gst_element_factory_make( "queue", "queue_a" );
	//GstElement *videoQueue = gst_element_factory_make( "queue", "queue_v" );

	//m_audioComposition = gst_element_factory_make( "gnlcomposition", "sample_comp_a0" );
	//m_videoComposition = gst_element_factory_make( "gnlcomposition", "sample_comp_v0" );

	//g_object_set( m_audioComposition, "caps", gst_caps_from_string( "audio/x-raw-int;audio/x-raw-float" ), NULL ); 
	//g_object_set( m_videoComposition, "caps", gst_caps_from_string( "video/x-raw-yuv;video/x-raw-rgb" ), NULL ); 

	//g_signal_connect( m_audioComposition, "pad-added", G_CALLBACK(onPadAdded), audioQueue );
	//g_signal_connect( m_videoComposition, "pad-added", G_CALLBACK(onPadAdded), videoQueue );

	//GstElement *audioSink  = gst_element_factory_make( "autoaudiosink", "audio-sink" );
	//GstElement *videoSink  = gst_element_factory_make( "autovideosink", "video-sink" );

	//m_pipeline->add( m_audioComposition );
	//m_pipeline->add( m_videoComposition );
	//m_pipeline->add( audioQueue );
	//m_pipeline->add( videoQueue );
	//m_pipeline->add( videoSink );
	//m_pipeline->add( audioSink );


	//if ( !gst_element_link( audioQueue, audioSink ) )
	//	g_printerr ("Audio Queue/Sink could not be linked.\n");
	//
	//if ( !gst_element_link( videoQueue, videoSink ) )
	//	g_printerr ("Video Queue/Sink could not be linked.\n");
}


MainWindow::~MainWindow( void )
{
	delete m_previewAudioComposition;
	delete m_pipeline;
	delete m_gstThread;
}


bool
MainWindow::addSample( int start, int mediaStart, int duration )
{
	gst::gnl::FileSource *audio = m_previewAudioComposition->addSource();
	audio->setDuration( 10 );
	audio->setFilename( "file:///C:/zelda.mp4" );
	m_previewAudioComposition->update();

	//GstElement *videoSource, *audioSource;

	//// Get the names of the src elements
	//std::stringstream nameStream( "sample_a" );
	//nameStream << m_nSamples;
	//std::string srcName = nameStream.str();
	//videoSource = gst_element_factory_make( "gnlfilesource", srcName.c_str() );
	//
	//nameStream.clear();
	//nameStream << "sample_comp" << m_nSamples;
	//srcName = nameStream.str();
	//audioSource = gst_element_factory_make( "gnlfilesource", srcName.c_str() );
	//
	// Add the src elements to the compositions
	//if ( !gst_bin_add( GST_BIN( m_videoComposition ), videoSource ) )
	//	goto addSample_RETURN_FALSE;
	//
	//if ( !gst_bin_add( GST_BIN( m_audioComposition ), audioSource ) )
	//	goto addSample_RETURN_FALSE;

	// set the properties
	//g_object_set( videoSource, "uri", m_filename.c_str(), NULL );
	//g_object_set( videoSource, "start", start * GST_SECOND, NULL );
	//g_object_set( videoSource, "duration", duration * GST_SECOND, NULL );
	//g_object_set( videoSource, "media-start", mediaStart * GST_SECOND, NULL );
	//g_object_set( videoSource, "media-duration", duration * GST_SECOND, NULL );
	//
	//g_object_set( audioSource, "uri", m_filename.c_str(), NULL );
	//g_object_set( audioSource, "start", start * GST_SECOND, NULL );
	//g_object_set( audioSource, "duration", duration * GST_SECOND, NULL );
	//g_object_set( audioSource, "media-start", mediaStart * GST_SECOND, NULL );
	//g_object_set( audioSource, "media-duration", duration * GST_SECOND, NULL );

	// inc the static id
	//m_nSamples++;

	//return true;

	// Free things on error
//addSample_RETURN_FALSE:
	// And goto helps keep the indentation flat. Don't dismiss it blindly, it CAN be useful
	// sometimes.
	//gst_object_unref( videoSource );
	//gst_object_unref( audioSource );

	//return false;
	return true;
}


void
MainWindow::OnQuit( wxCommandEvent &WXUNUSED(event) )
{
	m_pipeline->stop();
	Close( true );
}


void
MainWindow::OnAbout( wxCommandEvent &WXUNUSED(event) )
{
	/*wxMessageBox( _("This is a wxWidgets Hello World sample"),
		          _("About Hello World"),
				  wxOK | wxICON_INFORMATION, this );*/

	// Start playing
	m_filename = m_textControl->GetValue();
	addSample( 0, 2, 4 );
	//addSample( 4, 10, 4 );

	m_pipeline->play();
}


const wxPoint
&MainWindow::getStartupPosition( wxPoint &defaultPosition ) const
{
	// TODO save the window position, check monitor size.
	return defaultPosition;
}


const wxSize
&MainWindow::getStartupSize( wxSize &defaultSize ) const
{
	// TODO save the window size, check monitor size.
	return defaultSize;
}


BEGIN_EVENT_TABLE( MainWindow, wxFrame )

	EVT_MENU( EventId::Quit,  MainWindow::OnQuit  )
	EVT_MENU( EventId::About, MainWindow::OnAbout )

END_EVENT_TABLE()


	}