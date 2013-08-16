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
#include "Sample.h"

#include "ytpking/Guid.h"

#include "gst/gnl/FileSource.h"
#include "gst/gnl/TapeComposition.h"


	namespace ytpking
	{
	namespace smp
	{


Sample::Sample( const char *name, const char *filename, const Guid &guid )  :
	m_name( name ),
	m_filename( filename ),
	m_guid( guid ),
	m_start( 0u ),
	m_duration( 5u )
{
}


const char
*Sample::getGuid( void ) const
{
	return m_guid;
}


const char
*Sample::getName( void ) const
{
	return m_name.c_str();
}


const char
*Sample::getFilename( void ) const
{
	return m_filename.c_str();
}


int
Sample::getStart( void ) const
{
	return m_start;
}


int
Sample::getEnd( void ) const
{
	return m_start + m_duration;
}


int
Sample::getDuration( void ) const
{
	return m_duration;
}


SamplesDataFile::NodeReference
&Sample::getNodeReference( void )
{
	return m_nodeReference;
}


	} }