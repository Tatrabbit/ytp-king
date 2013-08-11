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
#include "ytpking/SampleComponent.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/log.h>

#include "gst/gnl/TapeComposition.h"

	namespace ytpking
	{


SampleComponent::SampleComponent( wxWindow *parent, const char *name,
		const gst::gnl::FileSource *audio,
		const gst::gnl::FileSource *video ) :

	wxWindow( parent, wxID_ANY ),
	m_parent( parent ),
	m_audioSource( audio ),
	m_videoSource( video )
{
	wxSizer *sizer = new wxStaticBoxSizer( wxHORIZONTAL, this, name );

	wxButton *button = new wxButton( this, EventId::ButtonDelete, "Delete" );

	sizer->Add( button, 0 );

	SetSizer( sizer );
}


void
SampleComponent::onButtonDelete( wxCommandEvent& event )
{
	m_audioPreviewComposition->deleteSource( m_audioSource );
	m_videoPreviewComposition->deleteSource( m_videoSource );

	m_audioPreviewComposition->update();
	m_videoPreviewComposition->update();
	
	Destroy();
}



BEGIN_EVENT_TABLE( SampleComponent, wxWindow )
	
	EVT_BUTTON( EventId::ButtonDelete, onButtonDelete )

END_EVENT_TABLE()


	}