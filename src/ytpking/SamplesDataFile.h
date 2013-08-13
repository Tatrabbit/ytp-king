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
#ifndef __YTPKING_SamplesDataFile_h
#define __YTPKING_SamplesDataFile_h

#include "ytpking/DataFile.h"

#include "rapidxml/rapidxml.hpp"


	namespace ytpking
	{

namespace smp {
	class SampleManager;
}


class SamplesDataFile :
	public DataFile
{
public:
	explicit SamplesDataFile( smp::SampleManager *manager );

	class NodeReference
	{
	public:
		NodeReference( void );

	private:
		friend class SamplesDataFile;

		rapidxml::xml_node<> *m_speaker;
		rapidxml::xml_node<> *m_speech;

		char *m_startString;
		char *m_endString;
	};

	NodeReference
		addSample( const char *name, const char *speaker, const char *guid );
	void
		renameSample( const char *newName, NodeReference &nodeReference );

	void
		changeSampleSpeaker( const char *newSpeakerName, NodeReference &nodeReference );

	void
		setSampleStart( int sampleStart, NodeReference &nodeReference );
	void
		setSampleEnd( int sampleStart, NodeReference &nodeReference );

	void
		loadAll( void )
		override;

	void
		saveToFile( void ) const
		override;

private:

	smp::SampleManager *m_manager;
	bool m_isLocked;

	// TODO I can optimize this by storing a hashmap of existing speaker nodes.
	//      currently it's searched top to bottom each time.
	rapidxml::xml_node<>
		*getOrMakeSpeakerNode( const char *speakerName );

};


	}


#endif