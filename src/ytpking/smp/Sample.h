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
#ifndef __YTPKING_SMP_Sample_h
#define __YTPKING_SMP_Sample_h

#include <string>


	namespace ytpking
	{

namespace gst {
namespace gnl {
	class TapeComposition;
	class FileSource;
} }

	namespace smp
	{


// TODO store the name here
class Sample
{
public:
	Sample( const char *filename );

	std::string m_filename;

	unsigned int m_start;
	unsigned int m_duration;

	void
		addToPreviewTapes( gst::gnl::FileSource *& audioSource, gst::gnl::FileSource *& videoSource ) const;

};


	} }


#endif