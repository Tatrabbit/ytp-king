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
#include "ytpking/SamplesDataFile.h"

#include <wx/log.h>

#include "ytpking/Guid.h"

#include "gst/gnl/TapeComposition.h"
#include "gst/gnl/FileSource.h"

#include "smp/SampleManager.h"
#include "smp/Sample.h"


#define MAX_START_FRAME_SIZE 16u
#define MAX_END_FRAME_SIZE   16u


using namespace rapidxml;


	namespace ytpking
	{

		using smp::SampleManager;


SamplesDataFile::
NodeReference::NodeReference( void ) :
	m_speaker( NULL ),
	m_speech( NULL ),
	m_startString( NULL ),
	m_endString( NULL )
{
}


SamplesDataFile::SamplesDataFile( SampleManager *manager ) :
	DataFile( "/samples.xml" ),
	m_manager( manager ),
	m_isLocked( false )
{
	xml_node<> *rootNode = m_xmlDocument.first_node();

	if ( rootNode == NULL )
	{
		rootNode = m_xmlDocument.allocate_node( node_element, "ytpking" );
		m_xmlDocument.append_node( rootNode );

		xml_node<> *samplesNode = m_xmlDocument.allocate_node( node_element, "samples" );
		rootNode->append_node( samplesNode );
	}
	else
	{
		bool shownMessage;
		if ( strcmp( rootNode->name(), "ytpking" ) != 0 )
		{
			wxSafeShowMessage( "Error", "Samples file is corrupt. Please make a backup of it, then delete it." );
			shownMessage = true;
		}
		else
			shownMessage = false;

		if ( rootNode->first_node( "samples" ) == NULL )
		{
			if ( !shownMessage )
				wxSafeShowMessage( "Error", "Samples file is corrupt. Please make a backup of it, then delete it." );

			xml_node<> *samplesNode = m_xmlDocument.allocate_node( node_element, "samples" );
			rootNode->append_node( samplesNode );
		}
	}
}


SamplesDataFile::NodeReference
SamplesDataFile::addSample( const char *name, const char *speaker, const char *guid )
{
	NodeReference nodeReference;

	if ( m_isLocked )
		return nodeReference;


	nodeReference.m_speaker = getOrMakeSpeakerNode( speaker );
	nodeReference.m_speech  = m_xmlDocument.allocate_node( node_element, "speech" );

	appendStringAttribute( nodeReference.m_speech, "name", name );
	appendStringAttribute( nodeReference.m_speech, "guid", guid );

	nodeReference.m_speaker->append_node( nodeReference.m_speech );

	saveToFile();

	return nodeReference;
}


void
SamplesDataFile::renameSample( const char *newName, NodeReference &nodeReference )
{
	xml_attribute<> *nameAttr = nodeReference.m_speech->first_attribute( "name" );

	newName = m_xmlDocument.allocate_string( newName );
	nameAttr->value( newName );

	saveToFile();
}


void
SamplesDataFile::changeSampleSpeaker( const char *newSpeakerName, NodeReference &nodeReference )
{
	nodeReference.m_speaker->remove_node( nodeReference.m_speech );

	if ( nodeReference.m_speaker->first_node() == NULL )
	{
		xml_node<> *samplesNode = m_xmlDocument.first_node()->first_node( "samples" );
		samplesNode->remove_node( nodeReference.m_speaker );
	}

	xml_node<> *speakerNode = getOrMakeSpeakerNode( newSpeakerName );
	if ( speakerNode )
	{
		nodeReference.m_speaker = speakerNode;
		nodeReference.m_speaker->append_node( nodeReference.m_speech );

		saveToFile();
	}
}


void
SamplesDataFile::setSampleStart( int sampleStart, NodeReference &nodeReference )
{
	if ( !setOrMakeNumberAttribute( sampleStart, nodeReference.m_speech, nodeReference.m_startString, "start", MAX_START_FRAME_SIZE ) )
		wxLogError( "Start time can't be more than %d digits long.", MAX_START_FRAME_SIZE - 1 );
}


void
SamplesDataFile::setSampleEnd( int sampleEnd, NodeReference &nodeReference )
{
	if ( !setOrMakeNumberAttribute( sampleEnd, nodeReference.m_speech, nodeReference.m_endString,  "end", MAX_END_FRAME_SIZE ) )
		wxLogError( "End time can't be more than %d digits long.", MAX_END_FRAME_SIZE - 1 );
}


void
SamplesDataFile::loadAll( void )
{
	m_isLocked = true;

	using gst::gnl::FileSource;

	xml_node<> *samplesNode = m_xmlDocument.first_node()->first_node( "samples" );

	xml_node<> *speakerNode = samplesNode->first_node( "speaker" );

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

			NodeReference nodeReference;
			nodeReference.m_speaker = speakerNode;
			nodeReference.m_speech  = speechNode;

			smp::Sample *sample = m_manager->addSample( "file:///C:/zelda.mp4", speechName, speakerName, &nodeReference );

			// get duration start and end
			int start, duration, end;
			start = getIntAttribute( speechNode, "start", 0 );
			end   = getIntAttribute( speechNode, "end", 5 );

			duration = end - start;
			if ( duration <= 0 ) // guard against invalid duration
				duration = 5;

			sample->m_start = start;
			sample->m_duration = duration;

			// get guid
			if ( !getStringAttribute( speechNode, "guid", sample->m_guid ) )
			{
				Guid guid;
				sample->m_guid = guid;
				appendStringAttribute( speechNode, "guid", guid );
			}

			speechNode = speechNode->next_sibling( "speech" );
		}

		speakerNode = speakerNode->next_sibling( "speaker" );
	}


	m_isLocked = false;
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



	}