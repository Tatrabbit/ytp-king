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
#include <wx/wx.h>
#include <gst/gst.h>


void main_loop_run( gpointer ) 
{ 
	//CustomData *customData = (CustomData *)data;

	GMainLoop *loop = g_main_loop_new( NULL, FALSE );
	g_main_loop_run( loop );
}


// This function will be called by the pad-added signal
void pad_added_handler (GstElement *src, GstPad *new_pad, GstElement *queue)
{
  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  GstPad *compatiblePad = gst_element_get_compatible_pad( queue, new_pad, gst_pad_get_caps( new_pad ) );

	if ( compatiblePad )
	{
		if ( gst_pad_link( new_pad, compatiblePad ) == GST_PAD_LINK_OK )
			g_print("  Link succeeded." );
		else
			g_print( "Link to '%s' from '%s' Failed.\n", GST_PAD_NAME (compatiblePad), GST_ELEMENT_NAME (queue) );
	}
	else
		g_print( "Skipping incompatible pad.\n" );
}


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

	DECLARE_EVENT_TABLE()

	//CustomData m_data;
	GThread    *m_gstThread;
	GstElement *m_gstPipeline;
private:

	bool
		addSample( GstElement *sink );
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_Quit, MyFrame::OnQuit)
	EVT_MENU(ID_About, MyFrame::OnAbout)
END_EVENT_TABLE()


IMPLEMENT_APP(MyApp)


MyApp::MyApp( void )
{
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

bool
MyApp::OnInit( void )
{
	MyFrame *frame = new MyFrame( _("Hello World, Chuu!"), wxPoint( 50, 50 ), wxSize( 450, 340 ) );

	frame->Show( true );
	SetTopWindow( frame );

	return true;
}

bool
MyFrame::addSample( GstElement *sink )
{
	GstElement *composition, *videoSource, *audioSource;

	composition = gst_element_factory_make( "gnlcomposition", "composition" );
	videoSource = gst_element_factory_make( "gnlfilesource", "video-1" );
	audioSource = gst_element_factory_make( "gnlfilesource", "audio-1" );

	if ( !gst_bin_add( GST_BIN( composition ), videoSource ) )
		goto MyFrame_addSample_EXIT;

	if ( !gst_bin_add( GST_BIN( composition ), audioSource ) )
		goto MyFrame_addSample_EXIT;

	if ( !gst_bin_add( GST_BIN( m_gstPipeline ), composition ) )
		goto MyFrame_addSample_EXIT;

	g_object_set( videoSource, "uri", "file:///C:/zelda.ogv", NULL );
	g_object_set( videoSource, "start", 0 * GST_SECOND, NULL );
	g_object_set( videoSource, "duration", 3 * GST_SECOND, NULL );
	g_object_set( videoSource, "media-start", 10 * GST_SECOND, NULL );
	g_object_set( videoSource, "media-duration", 3 * GST_SECOND, NULL );
	g_object_set( videoSource, "caps", gst_caps_from_string( "video/x-raw-yuv;video/x-raw-rgb" ), NULL ); 

	g_object_set( audioSource, "uri", "file:///C:/zelda.ogv", NULL );
	g_object_set( audioSource, "start", 3 * GST_SECOND, NULL );
	g_object_set( audioSource, "duration", 3 * GST_SECOND, NULL );
	g_object_set( audioSource, "media-start", 15 * GST_SECOND, NULL );
	g_object_set( audioSource, "media-duration", 3 * GST_SECOND, NULL );
	g_object_set( audioSource, "caps", gst_caps_from_string( "video/x-raw-yuv;video/x-raw-rgb" ), NULL ); 

	g_signal_connect( composition, "pad-added", G_CALLBACK(pad_added_handler), sink );

	return true;


MyFrame_addSample_EXIT:
	gst_object_unref( composition );
	gst_object_unref( videoSource );
	gst_object_unref( audioSource );

	return false;
}

MyFrame::MyFrame( const wxString &title, const wxPoint &position, const wxSize &size ) :
	wxFrame( NULL, -1, title, position, size ),
	m_gstThread( NULL )
{
	wxMenu *menuFile = new wxMenu;

	menuFile->Append( ID_About, _("&About") );
	menuFile->AppendSeparator();
	menuFile->Append( ID_Quit, _("&Quit") );

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, _("&File") );

	SetMenuBar( menuBar );

	CreateStatusBar();
	SetStatusText( _("Welcome to wxPingas!") );

	// Initialize GStreamer
	gst_debug_set_default_threshold( GST_LEVEL_WARNING );
	gst_init (NULL, NULL);
 

	// Build the pipeline
	m_gstPipeline = gst_pipeline_new( "pipeline" );

	GstElement *queue = gst_element_factory_make( "queue", "queue" );
	GstElement *sink  = gst_element_factory_make( "autovideosink", "video-sink" );

	gst_bin_add_many( GST_BIN( m_gstPipeline ), queue, sink, NULL );

	addSample( queue );

	if ( !gst_element_link( queue, sink ) )
		g_printerr ("Queue/Sink could not be linked.\n");
   
	// Start playing
	gst_element_set_state( m_gstPipeline, GST_STATE_PLAYING );

	// Create the Gstreamer Main Loop Thread
	m_gstThread = g_thread_new( "gst-main_loop", (GThreadFunc)main_loop_run, NULL );

	if ( m_gstThread == NULL )
		GST_ERROR( "Couldn't create GStreamer loop thread.\n" );
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
	wxMessageBox( _("This is a wxWidgets Hello World sample"),
		          _("About Hello World"),
				  wxOK | wxICON_INFORMATION, this );
}