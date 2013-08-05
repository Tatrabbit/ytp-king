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
#include "SamplesPage.h"

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/event.h>

#include "SamplesTreeCtrl.h"
#include "SourcesToolbar.h"

#include "../gst/gnl/Composition.h"


	namespace ytpking
	{
	namespace lnb
	{


SamplesPage::SamplesPage( wxWindow *parent, int samplesId ) :
	wxNotebookPage( parent, wxID_ANY )
{
	m_treeCtrl = new SamplesTreeCtrl( this, samplesId );
	m_toolbar = new SourcesToolbar( this );

	wxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );
	mainSizer->Add( m_treeCtrl, 1, wxEXPAND|wxALL );
	mainSizer->Add( m_toolbar, 0);

	SetSizer( mainSizer );
}

void
SamplesPage::onButtonAdd( wxCommandEvent& )
{
	//gst::gnl::FileSource *audioSource, *videoSource;

	//m_audioPreviewComposition->update();
	//m_videoPreviewComposition->update();

	m_treeCtrl->addSample( "Derp", "Herp", NULL, NULL );
}

wxBEGIN_EVENT_TABLE( SamplesPage, wxNotebookPage )

	EVT_BUTTON( SourcesToolbar::ButtonAdd, onButtonAdd )

wxEND_EVENT_TABLE()




	} }