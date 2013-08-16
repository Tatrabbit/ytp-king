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
#define YTPKING_GST_GNL_SampleManager_cpp
#include "SampleManager.h"

#include "Sample.h"
#include "SampleUser.h"


	namespace ytpking
	{
	namespace smp
	{


SampleManager::SampleManager( void ) :
	m_selectedSample( NULL )
{
}


SampleManager::~SampleManager( void )
{
	for ( SampleMap::const_iterator it = m_samples.begin(); it != m_samples.end(); ++it )
		delete it->second;
}


void
SampleManager::loadAll( void )
{
	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onLoadAllSamples();
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
smp::Sample
*SampleManager::getSelectedSample( void ) const
{
	return m_selectedSample;
}


/** Set the currently active sample. */
void
SampleManager::selectSample( smp::Sample *sample )
{
	m_selectedSample = sample;

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onSelectSample( sample );
}


smp::Sample
*SampleManager::addSample( const char *filename, const char *name, const char *speakerName,
                           const char *guid,
                           SamplesDataFile::NodeReference *nodeReferencePtr )
{
	smp::Sample *sample = new smp::Sample( name, filename, guid );

	if ( nodeReferencePtr != NULL )
		sample->m_nodeReference = *nodeReferencePtr;

	m_samples[sample->getGuid()] = sample;

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onAddSample( name, speakerName, sample );

	return sample;
}


void
SampleManager::deleteSample( smp::Sample *sample )
{
	// Defaults to the selected sample
	if ( sample == NULL )
		sample = m_selectedSample;

	// Callbacks before deletion.
	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onDeleteSample( sample );

	// Erase from Map
	SampleMap::const_iterator it = m_samples.find( sample->getGuid() );
	assert( it != m_samples.end() );
	m_samples.erase( it );

	// Finally, delete.
	delete sample;
}


void
SampleManager::renameSample( smp::Sample *sample, const char *name )
{
	SampleMap::iterator it = m_samples.find( sample->getGuid() );

	assert ( it != m_samples.end() );

	it->second->m_name = name;

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onRenameSample( name, sample );
}


void
SampleManager::changeSpeaker( smp::Sample *sample, const char *speakerName )
{
#ifndef NDEBUG
	SampleMap::const_iterator it = m_samples.find( sample->getGuid() );
	assert( it != m_samples.end() );
#endif

	for ( SampleUserSet::const_iterator it = m_sampleUsers.begin(); it != m_sampleUsers.end(); ++it )
		(*it)->onChangeSampleSpeaker( speakerName, sample );
}


void
SampleManager::saveSample( Sample *sample )
{
	SampleMap::const_iterator it = m_samples.find( sample->getGuid() );

	if ( it != m_samples.end() )
	{
		//SamplePair newSamplePair( sample, it->m_nodeReference );

		int start, duration, end;
		start    = it->second->m_start;
		duration = it->second->m_duration;
		end      = start + duration;
		
		//m_samplesDataFile->setSampleStart( start, newSamplePair.m_nodeReference );
		//m_samplesDataFile->setSampleEnd( end, newSamplePair.m_nodeReference );
		//m_samplesDataFile->saveToFile();
	}
}


Sample
*SampleManager::getSampleByGuid( const char *guid ) const
{
	SampleMap::const_iterator it = m_samples.find( guid );
	return it != m_samples.end()? it->second : NULL;
}


	} }