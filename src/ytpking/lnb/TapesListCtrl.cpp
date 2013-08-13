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
#include "TapesListCtrl.h"

#include "smp/TapeManager.h"
#include "smp/Tape.h"


	namespace ytpking
	{
	namespace lnb
	{


TapesListCtrl::TapesListCtrl( wxWindow *parent ) :
	// TODO make this be wxLC_VIRTUAL
	wxListCtrl( parent, wxID_ANY,wxDefaultPosition, wxDefaultSize,
		wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxLC_EDIT_LABELS ),
	smp::TapeUser( smp::tapeManager )
{
	AppendColumn( "What's Said" );
	AppendColumn( "Speakers" );
}


void
TapesListCtrl::onAddTape( smp::Tape &addedTape )
{
	int index = GetItemCount();

	InsertItem( index, addedTape.getName() );
	SetItemPtrData( index, (wxUIntPtr)&addedTape );
}


void
TapesListCtrl::onSelectTape( smp::Tape *selectedTape )
{
}


void
TapesListCtrl::onDeleteTape( smp::Tape &deletedTape )
{
	using smp::Tape;

	for ( int i = 0, count = GetItemCount(); i < count; ++i )
	{
		Tape *tape = (Tape *)GetItemData( i );

		if ( tape == &deletedTape )
		{
			DeleteItem( i );
			return;
		}
	}
}


void
TapesListCtrl::onSelectItem( wxListEvent& event )
{
	smp::Tape *tape = (smp::Tape *)GetItemData( event.GetIndex() );
	smp::tapeManager.selectTape( tape );
}


void
TapesListCtrl::onEditLabel( wxListEvent& event )
{
	if ( event.IsEditCancelled() )
		return;
	smp::Tape *tape = (smp::Tape *)GetItemData( event.GetIndex() );
	tape->setName( event.GetLabel() );
}


wxBEGIN_EVENT_TABLE( TapesListCtrl, wxListCtrl )

	EVT_LIST_ITEM_SELECTED( wxID_ANY, onSelectItem )
	EVT_LIST_END_LABEL_EDIT( wxID_ANY, onEditLabel )

wxEND_EVENT_TABLE()


	} }