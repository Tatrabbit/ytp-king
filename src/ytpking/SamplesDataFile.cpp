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
#include "ytpking/SamplesDataFile.h"

#include <fstream>

#include <wx/log.h>

#include "lnb/SamplesTreeCtrl.h"

#include "rapidxml/rapidxml_print.hpp"

#include "gst/gnl/Composition.h"
#include "gst/gnl/FileSource.h"


using namespace rapidxml;


	namespace ytpking
	{

using lnb::SamplesTreeCtrl;


SamplesDataFile::SamplesDataFile( SamplesTreeCtrl *samplesTreeCtrl ) :
	m_treeCtrl( samplesTreeCtrl ),
	m_filename( getSaveDataPath() ),
	m_isLocked( false )
{
	m_filename += "/samples.xml";

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

	if ( m_xmlDocument.first_node() == NULL )
	{
		xml_node<> *rootNode = m_xmlDocument.allocate_node( node_element, "samples" );
		m_xmlDocument.append_node( rootNode );
	}
}


SamplesDataFile::~SamplesDataFile( void )
{
	if ( m_fileBuffer != NULL )
		delete [] m_fileBuffer;
}


void
SamplesDataFile::addSample( const char *name, const char *speaker )
{
	if ( m_isLocked )
		return;

	xml_node<> *speakerNode = getOrMakeSpeakerNode( speaker );
	xml_node<> *speechNode  = m_xmlDocument.allocate_node( node_element, "speech" );

	const char *val = m_xmlDocument.allocate_string( name );
	xml_attribute<> *nameAttribute = m_xmlDocument.allocate_attribute( "name", val );

	speechNode->append_attribute( nameAttribute );

	speakerNode->append_node( speechNode );

	saveToFile();
}


xml_node<>
*SamplesDataFile::getOrMakeSpeakerNode( const char *speakerName )
{
	if ( m_isLocked )
		return NULL;

	// Get the XML name and compare
	xml_node<> *rootNode = m_xmlDocument.first_node();

	xml_node<> *speakerNode = rootNode->first_node( "speaker" );

	while ( speakerNode != NULL )
	{
		xml_attribute<> *nameAttr = speakerNode->first_attribute( "name" );

		if ( nameAttr && (strcmp( nameAttr->value(), speakerName ) == 0) )
			break;

		speakerNode = speakerNode->next_sibling( "speaker" );
	}

	if ( speakerNode == NULL )
	{
		speakerNode = m_xmlDocument.allocate_node( node_element, "speaker" );
		speakerName = m_xmlDocument.allocate_string( speakerName );
		xml_attribute<> *nameAttr = m_xmlDocument.allocate_attribute( "name", speakerName );

		speakerNode->append_attribute( nameAttr );

		rootNode->append_node( speakerNode );
	}

	return speakerNode;
}


void
SamplesDataFile::saveToFile( void ) const
{
	std::ofstream oFile( m_filename, std::ofstream::out|std::ofstream::trunc );

	oFile << m_xmlDocument;
}


void
SamplesDataFile::loadAll( void )
{
	m_isLocked = true;

	using gst::gnl::FileSource;

	xml_node<> *rootNode = m_xmlDocument.first_node();

	xml_node<> *speakerNode = rootNode->first_node( "speaker" );

	while ( speakerNode != NULL )
	{
		xml_attribute<> *speakerNameAttr = speakerNode->first_attribute( "name" );
		if ( speakerNameAttr == NULL )
		{
			speakerNode = speakerNode->next_sibling( "speaker" );
			continue;
		}
		const char *speakerName = speakerNameAttr->value();

		xml_node<> *speechNode = speakerNode->first_node( "speech" );

		while ( speechNode != NULL )
		{
			xml_attribute<> *speechNameAttr = speechNode->first_attribute( "name" );
			if ( speechNameAttr == NULL )
			{
				speechNode = speechNode->next_sibling( "speech" );
				continue;
			}
			const char *speechName = speechNameAttr->value();

			FileSource *audioSource, *videoSource;

			audioSource = m_audioPreviewComposition->addSource();
			videoSource = m_videoPreviewComposition->addSource();

			m_treeCtrl->addSample( speechName, speakerName, audioSource, videoSource );
			speechNode = speechNode->next_sibling( "speech" );
		}

		speakerNode = speakerNode->next_sibling( "speaker" );
	}


	m_isLocked = false;
}


	}