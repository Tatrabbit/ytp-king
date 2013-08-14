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
#include <wx/timer.h>

#include "gst/Pipeline.h"


	namespace ytpking
	{


MovieControlsWindow::MovieControlsWindow( wxWindow *parent ) :
	wxWindow( parent, wxID_ANY ),
	gst::PipelineUser( gst::timelinePipeline )
{
	m_seekSlider = new wxSlider( this, wxID_ANY, 0, 0, INT_MAX, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_TOP|wxSL_AUTOTICKS );

	wxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );
	mainSizer->Add( m_seekSlider, 1, wxALL|wxEXPAND );

	SetSizer( mainSizer );

	m_timer = new wxTimer( this, wxID_ANY );
}


MovieControlsWindow::~MovieControlsWindow( void )
{
	delete m_timer;
}


void
MovieControlsWindow::onSeekSlider( wxScrollEvent &event )
{
	gst::timelinePipeline.seek( (double)event.GetInt() / (double)INT_MAX );
}


void
MovieControlsWindow::onSeekTimer( wxTimerEvent &event )
{
	double seekPosition;
	if ( gst::timelinePipeline.getCurrentPosition( seekPosition ) )
	{
		int position = seekPosition * (double)INT_MAX;
		m_seekSlider->SetValue( position );
	}
	else
		m_seekSlider->SetValue( INT_MAX );
}


void
MovieControlsWindow::onPipelineStateChange( PipelineState oldState, PipelineState newState )
{
	switch ( newState )
	{
	case PipelineState::Playing:
		m_timer->Start( 100 );
		break;

	case PipelineState::Paused:
	case PipelineState::Stopped:
		if ( oldState == PipelineState::Playing )
			m_timer->Stop();
	}
}


wxBEGIN_EVENT_TABLE( MovieControlsWindow, wxWindow )

	EVT_COMMAND_SCROLL_THUMBRELEASE( wxID_ANY, onSeekSlider )
	EVT_COMMAND_SCROLL_PAGEUP( wxID_ANY, onSeekSlider )
	EVT_COMMAND_SCROLL_PAGEDOWN( wxID_ANY, onSeekSlider )
	EVT_TIMER( wxID_ANY, onSeekTimer )

wxEND_EVENT_TABLE()


	}