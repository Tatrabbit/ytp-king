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

#include "ytpking/SamplesDataFile.h"


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
		onBeginEditLabel( wxTreeEvent &event );
	void
		onEndEditLabel( wxTreeEvent &event );
	void
		onCollapsing( wxTreeEvent &event );

	/** Adds a sample to me.
	\param name the name of the sample, such as "Gee, it sure is boring around here".
	\param speaker The name of the speaker, such as "Mario" or "Link"
	\param audioSource the FileSource to be associated for audio.
	\param videoSource the FileSource to be associated for video.
	\param nodeReference If not NULL, the node is copied into to the tree item. If NULL,
	                     the SavaData is notified of a new node, and the data will be saved. */
	void
		addSample( const char *name, const char *speaker,
				SamplesDataFile::NodeReference *nodeReference = NULL );

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

	wxTreeItemId
		changeSpeaker( const wxTreeItemId &speech, const wxTreeItemId &currentSpeaker, const wxTreeItemId &newSpeaker );

	bool
		renameSpeaker( const char *newName, const wxTreeItemId &speechItem );


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

		SamplesDataFile::NodeReference m_nodeReference;
	};

private:

	SamplesDataFile *m_samplesDataFile;

	wxDECLARE_EVENT_TABLE();

};


	} }


#endif