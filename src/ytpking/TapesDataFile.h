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
#ifndef __YTPKING_TapesDataFile_h
#define __YTPKING_TapesDataFile_h

#include "ytpking/DataFile.h"


	namespace ytpking
	{

namespace smp {
	class TapeManager;
}


class TapesDataFile :
	public DataFile
{
public:
	explicit TapesDataFile( smp::TapeManager *manager );

	class NodeReference
	{
	public:
		NodeReference( void );

	private:
		friend class TapesDataFile;

		rapidxml::xml_node<> *m_tape;
	};

	NodeReference
		addTape( const char *name );

	void
		loadAll( void )
		override;

private:

	smp::TapeManager *m_manager;

};


	}


#endif