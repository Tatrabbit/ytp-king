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
	m_dataSize( 0 ),
	m_data( new char [1] )
{
	m_data[0] = '\0';

	wxDataFormat dataFormat;
	dataFormat.SetId( "asset" );
	SetFormat( dataFormat );
}


SampleDataObject::SampleDataObject( const char *sampleName ) :
	wxDataObjectSimple( wxFormatInvalid ),
	m_dataSize( strlen( sampleName ) ),
	m_data( new char [m_dataSize + 1] )
{
	strcpy( m_data, sampleName );

	wxDataFormat dataFormat;
	dataFormat.SetId( "asset" );
	SetFormat( dataFormat );
}


SampleDataObject::~SampleDataObject( void )
{
	delete [] m_data;
}


const char
*SampleDataObject::GetData( void ) const
{
	return m_data;
}


void
SampleDataObject::SetData( const char *sampleName )
{
	delete [] m_data;

	m_dataSize = strlen( sampleName );

	m_data = new char [m_dataSize + 1];
	strcpy( m_data, sampleName );
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
	memcpy( buf, m_data, m_dataSize );

	return true;
}


bool
SampleDataObject::SetData( size_t len, const void *buf )
{
	delete [] m_data;

	m_data = new char [len + 1];
	memcpy( m_data, buf, len );

	m_data[len] = '\0';

	m_dataSize = len;

	return true;
}


	}