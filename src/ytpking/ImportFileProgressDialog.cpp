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
#include "ImportFileProgressDialog.h"

#include "ytpking/DataDirectory.h"

#define BLOCK_SIZE (512u * 64u)

	namespace ytpking
	{


ImportFileProgressDialog::ImportFileProgressDialog( wxWindow *parent, const char *fullFilepath, const char *filename ) :
	wxProgressDialog( _("Import File"), _("Please be patient, importing..."), 1000, parent, wxPD_APP_MODAL|wxPD_CAN_ABORT ),
	m_filepath( fullFilepath ),
	m_filename( filename )
{
}

int
ImportFileProgressDialog::ShowModal( void )
{
	FILE *iFile = fopen( m_filepath.c_str(), "rb" );
	if ( iFile == NULL )
		return ModalResult::FileNotOpened;

	// Set the range to the filesize.
	size_t fileSize;
	fseek( iFile, 0, SEEK_END );
	fileSize = ftell( iFile );
	fseek( iFile, 0, SEEK_SET );

	SetRange( fileSize );

	std::string destinationPath = ytpking::dataDirectory.getSaveDataPath();
	destinationPath += "/sources/";
	destinationPath += m_filename;

	FILE *oFile = fopen( destinationPath.c_str(), "wb" );
	if ( oFile == NULL )
	{
		fclose( iFile );
		return ModalResult::WriteError;
	}

	wxProgressDialog::ShowModal();

	int currentValue = 0;

	unsigned char block[BLOCK_SIZE];
	bool finished = false;
	while( !finished )
	{
		size_t bytesRead;

		bytesRead = fread( block, sizeof( unsigned char ), BLOCK_SIZE, iFile );

		if ( bytesRead != BLOCK_SIZE )
		{
			if ( ferror( iFile ) )
			{
				fclose( oFile );
				fclose( iFile );
				return ModalResult::ReadError;
			}
			finished = true;
		}


		if ( fwrite( block, sizeof( unsigned char ), bytesRead, oFile ) != bytesRead )
		{
			fclose( oFile );
			fclose( iFile );
			return ModalResult::WriteError;
		}

		if ( !Update( currentValue += bytesRead ) )
		{
			fclose( oFile );
			fclose( iFile );
			return ModalResult::UserAbort;
		}
	}

	fclose( oFile );
	fclose( iFile );
	return ModalResult::FileCopied;
}


	}