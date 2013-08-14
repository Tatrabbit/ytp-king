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
#include "MovieControlsWindow.h"

#include <wx/slider.h>
#include <wx/sizer.h>

#include "gst/Pipeline.h"

	namespace ytpking
	{


MovieControlsWindow::MovieControlsWindow( wxWindow *parent ) :
	wxWindow( parent, wxID_ANY )
{
	m_seekSlider = new wxSlider( this, wxID_ANY, 0, 0, INT_MAX, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_TOP|wxSL_AUTOTICKS );

	wxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );
	mainSizer->Add( m_seekSlider, 1, wxALL|wxEXPAND );

	SetSizer( mainSizer );
}


void
MovieControlsWindow::onSeekSlider( wxScrollEvent &event )
{
	gst::timelinePipeline.seek( (double)event.GetInt() / (double)INT_MAX );
}


wxBEGIN_EVENT_TABLE( MovieControlsWindow, wxWindow )

	EVT_COMMAND_SCROLL_THUMBRELEASE( wxID_ANY, onSeekSlider )

wxEND_EVENT_TABLE()


	}