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
#include "gst/gnl/PreviewUser.h"

#include "rapidxml/rapidxml.hpp"

#include <wx/treectrl.h>


	namespace ytpking
	{

namespace smp {
	class SampleManager;
}


class SamplesDataFile :
	public DataFile,
	public gst::gnl::PreviewUser
{
public:
	explicit SamplesDataFile( smp::SampleManager *manager );
	virtual ~SamplesDataFile( void );
private:
	explicit SamplesDataFile( SamplesDataFile & );
	void operator=( SamplesDataFile & );
public:

	class NodeReference
	{
		friend class SamplesDataFile;

	private:
		rapidxml::xml_node<> *m_speaker;
		rapidxml::xml_node<> *m_speech;
	};

	NodeReference
		addSample( const char *name, const char *speaker );
	void
		renameSample( const char *newName, NodeReference &nodeReference );

	void
		changeSampleSpeaker( const char *newSpeakerName, NodeReference &nodeReference );

	// TODO I can optimize this by storing a hashmap of existing speaker nodes.
	//      currently it's searched top to bottom each time.
	rapidxml::xml_node<>
		*getOrMakeSpeakerNode( const char *speakerName );

	void
		saveToFile( void ) const;

	void
		loadAll( void );

private:

	std::string m_filename;

	smp::SampleManager *m_manager;
	char *m_fileBuffer;
	rapidxml::xml_document<> m_xmlDocument;
	bool m_isLocked;

};


	}


#endif