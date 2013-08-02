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
#include "SourcesListCtrl.h"

#include <wx/imaglist.h>




	namespace ytpking
	{
	namespace snb
	{


SourcesListCtrl::SourcesListCtrl( wxWindow *parent ) :
	wxListCtrl( parent, -1, wxDefaultPosition, wxDefaultSize,
	            wxLC_ICON|wxLC_SINGLE_SEL|wxLC_NO_HEADER )
{
	wxImageList *imageList = new wxImageList( 32, 32, false );
	imageList->Add( wxBitmap( "ICO_SPIRALBOX", wxBITMAP_TYPE_ICO_RESOURCE ) );

	AssignImageList( imageList, wxIMAGE_LIST_NORMAL );

	wxListItem item;

	item.SetText( "Derp" );
	item.SetId( 0 );
	item.SetImage( 0 );

	InsertItem( item );
}


	} }