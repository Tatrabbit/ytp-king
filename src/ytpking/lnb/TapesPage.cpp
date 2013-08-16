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
#include "TapesPage.h"

#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/button.h>

#include "TapesListCtrl.h"

#include "smp/TapeManager.h"


	namespace ytpking
	{
	namespace lnb
	{


TapesPage::TapesPage( wxWindow *parent ) :
	wxNotebookPage( parent, wxID_ANY )
{
	// Main Sizer
	wxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );

	// Tapes ListCtrl
	m_listCtrl = new TapesListCtrl( this );
	mainSizer->Add( m_listCtrl, 1, wxEXPAND|wxALL );

	// Toolbar
	wxSizer *toolbarSizer = new wxBoxSizer( wxHORIZONTAL );
	{
		// Add button
		wxButton *button;

		button = new wxButton( this, EventId::ButtonAdd );

		button->SetBitmap( wxBitmap( "ICO_SPIRALBOX", wxBITMAP_TYPE_ICO_RESOURCE ) );
		button->SetWindowStyle( wxBU_EXACTFIT|wxBU_NOTEXT );
		toolbarSizer->Add( button, 1 );
	}
	mainSizer->Add( toolbarSizer, 0 );

	// Assign
	SetSizer( mainSizer );
}


void
TapesPage::onButtonAdd( wxCommandEvent& event )
{
	smp::tapeManager->addTape( "New Tape" );
}



wxBEGIN_EVENT_TABLE( TapesPage, wxNotebookPage )

	EVT_BUTTON( EventId::ButtonAdd,  onButtonAdd  )

wxEND_EVENT_TABLE()



	} }