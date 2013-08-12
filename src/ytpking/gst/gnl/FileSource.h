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
#ifndef __YTPKING_GST_GNL_FileSource_h
#define __YTPKING_GST_GNL_FileSource_h

#include <gst/gst.h>


	namespace ytpking
	{
	namespace gst
	{

class Composition;

	namespace gnl
	{


class FileSource
{
friend class TapeComposition;

	// Only a Composition class may construct me.
	FileSource( void );
	~FileSource( void );

	explicit FileSource( FileSource & );
	void operator=( FileSource & );

	void
		setFilename( const char *filename );

	void
		setStart( gint64 startTime );

	void
		setDuration( gint64 duration );


	gint64 m_duration;


	GstElement *m_element;

};


	} } }


#endif
