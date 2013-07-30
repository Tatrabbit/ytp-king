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
#include <cstdlib>

#include <string>
#include <sstream>

#include <wx/wx.h>
#include <gst/gst.h>

#include <gst/interfaces/xoverlay.h>

#ifdef _MSC_VER
#	include <direct.h>
#	include <Shlwapi.h>

#	define getcwd _getcwd
#	define putenv _putenv
#else
#	include <unistd.h>
#	define getcwd getcwd
#endif


void main_loop_run( gpointer ) 
{
	SetEnvironmentVariable( L"GST_PLUGIN_SYSTEM_PATH", L"C:\\gstreamer-sdk\\0.10\\x86\\lib\\gstreamer-0.10" );
	gst_init( NULL, NULL );

	GMainLoop *loop = g_main_loop_new( NULL, FALSE );
	g_main_loop_run( loop );
}


// This function will be called by the pad-added signal
void onPadAdded (GstElement *src, GstPad *new_pad, GstElement *sink)
{
  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  GstPad *compatiblePad = gst_element_get_compatible_pad( sink, new_pad, gst_pad_get_caps( new_pad ) );

	if ( compatiblePad )
	{
		if ( gst_pad_link( new_pad, compatiblePad ) == GST_PAD_LINK_OK )
			g_print("  Link succeeded.\n" );
		else
			g_print( "Link to '%s' from '%s' Failed.\n", GST_PAD_NAME (compatiblePad), GST_ELEMENT_NAME (sink) );
	}
	else
		g_print( "Skipping incompatible pad.\n" );
}

void onSync( GstBus *bus, GstMessage *message, gpointer data );


enum
{
	ID_Quit = 1,
	ID_About
};


class MyApp :
	public wxApp
{
public:
	MyApp( void );

	char m_currentPath[FILENAME_MAX];

private:
	virtual bool OnInit( void )
		override;

	wxLog *m_logger;
};


class MyFrame :
	public wxFrame
{
public:

	MyFrame( const wxString &title, const wxPoint &pos, const wxSize &size );

	void
		OnQuit( wxCommandEvent &event );

	void
		OnAbout( wxCommandEvent &event );

	wxPanel *m_moviePanel;

	DECLARE_EVENT_TABLE()

private:

	GThread    *m_gstThread;
	GstElement *m_gstPipeline;

	GstElement *m_audioComposition;
	GstElement *m_videoComposition;

	static unsigned int m_nSamples;

	std::string m_filename;

	wxTextCtrl *m_textControl;

	bool
		addSample( int start, int mediaStart, int duration );
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_Quit, MyFrame::OnQuit)
	EVT_MENU(ID_About, MyFrame::OnAbout)
END_EVENT_TABLE()


IMPLEMENT_APP(MyApp)


MyApp::MyApp( void )
{
	if ( !getcwd( m_currentPath, sizeof( m_currentPath ) ) )
		m_currentPath[0] = '\0';

	FILE *result = freopen( "ErrorLog.txt", "w", stderr );
	freopen( "Log.txt", "w", stdout );

	if ( result )
	{
		m_logger = new wxLogStderr( stderr ); // TODO delete!
		wxLog::SetActiveTarget( m_logger );

		wxLogMessage( "Program Started." );
	}
	else
		wxSafeShowMessage( "Error", "Could not open the wxWidgets log file." );
}

//file:///C:/zelda.mp4
bool
MyApp::OnInit( void )
{
	// Initialize GStreamer
	gst_debug_set_default_threshold( GST_LEVEL_WARNING );

	MyFrame *frame = new MyFrame( _("Hello World, Chuu!"), wxPoint( 50, 50 ), wxSize( 450, 340 ) );

		//cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

		
		// set the plugins path
		//GstRegistry *registry;
		//registry = gst_registry_get_default();

		//std::string pluginPath( "C:\\gstreamer-sdk\\0.10\\x86\\lib\\gstreamer-0.10" );
		//pluginPath += cCurrentPath;

		//pluginPath += cCurrentPath;

		//pluginPath += "\\plugins";

		//wxSafeShowMessage( "derp", pluginPath.c_str() );

		//std::wstring path( pluginPath.begin(), pluginPath.end() );

		//putenv( pluginPath.c_str() );
		//SetEnvironmentVariable( L"GST_PLUGIN_SYSTEM_PATH", path.c_str() );

		//gst_init( NULL, NULL );

		//gst_default_registry_add_path( pluginPath.c_str() );
		//gst_update_registry();

		//int gstArgc = 2;

		// The const-ness is derpy
		//const char *gstArgvConst[2];

		//char **gstArgv = const_cast<char **>(gstArgvConst);

		//gstArgvConst[0] = cCurrentPath;
		//gstArgvConst[1] = "--gst-plugin-path";
		//gstArgvConst[1] = pluginPath.c_str();

		//gst_init( &gstArgc, &gstArgv );
		

		//gst_registry_add_path( registry, pluginPath.c_str() );
		//if ( gst_registry_scan_path( registry, pluginPath.c_str() ) )
			//wxLogMessage( "plugins added" );

	frame->Show( true );
	SetTopWindow( frame );

	return true;
}


bool
MyFrame::addSample( int start, int mediaStart, int duration )
{
	GstElement *videoSource, *audioSource;

	// Get the names of the src elements
	std::stringstream nameStream( "sample_a" );
	nameStream << m_nSamples;
	std::string srcName = nameStream.str();
	videoSource = gst_element_factory_make( "gnlfilesource", srcName.c_str() );

	nameStream.clear();
	nameStream << "sample_comp" << m_nSamples;
	srcName = nameStream.str();
	audioSource = gst_element_factory_make( "gnlfilesource", srcName.c_str() );

	// Add the src elements to the compositions
	if ( !gst_bin_add( GST_BIN( m_videoComposition ), videoSource ) )
		goto MyFrame_addSample_EXIT;

	if ( !gst_bin_add( GST_BIN( m_audioComposition ), audioSource ) )
		goto MyFrame_addSample_EXIT;

	// set the properties
	g_object_set( videoSource, "uri", m_filename.c_str(), NULL );
	g_object_set( videoSource, "start", start * GST_SECOND, NULL );
	g_object_set( videoSource, "duration", duration * GST_SECOND, NULL );
	g_object_set( videoSource, "media-start", mediaStart * GST_SECOND, NULL );
	g_object_set( videoSource, "media-duration", duration * GST_SECOND, NULL );

	g_object_set( audioSource, "uri", m_filename.c_str(), NULL );
	g_object_set( audioSource, "start", start * GST_SECOND, NULL );
	g_object_set( audioSource, "duration", duration * GST_SECOND, NULL );
	g_object_set( audioSource, "media-start", mediaStart * GST_SECOND, NULL );
	g_object_set( audioSource, "media-duration", duration * GST_SECOND, NULL );

	// inc the static id
	m_nSamples++;

	return true;

	// Free things on error
MyFrame_addSample_EXIT:
	gst_object_unref( videoSource );
	gst_object_unref( audioSource );

	return false;
}


unsigned int MyFrame::m_nSamples( 0u );


MyFrame::MyFrame( const wxString &title, const wxPoint &position, const wxSize &size ) :
	wxFrame( NULL, -1, title, position, size ),
	m_gstThread( NULL )
	//,m_filename( "file:///C:/zelda.mp4" )
{
	// Create the Gstreamer Main Loop Thread
	m_gstThread = g_thread_new( "gst-main_loop", (GThreadFunc)main_loop_run, NULL );

	if ( m_gstThread == NULL )
		GST_ERROR( "Couldn't create GStreamer loop thread.\n" );

	wxMenu *menuFile = new wxMenu;

	menuFile->Append( ID_About, _("&Play") );
	menuFile->AppendSeparator();
	menuFile->Append( ID_Quit, _("&Quit") );

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, _("&File") );

	SetMenuBar( menuBar );

	wxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );

	wxSizer *entrySizer = new wxBoxSizer( wxHORIZONTAL );

	m_textControl = new wxTextCtrl( this, -1 );
	//wxButton *playButton = new wxButton( this, -1, "Play" );

	entrySizer->Add( m_textControl, 1, wxALL|wxEXPAND );
	//entrySizer->Add( playButton, 0, wxALL|wxEXPAND );

	mainSizer->Add( entrySizer, 0, wxALL|wxEXPAND );

	m_moviePanel = new wxPanel( this );
	m_moviePanel->SetupColours();
	m_moviePanel->SetOwnBackgroundColour( wxColour( "black" ) );
	m_moviePanel->SetWindowStyle( wxALL | wxEXPAND );
	m_moviePanel->SetPosition( wxPoint( 0, 0 ) );
	m_moviePanel->SetSize( 200, 200 );

	mainSizer->Add( m_moviePanel, 1, wxALL|wxEXPAND, 0 );

	this->SetSizer( mainSizer );

	CreateStatusBar();
	SetStatusText( _("Welcome to wxPingas!") );

	// Build the pipeline
	m_gstPipeline = gst_pipeline_new( "pipeline" );

	GstElement *audioQueue = gst_element_factory_make( "queue", "queue_a" );
	GstElement *videoQueue = gst_element_factory_make( "queue", "queue_v" );

	m_audioComposition = gst_element_factory_make( "gnlcomposition", "sample_comp_a0" );
	m_videoComposition = gst_element_factory_make( "gnlcomposition", "sample_comp_v0" );

	g_object_set( m_audioComposition, "caps", gst_caps_from_string( "audio/x-raw-int;audio/x-raw-float" ), NULL ); 
	g_object_set( m_videoComposition, "caps", gst_caps_from_string( "video/x-raw-yuv;video/x-raw-rgb" ), NULL ); 

	g_signal_connect( m_audioComposition, "pad-added", G_CALLBACK(onPadAdded), audioQueue );
	g_signal_connect( m_videoComposition, "pad-added", G_CALLBACK(onPadAdded), videoQueue );

	GstElement *audioSink  = gst_element_factory_make( "autoaudiosink", "audio-sink" );
	GstElement *videoSink  = gst_element_factory_make( "autovideosink", "video-sink" );

	gst_bin_add_many( GST_BIN( m_gstPipeline ), m_audioComposition, m_videoComposition, audioQueue, videoQueue, videoSink, audioSink, NULL );


	if ( !gst_element_link( audioQueue, audioSink ) )
		g_printerr ("Audio Queue/Sink could not be linked.\n");

	if ( !gst_element_link( videoQueue, videoSink ) )
		g_printerr ("Video Queue/Sink could not be linked.\n");

	// connect to the x-window callback
	GstBus *bus = gst_element_get_bus( m_gstPipeline );
	gst_bus_enable_sync_message_emission( bus );
	gst_bus_add_signal_watch( bus );

	g_signal_connect( bus, "sync-message::element", (GCallback)onSync, this );

	// Start playing
	//gst_element_set_state( m_gstPipeline, GST_STATE_PLAYING );

	
}


void
MyFrame::OnQuit( wxCommandEvent &WXUNUSED(event) )
{
	gst_element_set_state( m_gstPipeline, GST_STATE_NULL );
	gst_object_unref( m_gstPipeline );

	if ( m_gstThread != NULL )
		g_thread_join( m_gstThread );

	Close( true );
}


void
MyFrame::OnAbout( wxCommandEvent &WXUNUSED(event) )
{
	/*wxMessageBox( _("This is a wxWidgets Hello World sample"),
		          _("About Hello World"),
				  wxOK | wxICON_INFORMATION, this );*/

	// Start playing
	m_filename = m_textControl->GetValue();
	gst_element_set_state( m_gstPipeline, GST_STATE_PLAYING );

	addSample( 0, 2, 4 );
	addSample( 4, 10, 4 );
}

void onSync( GstBus *bus, GstMessage *message, gpointer data )
{
	const GstStructure *structure = gst_message_get_structure( message );
	const char *structureName = gst_structure_get_name( structure );

	g_print( "Called '%s'\n", structureName );
	
	MyFrame *frame = (MyFrame *)data;

	if ( strcmp( structureName, "prepare-xwindow-id" ) == 0 )
	{
		GstObject *imagesink = GST_MESSAGE_SRC( message );
		g_object_set( imagesink, "force-aspect-ratio", true, NULL );
		gst_x_overlay_set_xwindow_id( GST_X_OVERLAY( imagesink ), (gulong)frame->m_moviePanel->GetHWND() );
	}
}