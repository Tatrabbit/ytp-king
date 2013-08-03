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
#include "GstreamerThread.h"

#include <glib.h>
#include <wx/log.h>


	namespace ytpking
	{
	namespace gst
	{


GstreamerThread::GstreamerThread( void )
{
	GThread *thread = g_thread_new( "gst-main_loop", (GThreadFunc)mainLoop, NULL );

	if ( thread != NULL )
		g_thread_unref( thread ); // It's fine, the thread keeps a ref of itself.
	else
		wxLogError( "Couldn't create GStreamer loop thread.\n" );
}


void
GstreamerThread::mainLoop( gpointer )
{
	GMainLoop *loop = g_main_loop_new( NULL, FALSE );

	g_main_loop_run( loop );

	g_main_loop_unref( loop );
}


	} }