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
#ifndef __YTPKING_SampleDataObject_h
#define __YTPKING_SampleDataObject_h

#include <wx/dataobj.h>

#include <string>


	namespace ytpking
	{

namespace smp
{
	class Sample;
}

namespace gst {
namespace gnl {
	class FileSource;
} }


class SampleDataObject :
	public wxDataObjectSimple
{
public:

	SampleDataObject( void );
	explicit SampleDataObject( const char *sampleName );

	virtual ~SampleDataObject( void );
private:
	explicit SampleDataObject( SampleDataObject & );
	void operator=( SampleDataObject & );
public:

	smp::Sample *m_sample;


	const char
		*GetSampleName( void ) const;

	void
		SetSampleName( const char *sampleName );

private:

	size_t m_dataSize;

	char *m_name;

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


#endif