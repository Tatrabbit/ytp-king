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
#ifndef YTPKING_SMP_Tape_h
#define YTPKING_SMP_Tape_h

#include <list>
#include <set>

#include "ytpking/TapesDataFile.h"


	namespace ytpking
	{

namespace gst {
namespace gnl {
	class TapeComposition;
} }

	namespace smp
	{


class Sample;
class SampleInstance;


class Tape
{
public:
	explicit Tape( TapesDataFile::NodeReference &nodeReference );
	~Tape( void );
private:
	explicit Tape( Tape & );
	void operator=( Tape & );
public:

	typedef std::list<SampleInstance *>           InstanceSet;
	typedef std::set<gst::gnl::TapeComposition *> CompositionSet;

	const InstanceSet
		&getInstances( void ) const;

	SampleInstance
		*appendSample( const Sample &sample, bool suppressSave = false );

	void
		deleteSample( const SampleInstance &sampleInstance );

	void
		connectToPreview( void );

	inline TapesDataFile::NodeReference
		&getNodeReference( void )
	{ return m_nodeReference; }


private:

	InstanceSet m_samples;
	TapesDataFile::NodeReference m_nodeReference;

	bool m_isConnected;

};


	} }


#endif