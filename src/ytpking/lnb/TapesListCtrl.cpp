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
#include "TapesListCtrl.h"
#include "smp/TapeManager.h"

	namespace ytpking
	{
	namespace lnb
	{


TapesListCtrl::TapesListCtrl( wxWindow *parent ) :
	// TODO make this be wxLC_VIRTUAL
	wxListCtrl( parent, wxID_ANY,wxDefaultPosition, wxDefaultSize,
	            wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES ),
	smp::TapeUser( smp::tapeManager )
{
	AppendColumn( "What's Said" );
}


void
TapesListCtrl::onAddTape( smp::Tape &addedTape )
{
	InsertItem( 0, "Your Majesty" );
	SetItemPtrData( 0, (wxUIntPtr)&addedTape );
}


void
TapesListCtrl::onSelectTape( smp::Tape *selectedTape )
{
}


void
TapesListCtrl::onDeleteTape( smp::Tape &deletedTape )
{
	DeleteItem( 0 );
}


void
TapesListCtrl::onSelectItem( wxListEvent& event )
{
	smp::Tape *tape = (smp::Tape *)GetItemData( event.GetIndex() );
	smp::tapeManager.selectTape( tape );
}


wxBEGIN_EVENT_TABLE( TapesListCtrl, wxListCtrl )

	EVT_LIST_ITEM_SELECTED( wxID_ANY, onSelectItem )

wxEND_EVENT_TABLE()


	} }