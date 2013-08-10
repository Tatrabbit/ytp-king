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
#ifndef __YTPKING_GST_GNL_Composition_h
#define __YTPKING_GST_GNL_Composition_h


#include <string>
#include <list>


typedef struct  _GstElement   GstElement;
typedef struct  _GstPad       GstPad;


	namespace ytpking
	{
	namespace gst
	{

class Pipeline;

	namespace gnl
	{

class FileSource;


class Composition
{
public:
	Composition( void );
	virtual ~Composition( void );
private:
	explicit Composition( Composition & );
	void operator=( Composition & );

public:

	virtual void
		addTo( Pipeline &pipeline ) = 0;

	FileSource
		*addSource( void );

	void
		deleteSource( const FileSource *source );

	void
		update( void );


protected:

	GstElement *m_selfElement;

	static void
		onPadAdded (GstElement *src, GstPad *new_pad, GstElement *sink);

private:

	typedef std::list<FileSource *> FileSourceList;
	FileSourceList m_sources;

};

	} } }

#endif