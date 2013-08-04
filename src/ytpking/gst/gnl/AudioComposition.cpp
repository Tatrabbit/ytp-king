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
#include "AudioComposition.h"

#include <gst/gst.h>

#include "../Pipeline.h"


	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{


AudioComposition::AudioComposition( void ) :
	//m_queueElement( gst_element_factory_make( "queue",         NULL ) ),
	m_sinkElement ( gst_element_factory_make( "autoaudiosink", NULL ) )
{
	//if ( !gst_element_link( m_queueElement, m_sinkElement ) )
		//GST_ERROR( "Audio Queue/Sink could not be linked.\n" );

	g_signal_connect( m_selfElement, "pad-added", G_CALLBACK( onPadAdded ), m_sinkElement );

	g_object_set( m_selfElement, "caps", gst_caps_from_string( "audio/x-raw-int;audio/x-raw-float" ), NULL ); 
}


void
AudioComposition::addTo( Pipeline &pipeline )
{
	gst_bin_add_many( GST_BIN( *pipeline ), m_selfElement, m_sinkElement, NULL );
}


	} } }