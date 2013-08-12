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
#include "SampleInstance.h"

#include "gst/gnl/PreviewTapes.h"
#include "gst/gnl/TapeComposition.h"
#include "smp/Sample.h"

	namespace ytpking
	{
	namespace smp
	{


unsigned int SampleInstance::m_nInstances( 0u );



SampleInstance::SampleInstance( const Sample *sample ) :
	m_sample( sample ),
	m_id( m_nInstances++ ),
	m_isConnected( false )
{
}


SampleInstance::~SampleInstance( void )
{
	gst::gnl::previewTapes.getAudio().removeSampleInstance( *this );
	gst::gnl::previewTapes.getVideo().removeSampleInstance( *this );
}


const Sample
&SampleInstance::getSample( void ) const
{
	return *m_sample;
}


void
SampleInstance::connectToPreview( void  )
{
	gst::gnl::previewTapes.getAudio().addSampleInstance( *this );
	gst::gnl::previewTapes.getVideo().addSampleInstance( *this );
}


	} }