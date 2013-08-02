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
#include "ytpking/TimelineSizer.h"
#include "SampleDataObject.h"

#include <wx/wx.h>

	namespace ytpking
	{


TimelineSizer::
TimelineDropTarget::TimelineDropTarget( void ) :
	wxDropTarget( new SampleDataObject )
{
}


wxDragResult
TimelineSizer::
TimelineDropTarget::OnData( wxCoord, wxCoord, wxDragResult defResult )
{
	if ( GetData() )
	{
		GetData();
		SampleDataObject *dataObject = (SampleDataObject *)GetDataObject();
		wxSafeShowMessage( _("Derp"), dataObject->GetData() );

		return defResult;
	}
	else
		return wxDragNone;
}



TimelineSizer::TimelineSizer( wxWindow *parent ) :
	wxBoxSizer( wxHORIZONTAL )
{
	m_firstSample = new wxWindow( parent, wxID_ANY, wxDefaultPosition, wxSize( 200, 100 ) );
	m_firstSample->SetOwnBackgroundColour( wxColour( "red" ) );

	m_firstSample->SetDropTarget( new TimelineDropTarget );

	Add( m_firstSample, 0 );
}


	}