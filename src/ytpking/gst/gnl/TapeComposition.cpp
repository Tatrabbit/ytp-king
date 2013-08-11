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
#include "TapeComposition.h"

#include <sstream>

#include <gst/gst.h>

#include "gst/Pipeline.h"

#include "smp/TapeManager.h"
#include "smp/Tape.h"

#include "FileSource.h"

	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{


TapeComposition::TapeComposition( void ) :
	m_selfElement( gst_element_factory_make( "gnlcomposition", NULL ) ),
	m_connectedTape( NULL )
{
}


TapeComposition::~TapeComposition( void )
{
	for ( FileSourceList::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
		delete *it;
}


void
TapeComposition::onPadAdded( GstElement *src, GstPad *new_pad, GstElement *sink )
{
	GstPad *compatiblePad = gst_element_get_compatible_pad( sink, new_pad, gst_pad_get_caps( new_pad ) );

	if ( compatiblePad )
		gst_pad_link( new_pad, compatiblePad );
}


FileSource
*TapeComposition::addSource( void )
{
	FileSource *source = new FileSource;

	if ( !gst_bin_add( GST_BIN( m_selfElement ), source->m_element ) )
	{
		delete source;
		return NULL;
	}
	else
	{
		m_sources.push_back( source );
		return source;
	}
}


void
TapeComposition::deleteSource( const FileSource *source )
{
	for ( FileSourceList::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
		if ( source == *it )
		{
			gst_bin_remove( GST_BIN( m_selfElement ), source->m_element );

			delete *it;
			m_sources.erase( it );
			break;
		}
}


void
TapeComposition::disconnectTape( smp::Tape *newTape )
{
	if ( m_connectedTape != NULL )
		m_connectedTape->disconnectFromComposition();

	m_connectedTape = newTape;

	for ( FileSourceList::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
	{
		gst_bin_remove( GST_BIN( m_selfElement ), (*it)->m_element );
		delete *it;
	}

	m_sources.clear();
}


void
TapeComposition::update( void )
{
	__int64 start = 0i64;

	for ( FileSourceList::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
	{
		g_object_set( (*it)->m_element, "start", start * GST_SECOND, NULL );

		// TODO account for (*it)->m_speed
		g_object_set( (*it)->m_element, "media-duration", (*it)->m_duration * GST_SECOND, NULL );

		start += (*it)->m_duration;
	}
}


	} } }