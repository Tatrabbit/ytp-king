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
typedef struct _GstMessage GstMessage;
typedef struct _GstBus     GstBus;

typedef void    *gpointer;


class wxWindow;

	namespace ytpking
	{
	namespace gst
	{


class Pipeline
{
public:
	Pipeline( wxWindow *drawWindow );
	~Pipeline( void );

private:
	Pipeline( const Pipeline &c );

	Pipeline
		&operator=( const Pipeline &c );
public:

	void
		play( void );
	void
		stop( void );

	
	bool
		add( GstElement *element );

private:
	GstElement *m_pipeline;

	//// BEGIN GStreamer Events

	static void
		onSync ( GstBus *bus, GstMessage *message, gpointer data );

	//// END GStreamer Events

};


	} }