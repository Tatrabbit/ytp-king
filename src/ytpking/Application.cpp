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
#include "ytpking/Application.h"

#ifdef _MSC_VER
#	define getcwd _getcwd
#else
#	define getcwd getcwd
#endif

#include <gst/gst.h>

#include "ytpking/MainWindow.h"
#include "ytpking/DataDirectory.h"


	namespace ytpking
	{


Application::Application( void )
{
	if ( !getcwd( m_currentDirectory, sizeof( m_currentDirectory ) ) )
		m_currentDirectory[0] = '\0';

	FILE *result = freopen( "ErrorLog.txt", "w", stderr );
	freopen( "Log.txt", "w", stdout );

	if ( result )
	{
		m_logger = new wxLogStderr( stderr ); // TODO delete!
		wxLog::SetActiveTarget( m_logger );

		wxLogMessage( "Program Started." );
	}
	// TODO the log message won't store in Program Files, use appdata folder.
	//else
		//wxSafeShowMessage( "Error", "Could not open the wxWidgets log file." );
}


bool
Application::OnInit( void )
{
	if ( ytpking::dataDirectory.getHasError() )
		return false;

	// Initialize GStreamer
	gst_debug_set_default_threshold( GST_LEVEL_WARNING );
	gst_init( NULL, NULL );

	MainWindow *frame = new MainWindow();

	frame->Show( true );
	SetTopWindow( frame );

	return true;
}


	}