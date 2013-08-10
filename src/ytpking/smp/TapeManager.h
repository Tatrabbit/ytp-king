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
#ifndef YTPKING_SMP_TapeManager_h
#define YTPKING_SMP_TapeManager_h


#include <set>


	namespace ytpking
	{
	namespace smp
	{

class Tape;
class TapeUser;

class TapeManager
{
public:
	TapeManager( void );
	~TapeManager( void );
private:
	explicit TapeManager( TapeManager & );
	void operator==( TapeManager & );
public:

	void
		initialize( void );

	
	/** Register a TapeUsr with this class.
	    Callbacks on this TapeUser will then be called.
	\param  tapeUser the SampleUser instance to be registered. */
	void
		registerTapeUser( TapeUser *tapeUser );

	/** Removes a TapeUser from this object.
	    This is done by the TapeUser's destructor, so this normally shouldn't need
		to be called.
	\param tapeUser The SampleUser to unregister. */
	void
		unregisterTapeUser( TapeUser *tapeUser );


	/** Get the currently active tape. */
	Tape
		*getSelectedTape( void ) const;

	/** Set the currently active tape. */
	void
		selectTape( Tape *tape );


	/** Adds a new Tape.
	    TapeUser::onAdd will be called.
	\param filename The filename of the sample.
	\param name     The name of the sample, such as "What's for dinner"
	\param speakerName The name of the speaker, e.g. The King
	\param nodeReference If NULL, the speaker will be created in the save DataFile. */
	Tape
		*addTape( void );

	/** Deletes a Tape, freeing the memeory.
	    Once freed, all remaining pointers will dangle, be sure that any
		class using them has SampleUser::onDelete defined to do so.
	\param sample The sample to delete. */
	void
		deleteTape( Tape *tape );

private:

	typedef std::set<Tape *>     TapeSet;
	typedef std::set<TapeUser *> TapeUserSet;

	Tape    *m_selectedTape;
	TapeSet  m_tapes;

	TapeUserSet m_tapeUsers;

};


#ifdef YTPKING_SMP_TapeManager_cpp
	TapeManager tapeManager;
#else
	extern TapeManager tapeManager;
#endif


	} }


#endif