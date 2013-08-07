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
#include "ytpking/MainWindow.h"

#include <gst/gst.h>

#include <wx/log.h>
#include <wx/menu.h>
#include <wx/treectrl.h>
#include <wx/spinctrl.h>

#include "ytpking/EventId.h"

#include "ytpking/DataFile.h"

#include "gst/GstreamerThread.h"
#include "gst/Pipeline.h"
#include "gst/gnl/AudioComposition.h"
#include "gst/gnl/VideoComposition.h"
#include "gst/gnl/FileSource.h"

#include "lnb/LibrarySizer.h"
#include "lnb/SamplesTreeCtrl.h"

#include "TimelineSizer.h"
#include "SamplePropertiesSizer.h"

#include "Sample.h"


	namespace ytpking
	{


unsigned int
	MainWindow::m_nSamples( 0u );


MainWindow::MainWindow( void ) :
	wxFrame( NULL, -1, "YTP King", getStartupPosition( wxPoint(50, 50) ), getStartupSize( wxSize( 800, 600 ) ) ),
	m_gstThread( new gst::GstreamerThread )
{
	gst::timelinePipeline.initialize();

	PreviewUser::init( &gst::timelinePipeline );

	// Get the folder save path
	DataFile::init();

	// Remove the ugly grey tinge on Windows
	SetBackgroundColour( wxNullColour );

	m_librarySizer          = new lnb::LibrarySizer( this, GlobalEventId::SamplesTreeCtrl );
	m_timelineWindow        = new TimelineWindow( this );
	m_samplePropertiesSizer = new SamplePropertiesSizer( this, GlobalEventId::SamplePropsSpinStartFrame );

	wxMenu *menuFile = new wxMenu;

	menuFile->Append( GlobalEventId::MainMenuAbout, _("&Play") );
	menuFile->AppendSeparator();
	menuFile->Append( GlobalEventId::MainMenuQuit, _("&Quit") );

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, _("&File") );

	SetMenuBar( menuBar );

	m_mainSizer = new wxBoxSizer( wxHORIZONTAL );

	m_mainSizer->Add( m_librarySizer, 1, wxEXPAND );

	m_sampleAndMovieSizer = new wxBoxSizer( wxHORIZONTAL );

	wxSizer *movieSizer = new wxBoxSizer( wxVERTICAL );

	wxSizer *entrySizer = new wxBoxSizer( wxHORIZONTAL );

	m_textControl = new wxTextCtrl( this, -1 );

	entrySizer->Add( m_textControl, 1, wxALL|wxEXPAND );

	movieSizer->Add( entrySizer, 0, wxALL|wxEXPAND );

		// movie panel
	m_moviePanel = new wxWindow( this, wxID_ANY );
	m_moviePanel->SetOwnBackgroundColour( wxColour( "black" ) );

	gst::timelinePipeline.setRenderWindow( m_moviePanel );

	movieSizer->Add( m_moviePanel, 1, wxALL|wxEXPAND );
	movieSizer->Add( m_timelineWindow, 0, wxALL|wxEXPAND );

	m_sampleAndMovieSizer->Add( m_samplePropertiesSizer );
	m_sampleAndMovieSizer->Add( movieSizer, 1, wxALL|wxEXPAND );

	m_mainSizer->Add( m_sampleAndMovieSizer, 3, wxEXPAND );

	m_sampleAndMovieSizer->Hide( m_samplePropertiesSizer );
	m_sampleAndMovieSizer->Layout();

	this->SetSizer( m_mainSizer );

	CreateStatusBar();
	SetStatusText( "Roll your cursor over something and look here for help." );
}


MainWindow::~MainWindow( void )
{
	PreviewUser::cleanup();
	delete m_gstThread;
}


void
MainWindow::onQuit( wxCommandEvent &WXUNUSED(event) )
{
	Close( true );
}


void
MainWindow::onAbout( wxCommandEvent &WXUNUSED(event) )
{
	/*wxMessageBox( _("This is a wxWidgets Hello World sample"),
		          _("About Hello World"),
				  wxOK | wxICON_INFORMATION, this );*/

	// Start playing
	m_filename = m_textControl->GetValue();

	gst::timelinePipeline.play();
}


void
MainWindow::onSamplesTreeChange( wxTreeEvent& event )
{
	wxTreeItemId selectedItem =  event.GetItem();

	if ( !selectedItem.IsOk() )
		return;

	lnb::SamplesTreeCtrl *tree =  m_librarySizer->getSamplesTreeCtrl();

	wxTreeItemData *data = tree->GetItemData( selectedItem );

	if ( data )
	{
		lnb::SamplesTreeCtrl::SamplesTreeData *treeData;
		treeData = (lnb::SamplesTreeCtrl::SamplesTreeData *)data;

		m_sampleAndMovieSizer->Show( m_samplePropertiesSizer );
		m_sampleAndMovieSizer->Layout();

		int start = treeData->m_sample->m_start;
		int end   = start + treeData->m_sample->m_duration;

		m_samplePropertiesSizer->updateConstraints( start, end );

		m_samplePropertiesSizer->setStart( start );
		m_samplePropertiesSizer->setEnd( end );

		wxTreeItemId speakerItem = tree->getSpeaker( selectedItem );

		if ( speakerItem.IsOk() )
			m_samplePropertiesSizer->setSpeakerName( tree->GetItemText( speakerItem ) );
	}
	else
	{
		m_sampleAndMovieSizer->Hide( m_samplePropertiesSizer );
		m_sampleAndMovieSizer->Layout();
	}
}

void
MainWindow::onSpinSamplePropertiesStartChange( wxSpinEvent& event )
{
	wxTreeCtrl *tree          =  m_librarySizer->getSamplesTreeCtrl();
	wxTreeItemId selectedItem = tree->GetSelection();

	wxTreeItemData *data = tree->GetItemData( selectedItem );

	if ( data )
	{
		lnb::SamplesTreeCtrl::SamplesTreeData *treeData;
		treeData = (lnb::SamplesTreeCtrl::SamplesTreeData *)data;

		int start    = event.GetInt();
		int end      = m_samplePropertiesSizer->getEnd();
		int duration = end - start;

		treeData->m_sample->m_start    = start;
		treeData->m_sample->m_duration = duration;

		m_audioPreviewComposition->update();
		m_videoPreviewComposition->update();

		m_samplePropertiesSizer->updateConstraints();
	}
}


void
MainWindow::onSpinSamplePropertiesEndChange( wxSpinEvent& event )
{
	wxTreeCtrl *tree =  m_librarySizer->getSamplesTreeCtrl();
	wxTreeItemId selectedItem = tree->GetSelection();

	wxTreeItemData *data = tree->GetItemData( selectedItem );

	if ( data )
	{
		lnb::SamplesTreeCtrl::SamplesTreeData *treeData;
		treeData = (lnb::SamplesTreeCtrl::SamplesTreeData *)data;

		int start = m_samplePropertiesSizer->getStart();
		int duration = event.GetInt() - start;

		treeData->m_sample->m_duration = duration;

		m_audioPreviewComposition->update();
		m_videoPreviewComposition->update();

		m_samplePropertiesSizer->updateConstraints();
	}
}


void
MainWindow::onSampleTextSpeakerNameChange( wxCommandEvent& event )
{
	lnb::SamplesTreeCtrl *tree =  m_librarySizer->getSamplesTreeCtrl();
	wxTreeItemId selectedItem = tree->GetSelection();

	if ( selectedItem.IsOk() )
		if ( tree->renameSpeaker( event.GetString(), selectedItem ) )
		{
			wxWindow *window = (wxWindow *)event.GetEventObject();
			window->SetFocus();
		}
}


const wxPoint
&MainWindow::getStartupPosition( wxPoint &defaultPosition ) const
{
	/** \todo TODO save the window position, check monitor size. */
	return defaultPosition;
}


const wxSize
&MainWindow::getStartupSize( wxSize &defaultSize ) const
{
	/** \todo save the window size, check monitor size. */
	return defaultSize;
}


BEGIN_EVENT_TABLE( MainWindow, wxFrame )

	EVT_MENU( GlobalEventId::MainMenuQuit,  onQuit  )
	EVT_MENU( GlobalEventId::MainMenuAbout, onAbout )

	EVT_TREE_SEL_CHANGED( GlobalEventId::SamplesTreeCtrl, onSamplesTreeChange )

	EVT_SPINCTRL( GlobalEventId::SamplePropsSpinStartFrame, onSpinSamplePropertiesStartChange )
	EVT_SPINCTRL( GlobalEventId::SamplePropsSpinEndFrame, onSpinSamplePropertiesEndChange )

	EVT_TEXT( GlobalEventId::SamplePropsTextSpeakerName, onSampleTextSpeakerNameChange)
END_EVENT_TABLE()


	}