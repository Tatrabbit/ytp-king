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
#include <wx/frame.h>
#include "gst/gnl/PreviewUser.h"

#include <string>
#include <sstream>

#include <wx/menu.h>
#include <wx/textctrl.h>


	namespace ytpking
	{

namespace gst {
	class GstreamerThread;
	class Pipeline;
	
	namespace gnl {
		class AudioComposition;
		class VideoComposition;
	}
}


class MainWindow :
	public wxFrame,
	public gst::gnl::PreviewUser
{
public:

	MainWindow( void );
	~MainWindow( void );

private: // TODO macros for = delete when it becomes available.
	MainWindow( const MainWindow &c );

	MainWindow
		&operator=( const MainWindow &c );

public:

	wxWindow *m_moviePanel;
	wxSizer  *m_sourcesSizer;
	wxWindow *m_timelineWindow;
	wxSizer  *m_samplePropertiesSizer;


	//// BEGIN wx Events

	void
		OnQuit( wxCommandEvent &event );

	void
		OnAbout( wxCommandEvent &event );

	//// END wx Events

private:

	enum EventId
	{
		Quit = 1,
		About
	};

	static unsigned int m_nSamples;

	std::string m_filename;

	wxTextCtrl *m_textControl;

	gst::GstreamerThread       *m_gstThread;
	gst::Pipeline              *m_pipeline;

	bool
		addSample( int start, int duration );

	wxDECLARE_EVENT_TABLE();

	const wxPoint
		&getStartupPosition( wxPoint &defaultPosition ) const;

	const wxSize
		&getStartupSize( wxSize &defaultSize ) const;

};


	}