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
#include "PreviewUser.h"

#include "../Pipeline.h"

#include "AudioTapeComposition.h"
#include "VideoTapeComposition.h"

	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{

TapeComposition *PreviewUser::m_audioPreviewComposition( NULL );
TapeComposition *PreviewUser::m_videoPreviewComposition( NULL );


void
PreviewUser::initialize( Pipeline *pipeline )
{
	m_audioPreviewComposition = new AudioTapeComposition;
	m_videoPreviewComposition = new VideoTapeComposition;

	m_audioPreviewComposition->addTo( *pipeline );
	m_videoPreviewComposition->addTo( *pipeline );
}


void
PreviewUser::cleanup( void )
{
	delete m_audioPreviewComposition;
	delete m_videoPreviewComposition;
}




	} } }