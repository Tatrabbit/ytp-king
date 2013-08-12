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
#ifndef __YTPKING_GST_GNL_TapeComposition_h
#define __YTPKING_GST_GNL_TapeComposition_h


#include <string>
#include <list>


typedef struct  _GstElement   GstElement;
typedef struct  _GstPad       GstPad;


	namespace ytpking
	{

namespace smp {
	class Tape;
	class Sample;
}

	namespace gst
	{

class Pipeline;

	namespace gnl
	{

class FileSource;


class TapeComposition
{
public:
	TapeComposition( void );
	virtual ~TapeComposition( void );
private:
	explicit TapeComposition( TapeComposition & );
	void operator=( TapeComposition & );

public:

	smp::Tape *m_connectedTape;

	virtual void
		addTo( Pipeline &pipeline ) = 0;

	// TODO removeFrom( Pipeline )

	/** Adds a new source to this TapeComposition.
	\return The newly created source. */
	FileSource
		*addSource( const smp::Sample &sample );

	/** Deletes the Filesource from this composition.
	\param source The source to delete. */
	void
		deleteSource( const FileSource *source );

	void
		disconnectTape( smp::Tape *newTape = NULL );

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