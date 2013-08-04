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
typedef struct _GstElement GstElement;


	namespace ytpking
	{
	namespace gst
	{

class Composition;

	namespace gnl
	{


class FileSource
{
friend class Composition;

private:
	// Only a Composition class may construct me.
	FileSource( void );
	~FileSource( void );

	// TODO macros for = delete when it becomes available.
	FileSource( const FileSource &c );

	FileSource
		&operator=( const FileSource &c );

public:

	void
		setFilename( const char *filename );

	void
		setStart( __int64 startTime );

	void
		setDuration( __int64 duration );

	void
		setSpeed( float speed );

private:

	__int64 m_start;
	__int64 m_duration;
	float   m_speed;

	GstElement *m_element;

};


	} } }
