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
#ifndef YTPKING_SMP_SampleInstance_h
#define YTPKING_SMP_SampleInstance_h

#include <set>


	namespace ytpking
	{

namespace gst {
namespace gnl {
	class TapeComposition;
	class FileSource;
} }

	namespace smp
	{


class Tape;
class Sample;


class SampleInstance
{
	friend class Tape;

public:
	SampleInstance( const Sample *sample );
	~SampleInstance( void );

private:
	SampleInstance( SampleInstance &);
	void operator=( SampleInstance &);

public:

	inline bool operator==( const SampleInstance &other ) const { return m_id == other.m_id; }
	inline bool operator< ( const SampleInstance &other ) const { return m_id <  other.m_id; }

	const Sample
		&getSample( void ) const;

private:
	const Sample *m_sample;

	static unsigned int m_nInstances;
	const unsigned int  m_id;

	bool m_isConnected;

	void
		connectToPreview( void );

};


	} }


#endif