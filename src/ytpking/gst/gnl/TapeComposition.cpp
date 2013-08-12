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

#include <cassert>
#include <sstream>

#include <gst/gst.h>

#include "gst/Pipeline.h"

#include "smp/TapeManager.h"
#include "smp/Tape.h"
#include "smp/Sample.h"
#include "smp/SampleInstance.h"

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
	for ( SampleInstanceList::const_iterator it = m_samples.begin(); it != m_samples.end(); ++it )
		delete it->second;
}


void
TapeComposition::onPadAdded( GstElement *src, GstPad *new_pad, GstElement *sink )
{
	GstPad *compatiblePad = gst_element_get_compatible_pad( sink, new_pad, gst_pad_get_caps( new_pad ) );

	if ( compatiblePad )
		gst_pad_link( new_pad, compatiblePad );
}


void
TapeComposition::addSampleInstance( const smp::SampleInstance &sampleInstance )
{
	// don't create anther if it exists.
#ifndef NDEBUG
	for ( SampleInstanceList::const_iterator it = m_samples.begin(); it != m_samples.end(); ++ it )
		assert( &sampleInstance != it->first );
#endif


	// Create a Filesource
	FileSource *source = new FileSource;

	if ( !gst_bin_add( GST_BIN( m_selfElement ), source->m_element ) )
	{
		// If there was an error, clean up safely
		delete source;
	}
	else
	{
		const smp::Sample *sample = &sampleInstance.getSample();

		// TODO not needed; do this in update()
		source->setFilename( sample->m_filename.c_str() );
		source->setStart( sample->m_start );
		source->setDuration( sample->m_duration );

		// Keep a pointer
		m_samples.push_back( SampleInstancePair( &sampleInstance, source ) );
	}
}


void
TapeComposition::removeSampleInstance( const smp::SampleInstance &sampleInstance )
{
	for ( SampleInstanceList::const_iterator it = m_samples.begin(); it != m_samples.end(); ++ it )
	{
		if ( &sampleInstance == it->first )
		{
			// TODO remove in destructor
			gst_bin_remove( GST_BIN( m_selfElement ), it->second->m_element );

			delete it->second;
			m_samples.erase( it );

			break;
		}
	}
}


void
TapeComposition::disconnectTape( void )
{
	for ( SampleInstanceList::const_iterator it = m_samples.begin(); it != m_samples.end(); ++ it )
	{
		gst_bin_remove( GST_BIN( m_selfElement ), it->second->m_element );
		delete it->second;
	}

	m_samples.clear();
}


void
TapeComposition::update( void )
{
	gint64 start = G_GINT64_CONSTANT( 0 );

	for ( SampleInstanceList::const_iterator it = m_samples.begin(); it != m_samples.end(); ++ it )
	{
		FileSource *source = it->second;

		g_object_set( source->m_element, "start", start * GST_SECOND, NULL );

		// TODO account for speed
		g_object_set( source->m_element, "media-duration", source->m_duration * GST_SECOND, NULL );

		start += source->m_duration;
	}
}


	} } }