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
#ifndef __YTPKING_SampleWindow_h
#define __YTPKING_SampleWindow_h

#include <wx/window.h>
#include <wx/dnd.h>


	namespace ytpking
	{


namespace smp
{
	class Tape;
	class SampleInstance;
}


class SampleWindow :
	public wxWindow
{
public:

	SampleWindow( wxWindow *parent,
			smp::Tape *tape, const smp::SampleInstance *sampleInstance );


	wxWindow *m_parent;

	smp::Tape                 *m_tape;
	const smp::SampleInstance *m_sampleInstance;

	void
		onButtonDelete( wxCommandEvent& event );


	wxDECLARE_EVENT_TABLE();

};


	}


#endif