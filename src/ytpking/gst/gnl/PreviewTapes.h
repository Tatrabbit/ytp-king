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
#ifndef __YTPKING_GST_GNL_PreviewTapes_h
#define __YTPKING_GST_GNL_PreviewTapes_h

#include "gst/PipelineContent.h"


	namespace ytpking
	{
	namespace gst
	{

class Pipeline;

	namespace gnl
	{


class FileSource;
class TapeComposition;


// TODO Rename to PreviewCompositions
class PreviewTapes :
	public PipelineContent
{
public:
	PreviewTapes( void );
	~PreviewTapes( void );
private:
	explicit PreviewTapes( PreviewTapes & );
	void operator=( PreviewTapes & );
public:

	void
		initialize( void );

	
	void
		connectToPipeline( Pipeline &pipeline )
		override;

	void
		disconnectFromPipeline( void )
		override;


	void
		update( void );


	// TODO don't use these, it defeats the purpose. Refactor.
	inline TapeComposition
		&getAudio( void ) const { return *m_audioComposition; }

	inline TapeComposition
		&getVideo( void ) const { return *m_videoComposition; }

private:

	TapeComposition *m_audioComposition;
	TapeComposition *m_videoComposition;

};


#ifdef __YTPKING_GST_GNL_PreviewTapes_cpp
	PreviewTapes previewTapes;
#else
	extern PreviewTapes previewTapes;
#endif


	} } }


#endif