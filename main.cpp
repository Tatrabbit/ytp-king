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

enum
{
	ID_Quit = 1,
	ID_About
};


class MyApp :
	public wxApp
{
	virtual bool OnInit( void )
		override;
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

};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_Quit, MyFrame::OnQuit)
	EVT_MENU(ID_About, MyFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)


bool
MyApp::OnInit( void )
{
	MyFrame *frame = new MyFrame( _("Hello World, Chuu!"), wxPoint( 50, 50 ), wxSize( 450, 340 ) );

	// Take Messages
	// Wait until error or EOS
	//bus = gst_element_get_bus (pipeline);
	//msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS) );
   
	 // Free resources
	/*if (msg != NULL)
		gst_message_unref (msg);*/
	//

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

	GstElement *pipeline;
	//GstBus *bus;
	//GstMessage *msg;
   
	///
	// Initialize GStreamer
	gst_init (NULL, NULL);
   
	// Build the pipeline
	pipeline = gst_parse_launch ("playbin2 uri=http://docs.gstreamer.com/media/sintel_trailer-480p.webm", NULL);
   
	// Start playing
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	///
}

void
MyFrame::OnQuit( wxCommandEvent &WXUNUSED(event) )
{
	/// Cleanup

	/*gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);*/
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