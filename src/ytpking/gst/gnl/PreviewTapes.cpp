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
#define __YTPKING_GST_GNL_PreviewTapes_cpp
#include "PreviewTapes.h"

#include <cassert>

#include "AudioTapeComposition.h"
#include "VideoTapeComposition.h"


	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{


PreviewTapes::PreviewTapes( void ) :
	m_audioComposition( NULL ),
	m_videoComposition( NULL )
{
}


PreviewTapes::~PreviewTapes( void )
{
	if ( m_audioComposition != NULL )
	{
		assert( m_videoComposition != NULL );

		delete m_audioComposition;
		delete m_videoComposition;
	}
}


void
PreviewTapes::initialize( void )
{
	assert( m_audioComposition == NULL );
	assert( m_videoComposition == NULL );

	m_audioComposition = new AudioTapeComposition;
	m_videoComposition = new VideoTapeComposition;
}


void
PreviewTapes::connectToPipeline( Pipeline &pipeline )
{
	assert( m_audioComposition != NULL );
	assert( m_videoComposition != NULL );

	m_audioComposition->addTo( pipeline );
	m_videoComposition->addTo( pipeline );

	PipelineContent::connectToPipeline( pipeline );
}


void
PreviewTapes::disconnectFromPipeline( void )
{
	// TODO

	PipelineContent::disconnectFromPipeline();
}


void
PreviewTapes::update( void )
{
	assert( m_audioComposition != NULL );
	assert( m_videoComposition != NULL );

	m_audioComposition->update();
	m_videoComposition->update();
}


void
PreviewTapes::disconnectTape( void ) const
{
	m_audioComposition->disconnectTape();
	m_videoComposition->disconnectTape();
}


	} } }