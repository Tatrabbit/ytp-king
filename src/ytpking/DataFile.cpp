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
#include "ytpking/DataFile.h"

#include <fstream>
#include <sstream>

#include <wx/log.h>

#include "rapidxml/rapidxml_print.hpp"

#include "ytpking/DataDirectory.h"


using namespace rapidxml;


	namespace ytpking
	{


DataFile::DataFile( const char *filename ) :
	m_filename( ytpking::dataDirectory.getSaveDataPath() )
{
	m_filename += filename;

	FILE * f = fopen( m_filename.c_str() , "rb" );
	if ( f )
	{
		// TODO there has to be a way to stream this :/
		fseek( f , 0, SEEK_END );
		long fileSize = ftell( f );
		rewind( f );

		m_fileBuffer = new char [fileSize + 1];

		// copy the file into the buffer:
		size_t bytesRead = fread( m_fileBuffer, 1, fileSize, f );
		if ( bytesRead != fileSize )
		{
			delete [] m_fileBuffer;
			m_fileBuffer = NULL;

			wxLogError( "Error reading saved samples.xml" );
		}

		m_fileBuffer[fileSize] = '\0';

		m_xmlDocument.parse<0>( m_fileBuffer );
	}
	else
		m_fileBuffer = NULL;
}


DataFile::~DataFile( void )
{
	if ( m_fileBuffer != NULL )
		delete [] m_fileBuffer;
}


void
DataFile::saveToFile( void ) const
{
	std::ofstream oFile( m_filename, std::ofstream::out|std::ofstream::trunc );

	oFile << m_xmlDocument;
}


bool
DataFile::setOrMakeNumberAttribute( int integerNumber, xml_node<> *node, char *&valueChar, const char *attributeName, size_t maxSize )
{
	std::stringstream stream;
	stream << integerNumber;

	std::string value( stream.str() );

	if ( value.length() >= maxSize )
		return false;

	xml_attribute<> *attr = node->first_attribute( attributeName );

	if ( attr == NULL )
	{
		attr = m_xmlDocument.allocate_attribute( attributeName, valueChar );
		node->append_attribute( attr );
	}

	if ( valueChar == NULL )
		valueChar = m_xmlDocument.allocate_string( value.c_str(), maxSize );

	strcpy( valueChar, value.c_str() );
	attr->value( valueChar );

	return true;
}


bool
DataFile::getStringAttribute( const rapidxml::xml_node<> *node, const char *attributeName, std::string &string ) const
{
	
	const xml_attribute<> *attr = node->first_attribute( attributeName );

	if ( attr == NULL )
		return false;

	string = attr->value();
	return true;
}


int
DataFile::getIntAttribute( const xml_node<> *node, const char *attributeName, int defaultValue ) const
{
	const xml_attribute<> *attr = node->first_attribute( attributeName );

	if ( attr == NULL )
		return defaultValue;

	int i;

	if ( sscanf( attr->value(), "%d", &i ) == 1 )
		return i;
	else
		return defaultValue;
}


void
DataFile::appendStringAttribute( rapidxml::xml_node<> *node, const char *allocatedAttributeName, const char *attributeValue )
{
	const char *val = m_xmlDocument.allocate_string( attributeValue );
	xml_attribute<> *nameAttribute = m_xmlDocument.allocate_attribute( allocatedAttributeName, val );
	node->append_attribute( nameAttribute );
}


	}