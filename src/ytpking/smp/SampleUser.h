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


	namespace ytpking
	{

namespace smp {
	class Sample;
}

	namespace gst
	{
	namespace gnl
	{


class SampleManager;


/** Base class for classes which are affected when a Sample is added or removed. */
class SampleUser
{
friend class SampleManager;

public:
	SampleUser( SampleManager &manager );
	~SampleUser( void );
private:
	SampleUser( SampleUser &);
	void operator=( const SampleUser & );

protected:
	/** A new smp::Sample has been added to SampleManager object.
	\param sampleName  The name of the added Sample.
	\param speakerName The name of the speaker
	\param addedSample The newly added smp::Sample. */
	virtual void
		onAddSample( char const *sampleName, char const *speakerName, smp::Sample *addedSample ) = 0;

	/** Called when a smp::Sample is selected.
	\param selectedSample The newly selected smp::Sample */
	virtual void
		onSelectSample( smp::Sample *selectedSample ) = 0;

	/** Called when a smp::Sample is about to be deleted.
	If a pointer matching deletedSample is held, it should be set to NULL or otherwise
	set to no longer match the sample, as that data is soon to be destroyed.
	\param deletedSample The sample which will soon be destroyed by SampleManager */
	virtual void
		onDeleteSample( smp::Sample *deletedSample ) = 0;

	/** Called when a smp::Sample has been renamed.
	\param newSampleName The new name of the sample
	\param sample        A pointer to the sample being renamed. */
	virtual void
		onRenameSample( char const *newSampleName, smp::Sample *sample ) = 0;

	/** Called when a smp::Sample's speaker has been changed.
	\param newSampleName The new name of the sample
	\param sample        A pointer to the sample being renamed. */
	virtual void
		onChangeSampleSpeaker( char const *speakerName, smp::Sample *sample ) = 0;

private:

	SampleManager *m_manager;
};


	} } }