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
#include "ytpking/DataFile.h"

#include <wx/log.h>

#ifdef _MSC_VER
#	include <ShlObj.h>
#endif

#include "utf8.h"


	namespace ytpking
	{


std::string  DataFile::m_savedataPath;
bool         DataFile::m_hasSavedataPath( false );


bool
DataFile::initialize( void )
{
// TODO for other platforms/compilers
#ifdef _MSC_VER
	TCHAR charPath[MAX_PATH];

	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_COMMON_APPDATA, NULL, 0, charPath ) ) )
	{
		m_hasSavedataPath = true;

		std::wstring wPath;
		wPath = charPath;

		wPath += L"\\rainChu";

		if ( !CreateDirectory( wPath.c_str(), NULL ) )
		{
			if ( GetLastError() != ERROR_ALREADY_EXISTS )
			{
				wxLogError( "Coulnd't create the save directory. Please file a bug report." );
				return m_hasSavedataPath = false;
			}
		}

		wPath += L"\\YTP King";
		
		if ( !CreateDirectory( wPath.c_str(), NULL ) )
		{
			if ( GetLastError() != ERROR_ALREADY_EXISTS )
			{
				wxLogError( "Coulnd't create the save directory. Please file a bug report." );
				return m_hasSavedataPath = false;
			}
		}

		utf8::utf32to8( wPath.begin(), wPath.end(), std::back_inserter( m_savedataPath ) );
		return true;
	}
	else
	{
		wxLogError( "Coulnd't locate your appdata folder. Please file a bug report." );
		return false;
	}
#endif
}


const char
*DataFile::getSaveDataPath( void )
{
	return m_hasSavedataPath? m_savedataPath.c_str() : NULL;
}


	}