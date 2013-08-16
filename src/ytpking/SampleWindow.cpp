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
#include "ytpking/SampleWindow.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/log.h>

#include "smp/TapeManager.h"
#include "smp/Tape.h"
#include "smp/Sample.h"
#include "smp/SampleInstance.h"

#include "gst/gnl/PreviewTapes.h"

#include "TimelineWindow.h"


	namespace ytpking
	{


SampleWindow::SampleWindow( wxWindow *parent,
		smp::Tape *tape, smp::SampleInstance *sampleInstance ) :

	wxWindow( parent, wxID_ANY ),
	m_parent( parent ),
	m_tape( tape ),
	m_sampleInstance( sampleInstance )
{
	wxSizer *sizer = new wxStaticBoxSizer( wxHORIZONTAL, this, sampleInstance->getSample().getName() );

	wxButton *button = new wxButton( this, TimelineWindow::ButtonDelete, "Delete" );

	sizer->Add( button, 0 );

	SetSizer( sizer );
}


void
SampleWindow::onButtonDelete( wxCommandEvent& event )
{	
	smp::tapeManager->deleteInstance( m_tape, *m_sampleInstance );

	if ( m_tape == smp::tapeManager->getSelectedTape() )
		gst::gnl::previewTapes.update();

	event.Skip();
}


BEGIN_EVENT_TABLE( SampleWindow, wxWindow )
	
	EVT_BUTTON( TimelineWindow::ButtonDelete, onButtonDelete )

END_EVENT_TABLE()


	}