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
#ifndef __YTPKING_GST_GNL_SamplesTreeCtrl_h
#define __YTPKING_GST_GNL_SamplesTreeCtrl_h

#include <wx/treectrl.h>


	namespace ytpking
	{

class Sample;

namespace gst {
namespace gnl {
	class FileSource;
} }

	namespace lnb
	{


class SamplesTreeCtrl :
	public wxTreeCtrl
{
public:

	SamplesTreeCtrl( wxWindow *parent, int samplesId );

	void
		onBeginDrag( wxTreeEvent &event );

	void
		addSample( const char *name, const char *speaker,
				gst::gnl::FileSource *audioSource,
				gst::gnl::FileSource *videoSource );

	class SamplesTreeData :
		public wxTreeItemData
	{
	public:
		SamplesTreeData( char const *filename );
		virtual
			~SamplesTreeData( void );

	private: // TODO macros for = delete when it becomes available.
		SamplesTreeData( const SamplesTreeData &c );

		SamplesTreeData
			&operator=( const SamplesTreeData &c );

	public:

		// TODO constructor, default to NULL
		Sample *m_sample;

	};


	wxDECLARE_EVENT_TABLE();

};


	} }


#endif