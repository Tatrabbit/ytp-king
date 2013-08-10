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
#define YTPKING_GST_GNL_SampleManager_cpp
#include "SampleManager.h"

#include "smp/Sample.h"
#include "SampleUser.h"


	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{


SampleManager::
SamplePair::SamplePair( Sample *sample ) :
	m_sample( sample )
{
}


SampleManager::
SamplePair::SamplePair( Sample *sample, const SamplesDataFile::NodeReference &nodeReference ) :
	m_sample( sample ),
	m_nodeReference( nodeReference )
{
}


SampleManager::SampleManager( void ) :
	m_samplesDataFile( NULL ),
	m_selectedSample( NULL )
{
}


SampleManager::~SampleManager( void )
{
	if ( m_samplesDataFile )
		delete m_samplesDataFile;
}


void
SampleManager::initialize( void )
{
	assert( m_samplesDataFile == NULL );
	m_samplesDataFile = new SamplesDataFile( this );

	m_samplesDataFile->loadAll();
}


void
SampleManager::registerSampleUser( SampleUser *sampleUser )
{
	m_sampleUsers.insert( sampleUser );
}


void
SampleManager::unregisterSampleUser( SampleUser *sampleUser )
{
	m_sampleUsers.erase( sampleUser );
}


/** Get the currently active sample. */
Sample
*SampleManager::getSelectedSample( void ) const
{
	return m_selectedSample;
}


/** Set the currently active sample. */
void
SampleManager::selectSample( Sample *sample )
{
	m_selectedSample = sample;

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onSelectSample( sample );
}


Sample
*SampleManager::addSample( const char *filename, const char *name, const char *speakerName,
                           SamplesDataFile::NodeReference *nodeReferencePtr )
{
	Sample *sample = new Sample( filename );

	SamplesDataFile::NodeReference nodeReference;
	if ( nodeReferencePtr != NULL )
		nodeReference = *nodeReferencePtr;
	else
		nodeReference = m_samplesDataFile->addSample( name, speakerName );

	SamplePair pair( sample, nodeReference );

	m_samples.insert( pair );

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onAddSample( name, speakerName, sample );

	return sample;
}


void
SampleManager::deleteSample( Sample *sample )
{
	if ( sample == NULL )
		sample = m_selectedSample;

	m_samples.erase( sample );

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onDeleteSample( sample );

	delete sample;
}


void
SampleManager::renameSample( Sample *sample, const char *name )
{
	// I don't know if I'm doing this the right way, perhaps not, but
	// I couldn't find out how to assign to it->m_name, it was treated by MSVC as a const std::string.
	SampleSet::iterator it = m_samples.find( sample );

	if ( it != m_samples.end() )
	{
		SamplePair newSamplePair( sample, it->m_nodeReference );

		m_samplesDataFile->renameSample( name, newSamplePair.m_nodeReference );

		m_samples.erase( it );
		m_samples.insert( newSamplePair );
	}

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onRenameSample( name, sample );
}


void
SampleManager::changeSpeaker( Sample *sample, const char *speakerName )
{
	// I don't know if I'm doing this the right way, perhaps not, but
	// I couldn't find out how to assign to it->m_name, it was treated by MSVC as a const std::string.
	SampleSet::iterator it = m_samples.find( sample );

	if ( it != m_samples.end() )
	{
		SamplePair newSamplePair( sample, it->m_nodeReference );

		m_samplesDataFile->changeSampleSpeaker( speakerName, newSamplePair.m_nodeReference );

		m_samples.erase( it );
		m_samples.insert( newSamplePair );
	}

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onChangeSampleSpeaker( speakerName, sample );
}


	} } }