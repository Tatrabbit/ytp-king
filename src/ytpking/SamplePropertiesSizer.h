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
#ifndef __YTPKING_SamplePropertiesSizer_h
#define __YTPKING_SamplePropertiesSizer_h

#include <wx/sizer.h>


class wxTextCtrl;

	namespace ytpking
	{


class SamplePropertiesSizer :
	// TODO Once things are a bit more ready, change this to derive from wxGridBagSizer
	//      and position everything nicely.
	public wxGridSizer
{
public:

	SamplePropertiesSizer( wxWindow *parent, int startId );

	void
		setStart( unsigned int start );
	void
		setEnd( unsigned int end );

	int
		getStart( void ) const;
	int
		getEnd( void ) const;

	const char
		*getSpeakerName( void ) const;
	void
		setSpeakerName( const char *speakerName );

	void
		updateConstraints( void );

	void
		updateConstraints( int start, int end );

private:

	wxSpinCtrl *m_startFrameSpinCtrl;
	wxSpinCtrl *m_endFrameSpinCtrl;

	wxTextCtrl *m_speakerName;


	void
		onSpeakerNameChange( wxCommandEvent& event );


	//wxDECLARE_EVENT_TABLE();
	
};


	}


#endif