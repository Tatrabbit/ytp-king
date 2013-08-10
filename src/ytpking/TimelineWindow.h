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
#ifndef __YTPKING_TimelineWindow_h
#define __YTPKING_TimelineWindow_h

#include <wx/window.h>
#include <smp/TapeUser.h>
#include <wx/dnd.h>
#include "gst/gnl/PreviewUser.h"

	namespace ytpking
	{


class TimelineWindow :
	public wxWindow,
	public smp::TapeUser
{
public:

	TimelineWindow( wxWindow *parent );

private:

	class TimelineDropTarget :
		public wxDropTarget,
		public gst::gnl::PreviewUser
	{
	public:

		TimelineDropTarget( wxWindow *parent, wxSizer *sizer );

		/// TODO Only show drags will be accepted if they've originated from
		//       certain controls fromthis program.

		//wxDragResult
		//	OnDragOver( wxCoord x, wxCoord y, wxDragResult defResult )
		//	override;


		wxDragResult
			OnData( wxCoord x, wxCoord y, wxDragResult defResult )
			override;

	private:

		wxWindow *m_parent;
		wxSizer  *m_sizer;

	};


	void
		onUpdate( wxUpdateUIEvent& event );

	
	void
		onAddTape( smp::Tape *addedTape )
		override;
	void
		onSelectTape( smp::Tape *selectedTape )
		override;
	void
		onDeleteTape( smp::Tape *deletedTape )
		override;


	wxDECLARE_EVENT_TABLE();
	
};


	}


#endif