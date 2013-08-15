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
#ifndef __YTPKING_DataDirectory_h
#define __YTPKING_DataDirectory_h

#include <string>

	namespace ytpking
	{


class DataDirectory
{
public:

	DataDirectory( void );

	/** Returns true if a fatal error prevented the path from being retrieved. */
	bool
		getHasError( void ) const;

	/** Gets the path in the user's home directory to save data to.
	/return the path usually, but empty string if something fatal happened during setup. */
	const char
		*getSaveDataPath( void ) const;

private:

	std::string m_savedataPath;

};


#ifdef __YTPKING_DataDirectory_cpp
	DataDirectory dataDirectory;
#else
	extern DataDirectory dataDirectory;
#endif


	}


#endif