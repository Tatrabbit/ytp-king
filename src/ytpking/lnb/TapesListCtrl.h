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
#ifndef YTPKING_LNB_TapesListCtrl_h
#define YTPKING_LNB_TapesListCtrl_h

#include <wx/listctrl.h>
#include "smp/TapeUser.h"


	namespace ytpking
	{
	namespace lnb
	{


class TapesListCtrl :
	public wxListCtrl,
	public smp::TapeUser
{
public:

	TapesListCtrl( wxWindow *parent );

	void
		onAddTape( smp::Tape &addedTape )
		override;
	void
		onSelectTape( smp::Tape *selectedTape )
		override;
	void
		onDeleteTape( smp::Tape &deletedTape )
		override;

	void
		onSelectItem( wxListEvent& event );


	wxDECLARE_EVENT_TABLE();

};


	} }


#endif