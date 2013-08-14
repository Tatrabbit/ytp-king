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
#ifndef __YTPKING_MainWindow_h
#define __YTPKING_MainWindow_h

#include <wx/frame.h>

#include <string>
#include <sstream>

#include <wx/textctrl.h>


class wxTreeEvent;


	namespace ytpking
	{


class SamplePropertiesWindow;

namespace lnb {
	class LibrarySizer;
}

namespace gst {
	class GstreamerThread;
	class Pipeline;
	
	namespace gnl {
		class AudioComposition;
		class VideoComposition;
	}
}


class MainWindow :
	public wxFrame
{
public:

	MainWindow( void );
	~MainWindow( void );

private: // TODO macros for = delete when it becomes available.
	MainWindow( const MainWindow &c );

	MainWindow
		&operator=( const MainWindow &c );

public:

	wxWindow               *m_moviePanel;
	lnb::LibrarySizer      *m_librarySizer;
	wxWindow               *m_timelineWindow;
	SamplePropertiesWindow *m_samplePropertiesWindow;


	void
		onQuit( wxCommandEvent &event );

	void
		onAbout( wxCommandEvent &event );

	void
		onSamplesTreeChange( wxTreeEvent& event );

private:

	wxSizer *m_mainSizer;
	wxSizer *m_sampleAndMovieSizer;

	static unsigned int m_nSamples;

	std::string m_filename;

	gst::GstreamerThread       *m_gstThread;

	const wxPoint
		&getStartupPosition( wxPoint &defaultPosition ) const;

	const wxSize
		&getStartupSize( wxSize &defaultSize ) const;


	wxDECLARE_EVENT_TABLE();

};


	}


#endif