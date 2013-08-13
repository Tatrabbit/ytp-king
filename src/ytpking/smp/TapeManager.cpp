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
#define YTPKING_SMP_TapeManager_cpp
#include "TapeManager.h"

#include "Tape.h"
#include "TapeUser.h"


	namespace ytpking
	{
	namespace smp
	{



TapeManager::TapeManager( void ) :
	m_tapesDataFile( NULL ),
	m_selectedTape( NULL )
{
}


TapeManager::~TapeManager( void )
{
	for ( TapeMap::const_iterator it = m_tapes.begin(); it != m_tapes.end(); ++it )
		delete it->first;

	if ( m_tapesDataFile )
		delete m_tapesDataFile;
}

void
TapeManager::initialize( void )
{
	assert( m_tapesDataFile == NULL );
	m_tapesDataFile = new TapesDataFile( this );
	m_tapesDataFile->loadAll();
}


void
TapeManager::registerTapeUser( TapeUser *tapeUser )
{
	m_tapeUsers.insert( tapeUser );
}


void
TapeManager::unregisterTapeUser( TapeUser *tapeUser )
{
	m_tapeUsers.erase( tapeUser );
}


Tape
*TapeManager::getSelectedTape( void ) const
{
	return m_selectedTape;
}


void
TapeManager::selectTape( Tape *tape )
{
	m_selectedTape = tape;

	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onSelectTape( tape );

	m_selectedTape->connectToPreview();
}


Tape
*TapeManager::addTape( void )
{
	Tape *tape = new Tape();
	TapesDataFile::NodeReference nodeReference = m_tapesDataFile->addTape( "Your Omnipotence" );
	m_tapes[tape ] = nodeReference;

	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onAddTape( *tape );


	return tape;
}


void
TapeManager::deleteTape( Tape *tape )
{
	TapeMap::const_iterator tapeIt = m_tapes.find( tape );

	if ( tapeIt != m_tapes.end() )
	{
		for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
			(*it)->onDeleteTape( *tape );

		delete tape;
		m_tapes.erase( tapeIt->first );
	}
}


	} }