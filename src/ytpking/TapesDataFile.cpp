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
#define __YTPKING_TapesDataFile_cpp
#include "ytpking/TapesDataFile.h"

#include <wx/log.h>


using namespace rapidxml;


	namespace ytpking
	{

TapesDataFile::
NodeReference::NodeReference( void ) :
	m_tape( NULL ),
	m_count( 0 )
{
}


TapesDataFile::TapesDataFile( smp::TapeManager *manager ) :
	DataFile( "/tapes.xml" ),
	m_manager( manager )
{
	xml_node<> *rootNode = m_xmlDocument.first_node();

	if ( rootNode == NULL )
	{
		rootNode = m_xmlDocument.allocate_node( node_element, "ytpking" );
		m_xmlDocument.append_node( rootNode );
	}
	else if ( strcmp( rootNode->name(), "ytpking" ) != 0 )
		wxSafeShowMessage( "Error", "Samples file is corrupt. Please make a backup of it, then delete it." );
}


TapesDataFile::NodeReference
TapesDataFile::addTape( const char *name )
{
	xml_node<> *tapeNode = m_xmlDocument.allocate_node( node_element, "tape" );

	appendStringAttribute( tapeNode, "name", name );

	xml_node<> *rootNode = m_xmlDocument.first_node();
	rootNode->append_node( tapeNode );

	saveToFile();

	NodeReference nodeReference;
	nodeReference.m_tape = tapeNode;
	return nodeReference;
}


void
TapesDataFile::deleteTape( NodeReference &nodeReference )
{
	xml_node<> *rootNode = m_xmlDocument.first_node();
	xml_node<> *foundNode = rootNode->first_node( "sample" );

	while ( foundNode != NULL )
	{
		if ( foundNode == nodeReference.m_tape)
		{
			rootNode->remove_node( nodeReference.m_tape );
			nodeReference.m_tape = NULL;
			return;
		}

		foundNode = foundNode->next_sibling( "sample" );
	}
}


int
TapesDataFile::addSample( const char *guid, NodeReference &nodeReference )
{
	const char *value = m_xmlDocument.allocate_string( guid );
	xml_node<> *sampleNode = m_xmlDocument.allocate_node( node_element, "sample", value );

	nodeReference.m_tape->append_node( sampleNode );

	saveToFile();

	return nodeReference.m_count++;
}


void
TapesDataFile::loadAll( void )
{
}


	}