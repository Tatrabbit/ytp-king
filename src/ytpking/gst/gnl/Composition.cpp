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
#include "Composition.h"

#include <sstream>

#include <gst/gst.h>

#include "../Pipeline.h"
#include "FileSource.h"


	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{


Composition::Composition( void ) :
	m_selfElement( gst_element_factory_make( "gnlcomposition", NULL ) )
{
}


Composition::~Composition( void )
{
	// even if it's never added to something, I should have dibs on its refcount so I can
	// delete it.
	gst_object_unref( m_selfElement );

	for ( FileSourceList::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
		delete *it;
}


void
Composition::onPadAdded( GstElement *src, GstPad *new_pad, GstElement *sink )
{
  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  GstPad *compatiblePad = gst_element_get_compatible_pad( sink, new_pad, gst_pad_get_caps( new_pad ) );

	if ( compatiblePad )
	{
		if ( gst_pad_link( new_pad, compatiblePad ) == GST_PAD_LINK_OK )
			g_print("  Link succeeded.\n" );
		else
			g_print( "Link to '%s' from '%s' Failed.\n", GST_PAD_NAME (compatiblePad), GST_ELEMENT_NAME (sink) );
	}
	else
		g_print( "Skipping incompatible pad.\n" );
}


FileSource
*Composition::addSource( void )
{
	FileSource *source = new FileSource;

	m_sources.push_back( source );

	if ( !gst_bin_add( GST_BIN( m_selfElement ), source->m_element ) )
	{
		delete source;
		return NULL;
	}
	else
		return source;
}


void
Composition::deleteSource( FileSource *source )
{
	for ( FileSourceList::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
		if ( source == *it )
		{
			delete *it;
			break;
		}
}


void
Composition::update( void )
{
	__int64 mediaStart = 0i64;

	for ( FileSourceList::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
	{
		g_object_set( (*it)->m_element, "media-start", mediaStart * GST_SECOND, NULL );
		g_object_set( (*it)->m_element, "media-duration", (*it)->m_duration * GST_SECOND, NULL );

		mediaStart += (*it)->m_duration;
	}
}


	} } }