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

#include "smp/SampleManager.h"
#include "smp/Sample.h"
#include "smp/SampleInstance.h"
#include "smp/TapeManager.h"
#include "smp/Tape.h"


using namespace rapidxml;


	namespace ytpking
	{

TapesDataFile::
TapeNodeReference::TapeNodeReference( void ) :
	m_tape( NULL )
{
}


TapesDataFile::
InstanceNodeReference::InstanceNodeReference( void ) :
	m_instance( NULL )
{
}


TapesDataFile::TapesDataFile( void ) :
	TapeUser( *smp::tapeManager ),
	DataFile( "/tapes.xml" ),
	m_isLocked( false )
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


void
TapesDataFile::onAddTape( smp::Tape &addedTape )
{
	if ( m_isLocked )
		return;

	xml_node<> *tapeNode = m_xmlDocument.allocate_node( node_element, "tape" );

	appendStringAttribute( tapeNode, "name", addedTape.getName() );

	xml_node<> *rootNode = m_xmlDocument.first_node();
	rootNode->append_node( tapeNode );

	addedTape.getNodeReference().m_tape = tapeNode;

	saveToFile();
}


void
TapesDataFile::onDeleteTape( smp::Tape &deletedTape )
{
	xml_node<> *rootNode = m_xmlDocument.first_node();
	xml_node<> *foundNode = rootNode->first_node( "sample" );

	while ( foundNode != NULL )
	{
		TapeNodeReference *nodeReference = &deletedTape.getNodeReference();
		if ( foundNode == nodeReference->m_tape)
		{
			rootNode->remove_node( nodeReference->m_tape );
			nodeReference->m_tape = NULL;
			return;
		}

		foundNode = foundNode->next_sibling( "sample" );
	}
}


void
TapesDataFile::onRenameTape( smp::Tape &tape )
{
	TapeNodeReference *nodeReference = &tape.getNodeReference();
	xml_attribute<> *nameAttribute = nodeReference->m_tape->first_attribute( "name" );

	if ( nameAttribute == NULL )
	{
		nameAttribute = m_xmlDocument.allocate_attribute( "name" );
		nodeReference->m_tape->append_attribute( nameAttribute );
	}
	const char *name = m_xmlDocument.allocate_string( tape.getName() );
	nameAttribute->value( name );

	saveToFile();
}


void
TapesDataFile::onLoadAllTapes( void )
{
	m_isLocked = true;

	xml_node<> *rootNode = m_xmlDocument.first_node();

	xml_node<> *tapeNode = rootNode->first_node( "tape" );
	
	bool hadError = false;
	while ( tapeNode != NULL )
	{
		TapeNodeReference tapeNodeReference;
		tapeNodeReference.m_tape = tapeNode;

		std::string name;
		if ( !getStringAttribute( tapeNode, "name", name ) )
			name = "(No Name)";

		smp::Tape *tape = smp::tapeManager->addTape( name.c_str(), &tapeNodeReference );

		xml_node<> *contentNode = tapeNode->first_node();

		while( contentNode != NULL )
		{
			if ( strcmp( contentNode->name(), "sample" ) == 0 )
			{
				InstanceNodeReference instanceNodeReference;
				instanceNodeReference.m_instance = contentNode;

				smp::Sample *sample = smp::sampleManager->getSampleByGuid( contentNode->value() );
				if ( sample != NULL )
					smp::tapeManager->appendInstance( tape, *sample, &instanceNodeReference );
				else
				{
					if ( !hadError )
					{// Only report once, it could be extremely annoying otherwise! Log the rest queitly.
						wxLogError( "One or more elements in the tape file were not loaded correctly." );
						hadError = true;
					}
					wxLogWarning( "Could not load sample %s for tape %s.", contentNode->value(), "{}" );
				}
			}
			// TODO
			// else if ( strcmp( contentNode->name(), "sample" ) == 0 )
			contentNode = contentNode->next_sibling();
		}

		tapeNode = tapeNode->next_sibling( "tape" );
	}

	m_isLocked = false;
}


void
TapesDataFile::onTapeAddInstance( smp::Tape &tape, smp::SampleInstance &sampleInstance )
{
	if ( m_isLocked )
		return;

	const char *value = m_xmlDocument.allocate_string( sampleInstance.getSample().getGuid() );
	xml_node<> *instanceNode = m_xmlDocument.allocate_node( node_element, "sample", value );

	tape.getNodeReference().m_tape->append_node( instanceNode );
	sampleInstance.getNodeReference().m_instance = instanceNode;

	saveToFile();
}


void
TapesDataFile::onTapeDeleteInstance( smp::Tape &tape, smp::SampleInstance &sampleInstance )
{
	xml_node<>  *tapeNode     =  tape.getNodeReference().m_tape;
	xml_node<> **instanceNode = &sampleInstance.getNodeReference().m_instance;

	tapeNode->remove_node( *instanceNode );

	*instanceNode = NULL;

	saveToFile();
}


	}