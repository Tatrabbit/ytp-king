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
#include "SamplePropertiesSizer.h"

#include <wx/spinctrl.h>
#include <wx/textctrl.h>


	namespace ytpking
	{


SamplePropertiesSizer::SamplePropertiesSizer( wxWindow *parent, int startId ) :
	wxGridSizer( 2, 8, 8 )
{
	m_startFrameSpinCtrl = new wxSpinCtrl( parent, startId, wxEmptyString, wxDefaultPosition, wxSize( 80, -1 ), wxSP_ARROW_KEYS, 0, 5  );
	m_endFrameSpinCtrl   = new wxSpinCtrl( parent, startId + 1, wxEmptyString, wxDefaultPosition, wxSize( 80, -1 ), wxSP_ARROW_KEYS, 1, 100  );

	m_speakerName = new wxTextCtrl( parent, startId + 2 );

	Add( m_startFrameSpinCtrl );
	Add( m_endFrameSpinCtrl );

	Add( m_speakerName, 0 );
}


void
SamplePropertiesSizer::setStart( unsigned int start )
{
	m_startFrameSpinCtrl->SetValue( start );
}


void
SamplePropertiesSizer::setEnd( unsigned int end )
{
	m_endFrameSpinCtrl->SetValue( end );
}


int
SamplePropertiesSizer::getStart( void ) const
{
	return m_startFrameSpinCtrl->GetValue();
}


int
SamplePropertiesSizer::getEnd( void ) const
{
	return m_endFrameSpinCtrl->GetValue();
}


const char
*SamplePropertiesSizer::getSpeakerName( void ) const
{
	return m_speakerName->GetValue();
}


void
SamplePropertiesSizer::setSpeakerName( const char *speakerName )
{
	m_speakerName->ChangeValue( speakerName );
	m_speakerName->SetInsertionPointEnd();
}


void
SamplePropertiesSizer::updateConstraints( void )
{
	m_startFrameSpinCtrl->SetMax( m_endFrameSpinCtrl->GetValue() - 1 );
	m_endFrameSpinCtrl->SetMin( m_startFrameSpinCtrl->GetValue() + 1 );
}


void
SamplePropertiesSizer::updateConstraints( int start, int end )
{
	m_startFrameSpinCtrl->SetMax( end - 1 );
	m_endFrameSpinCtrl->SetMin( start + 1 );
}


	} 