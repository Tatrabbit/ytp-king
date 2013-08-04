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
#include "FileSource.h"

#include <gst/gst.h>


	namespace ytpking
	{
	namespace gst
	{

class Composition;

	namespace gnl
	{


FileSource::FileSource( void ) :
	m_start( 0i64 ),
	m_duration( 1i64 ),
	m_speed( 1.0f ),
	m_element( gst_element_factory_make( "gnlfilesource", NULL ) )
{
}


FileSource::~FileSource( void )
{
	gst_object_unref( m_element) ;
}

void
FileSource::setFilename( const char *filename )
{
	g_object_set( m_element, "uri", filename, NULL );
}


void
FileSource::setStart( __int64 startTime )
{
	g_object_set( m_element, "media-start", (m_start = startTime) * GST_SECOND, NULL );
}


void
FileSource::setDuration( __int64 duration )
{
	g_object_set( m_element, "duration", (m_duration = duration) * GST_SECOND, NULL );
}


void
FileSource::setSpeed( float speed )
{
	m_speed = speed;
}


	} } }