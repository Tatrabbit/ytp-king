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

#include "Sample.h"
#include "SampleInstance.h"


	namespace ytpking
	{
	namespace smp
	{


Tape::Tape( const char *name, TapesDataFile::NodeReference &nodeReference ) :
	m_name( name ),
	m_nodeReference( nodeReference ),
	m_isConnected( false )
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

	if ( m_isConnected )
	{
		sampleInstance->connectToPreview();
		gst::gnl::previewTapes.update();
	}

	//if ( !suppressSave )
	//	ytpking::tapesDataFile->addSample( sample.getGuid(), m_nodeReference );

	return sampleInstance;
}


void
Tape::deleteSample( const SampleInstance &sampleInstance )
{
	int i = 0;
	for ( InstanceSet::const_iterator it = m_samples.begin(); it != m_samples.end(); ++it )
	{
		if ( **it == sampleInstance )
		{
			//ytpking::tapesDataFile->deleteElement( i, m_nodeReference );
			delete *it;
			m_samples.erase( it );
			return;
		};
		++i;
	}
}


void
Tape::connectToPreview( void )
{
	gst::gnl::previewTapes.disconnectTape();

	for ( InstanceSet::const_iterator it = m_samples.begin(); it != m_samples.end(); ++it )
		(*it)->connectToPreview();

	m_isConnected = true;
	
	gst::gnl::previewTapes.m_connectedTape = this;
	gst::gnl::previewTapes.update();
}


const char
*Tape::getName( void ) const
{
	return m_name.c_str();
}


void
Tape::setName( const char *newName )
{
	//ytpking::tapesDataFile->renameTape( (m_name = newName).c_str(), m_nodeReference );
}


	} }