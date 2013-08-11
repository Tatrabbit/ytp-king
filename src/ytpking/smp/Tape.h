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


	namespace ytpking
	{

namespace gst {
namespace gnl {
	class TapeComposition;
	class FileSource;
} }

	namespace smp
	{


class Sample;


class Tape
{
public:
	Tape( void );
	~Tape( void );
private:
	explicit Tape( Tape & );
	void operator=( Tape & );
public:
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

	private:
		struct Source
		{
			gst::gnl::FileSource      *fileSource;
			gst::gnl::TapeComposition *composition;

			inline bool operator< ( const Source &other ) const { return fileSource <  other.fileSource; }
		};
		typedef std::set<Source> SourceSet;

		const Sample *m_sample;

		static unsigned int m_nInstances;
		const unsigned int  m_id;

		SourceSet m_sources;

		void
			connectToComposition( gst::gnl::TapeComposition &composition );

	};


	typedef std::list<SampleInstance *>           InstanceSet;
	typedef std::set<gst::gnl::TapeComposition *> CompositionSet;

	const InstanceSet
		&getInstances( void ) const;

	SampleInstance
		*appendSample( const Sample &sample );

	void
		deleteSample( const SampleInstance &sampleInstance );

	void
		connectToComposition( gst::gnl::TapeComposition &composition );

private:

	InstanceSet    m_samples;

};


	} }


#endif