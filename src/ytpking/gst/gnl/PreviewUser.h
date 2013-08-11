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
#ifndef __YTPKING_GST_GNL_PreviewUser_h
#define __YTPKING_GST_GNL_PreviewUser_h


	namespace ytpking
	{
	namespace gst
	{

class Pipeline;

	namespace gnl
	{


class TapeComposition;

// TODO refactor this to have both compositions as a global instead.
class PreviewUser
{
protected:

	static void
		initialize( Pipeline *pipeline );

	static void
		cleanup( void );

	static TapeComposition *m_audioPreviewComposition;
	static TapeComposition *m_videoPreviewComposition;


};

	} } }


#endif