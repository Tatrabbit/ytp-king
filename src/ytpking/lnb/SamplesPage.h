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
#ifndef __YTPKING_LNB_SamplesPage_h
#define __YTPKING_LNB_SamplesPage_h

#include <wx/notebook.h>
#include "../gst/gnl/PreviewUser.h"


	namespace ytpking
	{
	namespace lnb
	{


class SourcesToolbar;
class SamplesTreeCtrl;


class SamplesPage :
	public wxNotebookPage,
	public gst::gnl::PreviewUser
{
public:

	SamplesPage( wxWindow *parent );

	SamplesTreeCtrl *m_treeCtrl;
	SourcesToolbar  *m_toolbar;

	void
		onButtonAdd( wxCommandEvent& event );


	wxDECLARE_EVENT_TABLE();
};


	} }


#endif	

