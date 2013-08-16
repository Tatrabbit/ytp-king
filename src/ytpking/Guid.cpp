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

#include "Guid.h"

#include <cassert>

#ifdef _MSC_VER
#include "Objbase.h"
#endif

#include "utf8.h"


	namespace ytpking
	{


Guid::Guid( void )
{
#ifdef _MSC_VER
	OLECHAR guidStringPtr[40];
	GUID guid;
	CoCreateGuid( &guid );

#	ifndef NDEBUG
	int charSize =
#	endif
		
	StringFromGUID2( guid, guidStringPtr, 40 );

	assert( charSize > 0 );

	std::wstring wideString = guidStringPtr;

	utf8::utf16to8( wideString.begin(), wideString.end(), std::back_inserter( m_string ) );
#endif
}


Guid::Guid( const char *guid ) :
	m_string( guid )
{
}


	}