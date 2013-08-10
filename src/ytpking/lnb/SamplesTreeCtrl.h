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
#include "../gst/gnl/SampleUser.h"


	namespace ytpking
	{

namespace smp {
	class Sample;
}

namespace gst {
namespace gnl {
	class FileSource;
} }

	namespace lnb
	{


class SamplesTreeCtrl :
	public wxTreeCtrl,
	public gst::gnl::SampleUser
{
public:

	SamplesTreeCtrl( wxWindow *parent, int samplesId );

	void
		onBeginDrag( wxTreeEvent &event );
	void
		onBeginEditLabel( wxTreeEvent &event );
	void
		onEndEditLabel( wxTreeEvent &event );
	void
		onCollapsing( wxTreeEvent &event );
	void
		onSelectionChanging( wxTreeEvent &event );


	/** Gets the speaker wxTreeItemId with the given name.
	\param speakerName the name of the speaker to find
	\return A wxTreeItemId regardless of whether it was found. to check, use IsOk() */
	wxTreeItemId
		getSpeaker( const char *speakerName ) const;

	/** Gets the speaker node parent of the given node.
	No matter how deep it's nested, this will return the speaker parent node.
	\param speech the speech item to find the parent of.
	\return If speech is a valid node, returns a valid Speaker node. If in doubht, check with
	        IsOk() */
	wxTreeItemId
		getSpeaker(	const wxTreeItemId &speech ) const;


	class SamplesTreeData :
		public wxTreeItemData
	{
	public:
		SamplesTreeData( smp::Sample *sample );

		smp::Sample *m_sample;

	};

private:

	const smp::Sample *m_selectedSample;

	void
		onAddSample( char const *sampleName, char const *speakerName, smp::Sample *addedSample )
		override;

	void
		onSelectSample( smp::Sample *selectedSample )
		override;

	void
		onDeleteSample( smp::Sample *deletedSample )
		override;

	void
		onRenameSample( const char *newSampleName, smp::Sample *sample )
		override;

	void
		onChangeSampleSpeaker( char const *speakerName, smp::Sample *sample )
		override;

	wxTreeItemId
		changeSpeaker( const wxTreeItemId &speech, const wxTreeItemId &currentSpeaker, const wxTreeItemId &newSpeaker );

	/** Gets the tree item with the provided sample, searhing the entire tree.
	\param sample The sample to compare with. */
	wxTreeItemId
		getTreeItem( smp::Sample *sample ) const;

	/** Gets the tree item with the provided sample.
		This can only be called on tree items that have speech attached.
	\param sample The sample to compare with
	\param parent the root to start looking at. All sub items will be searched, recursively. */
	wxTreeItemId
		getTreeItem( smp::Sample *sample, const wxTreeItemId &parent ) const;


	wxDECLARE_EVENT_TABLE();

};


	} }


#endif