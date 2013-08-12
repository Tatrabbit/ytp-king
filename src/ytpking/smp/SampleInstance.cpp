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

#include "gst/gnl/TapeComposition.h"
#include "smp/Sample.h"

	namespace ytpking
	{
	namespace smp
	{


unsigned int SampleInstance::m_nInstances( 0u );



SampleInstance::SampleInstance( const Sample *sample ) :
	m_sample( sample ),
	m_id( m_nInstances++ )
{
}


SampleInstance::~SampleInstance( void )
{
	for ( SourceSet::const_iterator it = m_sources.begin(); it != m_sources.end(); ++it )
		it->composition->removeSampleInstance( *this );
}


const Sample
&SampleInstance::getSample( void ) const
{
	return *m_sample;
}


void
SampleInstance::connectToComposition( gst::gnl::TapeComposition &composition )
{
	Source source;
	source.fileSource = composition.addSampleInstance( *this );
	source.composition = &composition;

	m_sources.insert( source );
}


	} }