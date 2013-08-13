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
#ifndef __YTPKING_GST_Pipeline_h
#define __YTPKING_GST_Pipeline_h


typedef struct _GstElement GstElement;
typedef struct _GstMessage GstMessage;
typedef struct _GstBus     GstBus;

typedef void    *gpointer;


class wxWindow;

	namespace ytpking
	{
	namespace gst
	{


namespace gnl {
	class Composition;
}


/** A wrapper for a GStreamer pipeline. */
class Pipeline
{
public:

	Pipeline( void );
	~Pipeline( void );

	bool m_hasContent;

private:
	Pipeline( Pipeline & );

	void
		operator=( const Pipeline & );

public:

	/** Initializes the Pipeline. Must be called after gst_init. */
	void
		initialize( void );

	/** Sets the window to render onto.
	\param renderWindow The wxWindow to render onto. This should preferably be
	                  an empty control */
	void
		setRenderWindow( wxWindow *renderWindow );

	/** Starts the pipeline playing. This will fail if setRenderWindow hasn't
	    been called. */
	void
		play( void );

	/** Stops the pipeline if playing. */
	void
		stop( void );

	/** Access to the Gst pipeline.
	\todo remove this, it's silly. */
	GstElement
		*operator*( void );

private:
	GstElement *m_pipeline;
	bool        m_hasSetRenderWindow;

	static void
		onMessage ( GstBus *bus, GstMessage *message, gpointer data );

	static void
		onSyncMessage ( GstBus *bus, GstMessage *message, gpointer data );

};

#ifdef YTPKING_GST_Pipeline_cpp
	Pipeline timelinePipeline;
#else
	/** The pipeline for the timeline preview. */
	extern Pipeline timelinePipeline;
#endif


	} }


#endif