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
#define YTPKING_GST_Pipeline_cpp
#include "Pipeline.h"

#include <gst/gst.h>
#include <gst/interfaces/xoverlay.h>

#include <wx/window.h>

#include "gnl/Composition.h"


	namespace ytpking
	{
	namespace gst
	{


Pipeline::Pipeline( void ) :
	m_pipeline( NULL ),
	m_hasSetRenderWindow( false )
{
}


Pipeline::~Pipeline( void )
{
	if ( m_pipeline )
	{
		stop();
		gst_object_unref( m_pipeline );
	}
}



void
Pipeline::initialize( void )
{
	m_pipeline = gst_pipeline_new( "pipeline" );

	GstBus *bus = gst_element_get_bus( m_pipeline );
	gst_bus_enable_sync_message_emission( bus );
	gst_bus_add_signal_watch( bus );

	g_signal_connect( bus, "message", (GCallback)onMessage, this );
}

void
Pipeline::setRenderWindow( wxWindow *renderWindow )
{
	if ( m_pipeline != NULL )
	{
		GstBus *bus = gst_element_get_bus( m_pipeline );
		g_signal_connect( bus, "sync-message::element", (GCallback)onSyncMessage, renderWindow );

		m_hasSetRenderWindow = true;
	}
}


void
Pipeline::play( void )
{
	if ( m_hasSetRenderWindow )
		gst_element_set_state( m_pipeline, GST_STATE_PLAYING );
}


void
Pipeline::stop( void )
{
	if ( m_hasSetRenderWindow )
		gst_element_set_state( m_pipeline, GST_STATE_NULL );
}


GstElement
*Pipeline::operator*( void )
{
	return m_pipeline;
}


void
Pipeline::onMessage( GstBus *bus, GstMessage *message, gpointer data )
{
	Pipeline *pipeline = (Pipeline *)data;

	switch ( GST_MESSAGE_TYPE( message ) )
	{
	case GST_MESSAGE_EOS:
	case GST_MESSAGE_ERROR:
		pipeline->stop();

	default:
		break;
	}
}


void
Pipeline::onSyncMessage( GstBus *bus, GstMessage *message, gpointer data )
{
	const GstStructure *structure = gst_message_get_structure( message );
	const char *structureName = gst_structure_get_name( structure );
	
	wxWindow *window = (wxWindow *)data;

	if ( strcmp( structureName, "prepare-xwindow-id" ) == 0 )
	{
		GstObject *imagesink = GST_MESSAGE_SRC( message );
		g_object_set( imagesink, "force-aspect-ratio", true, NULL );
		gst_x_overlay_set_xwindow_id( GST_X_OVERLAY( imagesink ), (gulong)window->GetHWND() );
	}
}


	} }