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

#include <wx/textctrl.h>


class wxTreeEvent;

	namespace ytpking
	{

class SamplePropertiesSizer;

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

	wxWindow              *m_moviePanel;
	lnb::LibrarySizer     *m_librarySizer;
	wxWindow              *m_timelineWindow;
	SamplePropertiesSizer *m_samplePropertiesSizer;


	//// BEGIN wx Events

	void
		onQuit( wxCommandEvent &event );

	void
		onAbout( wxCommandEvent &event );

	void
		onSamplesTreeChange( wxTreeEvent& event );

	void
		onSpinSamplePropertiesStartChange( wxSpinEvent& event );
	void
		onSpinSamplePropertiesEndChange( wxSpinEvent& event );

	//// END wx Events

private:

	enum EventId
	{
		MenuQuit = 1,
		MenuAbout,
		PageSamples,
		SpinSampleStartFrame,
		SpinSampleEndFrame
	};
	wxSizer *m_mainSizer;
	wxSizer *m_sampleAndMovieSizer;

	static unsigned int m_nSamples;

	std::string m_filename;

	wxTextCtrl *m_textControl;

	gst::GstreamerThread       *m_gstThread;
	gst::Pipeline              *m_pipeline;

	wxDECLARE_EVENT_TABLE();

	const wxPoint
		&getStartupPosition( wxPoint &defaultPosition ) const;

	const wxSize
		&getStartupSize( wxSize &defaultSize ) const;

};


	}