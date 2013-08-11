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
#include "SamplePropertiesWindow.h"

#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>

#include "smp/SampleManager.h"
#include "smp/Sample.h"


	namespace ytpking
	{


SamplePropertiesWindow::SamplePropertiesWindow( wxWindow *parent ) :
	wxWindow( parent, wxID_ANY )
{
	wxSizer *sizer = new wxGridSizer( 2, 8, 8 );

	m_startFrameSpinCtrl = new wxSpinCtrl( this, SpinStartFrame, wxEmptyString, wxDefaultPosition, wxSize( 80, -1 ), wxSP_ARROW_KEYS, 0, 5  );
	m_endFrameSpinCtrl   = new wxSpinCtrl( this, SpinEndFrame, wxEmptyString, wxDefaultPosition, wxSize( 80, -1 ), wxSP_ARROW_KEYS, 1, 100  );

	m_speakerName = new wxTextCtrl( this, TextSpeakerName );

	sizer->Add( m_startFrameSpinCtrl );
	sizer->Add( m_endFrameSpinCtrl );

	sizer->Add( m_speakerName, 0 );

	SetSizer( sizer );
}


void
SamplePropertiesWindow::setStart( unsigned int start )
{
	m_startFrameSpinCtrl->SetValue( start );
}


void
SamplePropertiesWindow::setEnd( unsigned int end )
{
	m_endFrameSpinCtrl->SetValue( end );
}


int
SamplePropertiesWindow::getStart( void ) const
{
	return m_startFrameSpinCtrl->GetValue();
}


int
SamplePropertiesWindow::getEnd( void ) const
{
	return m_endFrameSpinCtrl->GetValue();
}


const char
*SamplePropertiesWindow::getSpeakerName( void ) const
{
	return m_speakerName->GetValue();
}


void
SamplePropertiesWindow::setSpeakerName( const char *speakerName )
{
	m_speakerName->ChangeValue( speakerName );
	m_speakerName->SetInsertionPointEnd();
}


void
SamplePropertiesWindow::updateConstraints( void )
{
	m_startFrameSpinCtrl->SetMax( m_endFrameSpinCtrl->GetValue() - 1 );
	m_endFrameSpinCtrl->SetMin( m_startFrameSpinCtrl->GetValue() + 1 );
}


void
SamplePropertiesWindow::updateConstraints( int start, int end )
{
	m_startFrameSpinCtrl->SetMax( end - 1 );
	m_endFrameSpinCtrl->SetMin( start + 1 );
}


void
SamplePropertiesWindow::onSpinStartChange( wxSpinEvent& event )
{
	smp::Sample *sample = smp::sampleManager.getSelectedSample();
	if ( sample != NULL )
	{
		int start    = event.GetInt();
		int end      = getEnd();
		int duration = end - start;

		sample->m_start    = start;
		sample->m_duration = duration;
	}

	m_endFrameSpinCtrl->SetMin( event.GetInt() + 1 );
}


void
SamplePropertiesWindow::onSpinEndChange( wxSpinEvent& event )
{
	smp::Sample *sample = smp::sampleManager.getSelectedSample();
	if ( sample != NULL )
		sample->m_duration = event.GetInt() - sample->m_start;

	m_startFrameSpinCtrl->SetMax( event.GetInt() - 1 );
}


void
SamplePropertiesWindow::onTextSpeakerNameChange( wxCommandEvent& event )
{
	smp::Sample *selectedSample = smp::sampleManager.getSelectedSample();
	if ( selectedSample != NULL )
	{
		smp::sampleManager.changeSpeaker( selectedSample, event.GetString().c_str() );

		// refocus me
		wxWindow *window = (wxWindow *)event.GetEventObject();
		window->SetFocus();
	}
}


BEGIN_EVENT_TABLE( SamplePropertiesWindow, wxWindow )

	EVT_SPINCTRL( SpinStartFrame,  onSpinStartChange )
	EVT_SPINCTRL( SpinEndFrame,    onSpinEndChange )

	EVT_TEXT(     TextSpeakerName, onTextSpeakerNameChange )

END_EVENT_TABLE()


	} 