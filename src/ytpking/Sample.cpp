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
#include "ytpking/Sample.h"

#include "gst/gnl/Composition.h"
#include "gst/gnl/FileSource.h"

	namespace ytpking
	{


Sample::Sample( const char *filename )  :
	m_filename( filename ),
	m_start( 0u ),
	m_duration( 5u )
{
}


const gst::gnl::FileSource
*Sample::addToComposition( gst::gnl::Composition *composition ) const
{
	using gst::gnl::FileSource;
	
	FileSource *source = composition->addSource();

	source->setFilename( m_filename.c_str() );
	source->setStart( m_start );
	source->setDuration( m_duration );

	composition->update();

	return source;
}


	}