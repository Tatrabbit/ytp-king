/*  YTP King - Easy to use sentence mixer
 *  Copyright (C) 2013  Alex "rainChu" Haddad
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
#include "SourcesNotebook.h"

#include "SourcesPage.h"
#include "SamplesPage.h"
#include "TapesPage.h"


	namespace ytpking
	{
	namespace snb
	{


SourcesNotebook::SourcesNotebook( wxWindow *parent ) :
	wxNotebook( parent, -1, wxDefaultPosition, wxDefaultSize )
{
	m_sourcesPage = new SourcesPage( this );
	AddPage( m_sourcesPage, "Sources" );

	m_samplesPage = new SamplesPage( this );
	AddPage( m_samplesPage, "Samples" );

	m_tapesPage = new TapesPage( this );
	AddPage( m_tapesPage, "Tapes" );
}



	} }