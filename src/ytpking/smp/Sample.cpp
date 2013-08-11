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

#include "gst/gnl/PreviewTapes.h"
#include "gst/gnl/FileSource.h"


	namespace ytpking
	{
	namespace smp
	{


Sample::Sample( const char *filename )  :
	m_filename( filename ),
	m_start( 0u ),
	m_duration( 5u )
{
}


void
Sample::addToPreviewTapes( gst::gnl::FileSource *& audioSource, gst::gnl::FileSource *& videoSource ) const
{
	using namespace gst::gnl;
	
	previewTapes.addSource( audioSource, videoSource );

	audioSource->setFilename( m_filename.c_str() );
	audioSource->setStart( m_start );
	audioSource->setDuration( m_duration );

	videoSource->setFilename( m_filename.c_str() );
	videoSource->setStart( m_start );
	videoSource->setDuration( m_duration );


	previewTapes.update();
}


	} }