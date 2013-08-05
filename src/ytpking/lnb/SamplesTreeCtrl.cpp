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
SamplesTreeCtrl::addSample( const char *name, const char *speaker,
		gst::gnl::FileSource *audioSource,
		gst::gnl::FileSource *videoSource )
{
	SamplesTreeData *data = new SamplesTreeData( "file:///C:/zelda.mp4" );

	wxTreeItemId root, speakerItem;
	
	root = GetRootItem();

	wxTreeItemIdValue cookie;

	speakerItem = GetFirstChild( root, cookie );
	while( speakerItem.IsOk() )
	{
		if ( strcmp( GetItemText( speakerItem ), speaker ) == 0 )
		{
			AppendItem( speakerItem, name, -1, -1, data );
			return;
		}

		speakerItem = GetNextChild( root, cookie );
	}

	speakerItem = AppendItem( root, speaker );
	AppendItem( speakerItem, name, -1, -1, data );
}


wxBEGIN_EVENT_TABLE( SamplesTreeCtrl, wxTreeCtrl )

	EVT_TREE_BEGIN_DRAG( wxID_ANY, onBeginDrag  )
	EVT_TREE_BEGIN_LABEL_EDIT( wxID_ANY, onBeginEditLabel )

wxEND_EVENT_TABLE()


	} }