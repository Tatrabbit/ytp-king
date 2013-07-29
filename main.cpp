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

// Structure to contain all our information, so we can pass it to callbacks
typedef struct _CustomData {
  GstElement *pipeline;
  GstElement *composition;
  GstElement *sink;
  GMainLoop  *loop;

} CustomData;


void main_loop_run( gpointer data ) 
{ 
	if ( !data )
		return;

	CustomData *customData = (CustomData *)data;

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

	CustomData m_data;
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


MyFrame::MyFrame( const wxString &title, const wxPoint &position, const wxSize &size ) :
	wxFrame( NULL, -1, title, position, size )
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
 
	//// Build the pipeline
	m_data.pipeline = gst_pipeline_new( "pipeline" );

	GstElement *source1, *source2;

	m_data.composition = gst_element_factory_make( "gnlcomposition", "composition" );
	source1 = gst_element_factory_make( "gnlfilesource", "video-1" );
	source2 = gst_element_factory_make( "gnlfilesource", "video-2" );

	GstElement *queue = gst_element_factory_make( "queue", "queue" );

	m_data.sink = gst_element_factory_make( "autovideosink", "video-sink" );


	if ( !gst_bin_add( GST_BIN(m_data.composition), source1 ) )
		g_printerr( "Couldn't add source 1 to composition\n" );

	if ( !gst_bin_add( GST_BIN(m_data.composition), source2 ) )
		g_printerr( "Couldn't add source 2 to composition\n" );

	if ( !gst_bin_add( GST_BIN(m_data.pipeline), m_data.composition ) )
		g_printerr( "Couldn't add composition\n" );

	if ( !gst_bin_add( GST_BIN(m_data.pipeline), queue ) )
		g_printerr( "Couldn't add queue\n" );

	if ( !gst_bin_add( GST_BIN(m_data.pipeline), m_data.sink ) )
		g_printerr( "Couldn't add sink\n" );


	g_object_set( source1, "uri", "file:///C:/zelda.ogv", NULL );
	g_object_set( source1, "start", 0 * GST_SECOND, NULL );
	g_object_set( source1, "duration", 3 * GST_SECOND, NULL );
	g_object_set( source1, "media-start", 10 * GST_SECOND, NULL );
	g_object_set( source1, "media-duration", 3 * GST_SECOND, NULL );

	g_object_set( source2, "uri", "file:///C:/zelda.ogv", NULL );
	g_object_set( source2, "start", 3 * GST_SECOND, NULL );
	g_object_set( source2, "duration", 3 * GST_SECOND, NULL );
	g_object_set( source2, "media-start", 15 * GST_SECOND, NULL );
	g_object_set( source2, "media-duration", 3 * GST_SECOND, NULL );

	g_object_set (source1, "caps", gst_caps_from_string ("video/x-raw-yuv;video/x-raw-rgb"), NULL); 
	g_object_set (source2, "caps", gst_caps_from_string ("video/x-raw-yuv;video/x-raw-rgb"), NULL); 

	if ( !gst_element_link( queue, m_data.sink ) )
		g_printerr ("Queue/Sink could not be linked.\n");

	g_signal_connect( m_data.composition, "pad-added", G_CALLBACK(pad_added_handler), queue );
   
	// Start playing
	gst_element_set_state (m_data.pipeline, GST_STATE_PLAYING);
	///

	GstBus *bus = gst_element_get_bus (m_data.pipeline);
	 
	GThread *thread = g_thread_new( "myThread", (GThreadFunc)main_loop_run, &m_data );

	if ( thread == NULL )
		g_printerr( "couldnt' create thread\n" );

}


void
MyFrame::OnQuit( wxCommandEvent &WXUNUSED(event) )
{
	/// Cleanup

	//gst_object_unref (bus);
	//gst_element_set_state (pipeline, GST_STATE_NULL);
	//gst_object_unref (pipeline);
	///
	Close( true );
}


void
MyFrame::OnAbout( wxCommandEvent &WXUNUSED(event) )
{
	wxMessageBox( _("This is a wxWidgets Hello World sample"),
		          _("About Hello World"),
				  wxOK | wxICON_INFORMATION, this );
}