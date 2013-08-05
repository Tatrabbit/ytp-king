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
#include "SamplesTreeCtrl.h"

#include <wx/imaglist.h>
#include <wx/event.h>
#include <wx/wx.h>
#include <wx/dnd.h>

#include "ytpking/SampleDataObject.h"
#include "ytpking/Sample.h"
#include "ytpking/SamplesDataFile.h"

	namespace ytpking
	{
	namespace lnb
	{


SamplesTreeCtrl::
SamplesTreeData::SamplesTreeData( char const *filename ) :
	m_sample( new Sample( filename ) )
{
}

SamplesTreeCtrl::
SamplesTreeData::~SamplesTreeData( void )
{
	delete m_sample;
}


SamplesTreeCtrl::SamplesTreeCtrl( wxWindow *parent, int samplesId ) :
	wxTreeCtrl( parent, samplesId, wxDefaultPosition, wxDefaultSize,
		wxTR_HAS_BUTTONS|wxTR_SINGLE|wxTR_TWIST_BUTTONS|
			wxTR_ROW_LINES|wxTR_HIDE_ROOT|wxTR_EDIT_LABELS)
{
	// TODO Documentation says there must be an image list for item dragging in MSW.
	//      Does this still apply?

	//wxImageList *imageList = new wxImageList( 32, 32 );
	//imageList->Add( wxBitmap( "ICO_SPIRALBOX", wxBITMAP_TYPE_ICO_RESOURCE ) );
	//AssignImageList( imageList );

	wxTreeItemId root = AddRoot( "" );

	m_samplesDataFile = new SamplesDataFile( this );

	m_samplesDataFile->loadAll();
}


void
SamplesTreeCtrl::onBeginDrag( wxTreeEvent& event )
{
	// It's confusing to drag something, and not see it affected.
	SelectItem( event.GetItem() );

	wxTreeItemData *data = GetItemData( event.GetItem() );
	if ( data )
	{
		SamplesTreeData *treeData = (SamplesTreeData *)data;
		SampleDataObject dataObject( GetItemText( event.GetItem() ) );

		dataObject.m_sample = treeData->m_sample;

		wxDropSource dropSource( this );
		dropSource.SetData( dataObject );

		// wxDragResult result = // should I maybe check this?
		dropSource.DoDragDrop( wxDrag_CopyOnly );
	}
}

	
void
SamplesTreeCtrl::onBeginEditLabel( wxTreeEvent &event )
{
	wxTreeItemId item = event.GetItem();

	if ( !item.IsOk() )
	{
		event.Veto();
		return;
	}

	wxTreeItemData *data = GetItemData( item );
	if ( !data )
	{
		event.Veto();
		return;
	}
}


void
SamplesTreeCtrl::onCollapsing( wxTreeEvent &event )
{
	wxTreeItemId item = event.GetItem();

	wxTreeItemData *data = GetItemData( item );
	if ( !data ) // Prevent collapsing of speakers
	{
		event.Veto();
		return;
	}
}


void
SamplesTreeCtrl::addSample( const char *name, const char *speaker,
		gst::gnl::FileSource *audioSource,
		gst::gnl::FileSource *videoSource )
{
	SamplesTreeData *data = new SamplesTreeData( "file:///C:/zelda.mp4" );

	wxTreeItemId speakerItem = getSpeaker( speaker );
	
	if ( speakerItem.IsOk() )
		AppendItem( speakerItem, name, -1, -1, data );
	else
	{
		speakerItem = AppendItem( GetRootItem(), speaker );
		AppendItem( speakerItem, name, -1, -1, data );
	}

	Expand( speakerItem );

	m_samplesDataFile->addSample( name, speaker );
}


wxTreeItemId
SamplesTreeCtrl::getSpeaker( const char *speakerName ) const
{
	wxTreeItemId root, speakerItem;
	
	root = GetRootItem();

	wxTreeItemIdValue cookie;
	
	speakerItem = GetFirstChild( root, cookie );
	while( speakerItem.IsOk() )
	{
		if ( strcmp( GetItemText( speakerItem ), speakerName ) == 0 )
			return speakerItem;

		speakerItem = GetNextChild( root, cookie );
	}

	return speakerItem;
}

wxTreeItemId
SamplesTreeCtrl::getSpeaker( const wxTreeItemId &speech ) const
{
	wxTreeItemId parentItem = GetItemParent( speech );
	while ( true )
	{
		if ( parentItem.IsOk() )
		{
			if ( GetItemData( parentItem ) == NULL )
				return parentItem;
		}
		else
			return parentItem;

		parentItem = GetItemParent( parentItem );
	}
}


wxTreeItemId
SamplesTreeCtrl::changeSpeaker( const wxTreeItemId &speech,
                                const wxTreeItemId &currentSpeaker,
                                const wxTreeItemId &newSpeaker )
{
	wxTreeItemId newSpeechItem;
	newSpeechItem = AppendItem( newSpeaker, GetItemText( speech ), -1, -1, GetItemData( speech ) );

	SetItemData( speech, NULL ); // replace the data with NULL; speech will not delete it now!
	Delete( speech );

	if ( GetChildrenCount( currentSpeaker ) == 0 )
		Delete( currentSpeaker );

	return newSpeechItem;
}


bool
SamplesTreeCtrl::renameSpeaker( const char *newName, const wxTreeItemId &speechItem )
{
	// Is there a speaker of this new name?
	wxTreeItemId speakerItem = getSpeaker( newName );
	if ( speakerItem.IsOk() )
	{
		// The speaker of this name already exists.
		// So I merge the item into that tree.

		wxTreeItemId currentSpeakerItem = getSpeaker( speechItem );
		if ( currentSpeakerItem.IsOk() )
		{
			SelectItem( changeSpeaker( speechItem, currentSpeakerItem, speakerItem ) );
			return true;
		}
	}
	else
	{
		// The speaker doesn't already exist.

		speakerItem = getSpeaker( speechItem );

		// Do I have siblings?
		if ( GetChildrenCount( speakerItem ) == 1 )
		{
			// There's nobody else. I should change the speaker name in place.
			SetItemText( speakerItem, newName );
			return false;
		}
		else
		{
			// I have a different name than my siblings, I should create a
			// new parent and move there.
			wxTreeItemId newSpeakerItem = AppendItem( GetRootItem(), newName );
			SelectItem( changeSpeaker( speechItem, speakerItem, newSpeakerItem ) );
			return true;
		}
	}

	return false;
}


wxBEGIN_EVENT_TABLE( SamplesTreeCtrl, wxTreeCtrl )

	EVT_TREE_BEGIN_DRAG( wxID_ANY, onBeginDrag  )
	EVT_TREE_BEGIN_LABEL_EDIT( wxID_ANY, onBeginEditLabel )
	EVT_TREE_ITEM_COLLAPSING( wxID_ANY, onCollapsing )

wxEND_EVENT_TABLE()


	} }