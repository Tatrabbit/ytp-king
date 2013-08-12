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
#include "Tape.h"

#include "gst/gnl/TapeComposition.h"
#include "gst/gnl/PreviewTapes.h"

#include "SampleInstance.h"


	namespace ytpking
	{
	namespace smp
	{


Tape::Tape( void )
{
}


Tape::~Tape( void )
{
	for ( InstanceSet::const_iterator it = m_samples.begin(); it != m_samples.end(); ++it )
		delete *it;
}


const Tape::InstanceSet
&Tape::getInstances( void ) const
{
	return m_samples;
}


SampleInstance
*Tape::appendSample( const Sample &sample )
{
	SampleInstance *sampleInstance = new SampleInstance( &sample );
	m_samples.push_back( sampleInstance );

	sampleInstance->connectToPreview();

	gst::gnl::previewTapes.update();

	return sampleInstance;
}


void
Tape::deleteSample( const SampleInstance &sampleInstance )
{
	for ( InstanceSet::const_iterator it = m_samples.begin(); it != m_samples.end(); ++it )
		if ( **it == sampleInstance )
		{
			delete *it;
			m_samples.erase( it );
			return;
		};
}


void
Tape::connectToPreview( void )
{
	gst::gnl::previewTapes.disconnectTape();

	for ( InstanceSet::const_iterator it = m_samples.begin(); it != m_samples.end(); ++it )
		(*it)->connectToPreview();

	gst::gnl::previewTapes.update();
}


	} }