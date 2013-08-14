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
#include <wx/log.h>

#include "gst/PipelineContent.h"
#include "gnl/TapeComposition.h"


	namespace ytpking
	{
	namespace gst
	{


Pipeline::Pipeline( void ) :
	m_pipeline( NULL ),
	m_hasSetRenderWindow( false ),
	m_content( NULL )
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
	changePipelineState( GST_STATE_PLAYING );
}


void
Pipeline::stop( void )
{
	changePipelineState( GST_STATE_NULL );
}

void
Pipeline::pause( void )
{
	changePipelineState( GST_STATE_PAUSED );
}



void
Pipeline::seek( double position )
{
	assert( position >= 0.0 && position <= 1.0 );

	if ( m_content == NULL )
		return;

	GstState currentState = GST_STATE( m_pipeline );

	setPipelineStateSync( GST_STATE_PAUSED );

	gint64 duration;
	GstFormat format = GST_FORMAT_TIME;

	if ( !gst_element_query_duration( m_pipeline, &format, &duration ) || format != GST_FORMAT_TIME )
	{
		wxLogError( "An unknown problem occurred while trying to query the pipeline duration." );
		return;
	}

	gint64 timePosition = (long double)position * (long double)duration;
   
	GstEvent *seek_event = gst_event_new_seek( (gdouble)1.0, GST_FORMAT_TIME, (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE),
	                                           GST_SEEK_TYPE_SET, timePosition, GST_SEEK_TYPE_NONE, 0);
   
	gst_element_send_event ( m_pipeline, seek_event);

	if ( currentState != GST_STATE_NULL )
		gst_element_set_state( m_pipeline, currentState );
}


bool
Pipeline::getCurrentPosition( double &position ) const
{
	if ( m_content == NULL )
		return false;

	GstState currentState = GST_STATE( m_pipeline );

	if ( currentState == GST_STATE_NULL )
		return false;

	gint64 duration, timePosition;
	GstFormat format = GST_FORMAT_TIME;

	if ( !gst_element_query_duration( m_pipeline, &format, &duration ) || format != GST_FORMAT_TIME )
		return false;

	if ( !gst_element_query_position( m_pipeline, &format, &timePosition ) || format != GST_FORMAT_TIME )
		return false;

	position = (double)timePosition / (double)duration;
	return true;
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


void
Pipeline::registerPipelineUser( PipelineUser &pipelineUser )
{
	m_pipelineUsers.insert( &pipelineUser );
}


void
Pipeline::unregisterPipelineUser( PipelineUser &pipelineUser )
{
	m_pipelineUsers.erase( &pipelineUser );
}


bool
Pipeline::changePipelineState( GstState state )
{
	if ( m_hasSetRenderWindow && m_content != NULL )
	{
		PipelineUser::PipelineState oldState, newState;

		if ( !getPipelelineUserState( oldState ) )
			return false;

		gst_element_set_state( m_pipeline, state  );

		// Block until the state has changed.
		if ( !getPipelelineUserState( newState ) )
			return false;

		if ( oldState != newState )
			for ( UserSet::const_iterator it = m_pipelineUsers.begin(); it != m_pipelineUsers.end(); ++it )
				(*it)->onPipelineStateChange( oldState, newState );
	}

	return true;
}


bool
Pipeline::getPipelelineUserState( PipelineUser::PipelineState &state ) const
{
	GstState gstState;

	if ( gst_element_get_state( m_pipeline, &gstState, NULL, GST_CLOCK_TIME_NONE ) != GST_STATE_CHANGE_FAILURE )
	{
		switch ( gstState )
		{
		case GST_STATE_VOID_PENDING:
		case GST_STATE_NULL:
			state = PipelineUser::Stopped;
			break;
		case GST_STATE_READY:
		case GST_STATE_PAUSED:
			state = PipelineUser::Paused;
			break;
		case GST_STATE_PLAYING:
			state = PipelineUser::Playing;
		}

		return true;
	}
	else
		return false;
}


bool
Pipeline::setPipelineStateSync( GstState state )
{
	switch ( gst_element_set_state( m_pipeline, GST_STATE_PAUSED ) )
	{
	case GST_STATE_CHANGE_FAILURE:
	case GST_STATE_CHANGE_NO_PREROLL:
		wxLogError( "An unknown problem occurred while trying to ready the pipeline for seeking." );
		return false;
	case GST_STATE_CHANGE_ASYNC:
		if ( gst_element_get_state( m_pipeline, NULL,  NULL, G_GINT64_CONSTANT( 5 ) * GST_SECOND ) != GST_STATE_CHANGE_SUCCESS )
		{
			wxLogError( "A timeout occurred while trying to ready the pipeline for seeking." );
			return false;
		}
		//passthrough
	case GST_STATE_CHANGE_SUCCESS:
		break;
	}
	return true;
}


	} }