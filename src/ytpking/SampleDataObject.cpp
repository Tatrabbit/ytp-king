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
#include "SampleDataObject.h"


	namespace ytpking
	{


SampleDataObject::SampleDataObject( void ) :
	wxDataObjectSimple( wxFormatInvalid ),
	m_dataSize( 1 ),
	m_name( new char [1] ),
	m_sample( NULL )
{
	m_name[0] = '\0';

	wxDataFormat dataFormat;
	dataFormat.SetId( "asset" );
	SetFormat( dataFormat );
}


SampleDataObject::SampleDataObject( const char *sampleName ) :
	wxDataObjectSimple( wxFormatInvalid ),
	m_dataSize( strlen( sampleName ) + sizeof(void *) + 1 ),
	m_name( new char [m_dataSize - sizeof(void *)] ),
	m_sample( NULL )
{
	strcpy( m_name, sampleName );

	wxDataFormat dataFormat;
	dataFormat.SetId( "asset" );
	SetFormat( dataFormat );
}


SampleDataObject::~SampleDataObject( void )
{
	delete [] m_name;
}


const char
*SampleDataObject::GetSampleName( void ) const
{
	return m_name;
}


void
SampleDataObject::SetSampleName( const char *sampleName )
{
	delete [] m_name;

	int len = strlen( sampleName ) + 1;
	m_dataSize = len + sizeof(void *);

	m_name = new char [len];

	strcpy( m_name, sampleName );
}


size_t
SampleDataObject::GetDataSize( void ) const
{
	// m_dataSize is faster than a strlen because we're sometimes
	// told it when the data is set.
	return m_dataSize;
}


bool
SampleDataObject::GetDataHere( void *buf ) const
{
#ifndef NDEBUG
	unsigned char *notMyPointer = ((unsigned char*)buf) + GetDataSize();
	unsigned char notMyData = *notMyPointer;
#endif

	char *charBuf = (char *)buf;

	memcpy( charBuf, &m_sample, sizeof(void *) );
	strcpy( charBuf+ sizeof(void *), m_name );

	// Let's just be sure I didn't touch other people's things.
	assert( *notMyPointer == notMyData );

	return true;
}


bool
SampleDataObject::SetData( size_t len, const void *buf )
{

	// TODO no need to deal with those crazy buffers, just copy in and out here.
	delete [] m_name;

	char *charBuf = (char *)buf;

	memcpy( &m_sample, charBuf, sizeof(void *) );


	// let's not use strcpy. What if the ending null char is missing?
	int strSize = len - sizeof(void *);
	m_name = new char [strSize];
	memcpy( m_name, charBuf + sizeof(void *), strSize );

	m_dataSize = len;

	return true;
}


	}