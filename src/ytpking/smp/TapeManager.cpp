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

#include "TapesDataFile.h"

#include "Tape.h"
#include "TapeUser.h"


	namespace ytpking
	{
	namespace smp
	{



TapeManager::TapeManager( void ) :
	m_selectedTape( NULL )
{
}


TapeManager::~TapeManager( void )
{
	for ( TapeSet::const_iterator it = m_tapes.begin(); it != m_tapes.end(); ++it )
		delete *it;

	if ( ytpking::tapesDataFile != NULL )
		delete ytpking::tapesDataFile;
}

void
TapeManager::initialize( void )
{
	assert( ytpking::tapesDataFile == NULL );
	ytpking::tapesDataFile = new TapesDataFile( this );
	ytpking::tapesDataFile->loadAll();
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
	TapesDataFile::NodeReference nodeReference = ytpking::tapesDataFile->addTape( "Your Omnipotence" );
	Tape *tape = new Tape( nodeReference );

	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onAddTape( *tape );


	return tape;
}


void
TapeManager::deleteTape( Tape *tape )
{
	TapeSet::const_iterator tapeIt = m_tapes.find( tape );

	if ( tapeIt != m_tapes.end() )
	{
		for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
			(*it)->onDeleteTape( *tape );

		ytpking::tapesDataFile->deleteTape( tape->getNodeReference() );
		delete tape;
		m_tapes.erase( *tapeIt );
	}
}


	} }