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
#include "SamplesTreeCtrl.h"


	namespace ytpking
	{
	namespace snb
	{


SamplesTreeCtrl::SamplesTreeCtrl( wxWindow *parent ) :
	wxTreeCtrl( parent, wxID_ANY,wxDefaultPosition, wxDefaultSize,
	            wxTR_HAS_BUTTONS|wxTR_SINGLE|wxTR_TWIST_BUTTONS|
				wxTR_ROW_LINES|wxTR_HIDE_ROOT)
{
	wxTreeItemId root = AddRoot( "" );

	wxTreeItemId derpItem = AppendItem( root, "Derp" );
	wxTreeItemId herpItem = AppendItem( derpItem, "Herp" );
	AppendItem( herpItem, "Poppins" );
}


	} }