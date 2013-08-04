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
#include <wx/dataobj.h>

#include <string>


	namespace ytpking
	{

namespace gst {
namespace gnl {
	class FileSource;
} }


class SampleDataObject :
	public wxDataObjectSimple
{
public:

	SampleDataObject( void );
	SampleDataObject( const char *sampleName );

	virtual
		~SampleDataObject( void );

	gst::gnl::FileSource
		*GetAudioSource( void ) const;

	void
		SetAudioSource( gst::gnl::FileSource *audioSource );


	gst::gnl::FileSource
		*GetVideoSource( void ) const;

	void
		SetVideoSource( gst::gnl::FileSource *videoSource );

	const char
		*GetSampleName( void ) const;

	void
		SetSampleName( const char *sampleName );

private:

	size_t m_dataSize;

	char *m_name;
	gst::gnl::FileSource *m_audioSource;
	gst::gnl::FileSource *m_videoSource;

	inline void
		SetFormat( const wxDataFormat &format )
	{ wxDataObjectSimple::SetFormat( format ); }


	size_t
		GetDataSize( void )
		const override;

	bool
		GetDataHere( void *buf )
		const override;


	bool SetData( size_t len, const void *buf )
		override;

};


	}