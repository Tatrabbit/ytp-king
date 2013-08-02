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
#include <string>
#include <sstream>

#include <wx/wx.h>


typedef struct  _GstElement   GstElement;
typedef struct  _GstMessage   GstMessage;
typedef struct  _GThread      GThread;
typedef struct  _GstPad       GstPad;
typedef struct  _GstBus       GstBus;

typedef void    *gpointer;


	namespace ytpking
	{


class MainWindow :
	public wxFrame
{
public:

	MainWindow( void );

	wxPanel *m_moviePanel;

	wxSizer *m_sourcesSizer;


	//// BEGIN wx Events

	void
		OnQuit( wxCommandEvent &event );

	void
		OnAbout( wxCommandEvent &event );

	//// END wx Events


	//// BEGIN GStreamer Events

	static void
		onPadAdded (GstElement *src, GstPad *new_pad, GstElement *sink);

	static void
		onSync( GstBus *bus, GstMessage *message, gpointer data );

	//// END GStreamer Events

private:

	enum EventId
	{
		Quit = 1,
		About
	};

	GThread    *m_gstThread;
	GstElement *m_gstPipeline;

	GstElement *m_audioComposition;
	GstElement *m_videoComposition;

	static unsigned int m_nSamples;

	std::string m_filename;

	wxTextCtrl *m_textControl;

	bool
		addSample( int start, int mediaStart, int duration );

	wxDECLARE_EVENT_TABLE();

	const wxPoint
		&getStartupPosition( wxPoint &defaultPosition ) const;

	const wxSize
		&getStartupSize( wxSize &defaultSize ) const;

};


	}