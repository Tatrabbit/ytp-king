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
#include "Pipeline.h"

#include <gst/gst.h>
#include <gst/interfaces/xoverlay.h>

#include <wx/window.h>

#include "gnl/Composition.h"


	namespace ytpking
	{
	namespace gst
	{


Pipeline::Pipeline( wxWindow *drawWindow ) :
	m_pipeline( gst_pipeline_new( "pipeline" ) )
{
	// connect to the x-window callback
	GstBus *bus = gst_element_get_bus( m_pipeline );
	gst_bus_enable_sync_message_emission( bus );
	gst_bus_add_signal_watch( bus );

	g_signal_connect( bus, "message", (GCallback)onMessage, this );
	g_signal_connect( bus, "sync-message::element", (GCallback)onSync, drawWindow );
}


void
Pipeline::play( void )
{
	gst_element_set_state( m_pipeline, GST_STATE_PLAYING );
}


void
Pipeline::stop( void )
{
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
Pipeline::onSync( GstBus *bus, GstMessage *message, gpointer data )
{
	const GstStructure *structure = gst_message_get_structure( message );
	const char *structureName = gst_structure_get_name( structure );

	g_print( "Called '%s'\n", structureName );
	
	wxWindow *window = (wxWindow *)data;

	if ( strcmp( structureName, "prepare-xwindow-id" ) == 0 )
	{
		GstObject *imagesink = GST_MESSAGE_SRC( message );
		g_object_set( imagesink, "force-aspect-ratio", true, NULL );
		gst_x_overlay_set_xwindow_id( GST_X_OVERLAY( imagesink ), (gulong)window->GetHWND() );
	}
}


	} }