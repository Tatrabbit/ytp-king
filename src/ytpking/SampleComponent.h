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
#ifndef __YTPKING_SampleComponent_h
#define __YTPKING_SampleComponent_h

#include <wx/window.h>
#include <wx/dnd.h>

#include "smp/Tape.h"

	namespace ytpking
	{


class SampleComponent :
	public wxWindow
{
public:

	SampleComponent( wxWindow *parent, const char *name,
			smp::Tape *tape, const smp::Tape::SampleInstance *sampleInstance );


	wxWindow *m_parent;

	smp::Tape                 *m_tape;
	const smp::Tape::SampleInstance *m_sampleInstance;

	void
		onButtonDelete( wxCommandEvent& event );


	wxDECLARE_EVENT_TABLE();

};


	}


#endif