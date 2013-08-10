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
#include "SourcesPage.h"

#include <wx/sizer.h>

#include "SourcesListCtrl.h"


	namespace ytpking
	{
	namespace lnb
	{


SourcesPage::SourcesPage( wxWindow *parent ) :
	wxNotebookPage( parent, -1 )
{
	m_listCtrl = new SourcesListCtrl( this );

	wxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );
	
	mainSizer->Add( m_listCtrl, 1, wxEXPAND|wxALL );

	SetSizer( mainSizer );
}


	} }