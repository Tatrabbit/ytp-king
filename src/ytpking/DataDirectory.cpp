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
#define __YTPKING_DataDirectory_cpp
#include "DataDirectory.h"

#include <wx/log.h>

#ifdef _MSC_VER
#	include <ShlObj.h>
#endif

#include "utf8.h"


	namespace ytpking
	{


DataDirectory::DataDirectory( void )
{
// TODO for other platforms/compilers
#ifdef _MSC_VER
	TCHAR charPath[MAX_PATH];

	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0, charPath ) ) )
	{
		std::wstring wPath;
		wPath = charPath;

		wPath += L"\\rainChu";

		if ( !CreateDirectory( wPath.c_str(), NULL ) )
		{
			if ( GetLastError() != ERROR_ALREADY_EXISTS )
			{
				wxSafeShowMessage( "Error", "Coulnd't create the save directory. Please file a bug report." );
				return;
			}
		}

		wPath += L"\\YTP King";
		
		if ( !CreateDirectory( wPath.c_str(), NULL ) )
		{
			if ( GetLastError() != ERROR_ALREADY_EXISTS )
			{
				wxSafeShowMessage( "Error", "Coulnd't create the save directory. Please file a bug report." );
				abort();
			}
		}

		utf8::utf32to8( wPath.begin(), wPath.end(), std::back_inserter( m_savedataPath ) );
	}
	else
		wxSafeShowMessage( "Error", "Coulnd't locate your appdata folder. Please file a bug report." );
#endif
}


bool
DataDirectory::getHasError( void ) const
{
	return m_savedataPath.empty();
}


const char
*DataDirectory::getSaveDataPath( void ) const
{
	return m_savedataPath.c_str();
}


	}