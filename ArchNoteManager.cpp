/* 
* ArchNoteManager.cpp
*
* Created: 4/2/2015 3:04:36 PM
* Author: 7002815
*/


#include "ArchNoteManager.h"
#include "MIDI.h"

// default constructor
ArchNoteManager::ArchNoteManager( ArchRegionManager* regionManager)
{
	this->regionManager = regionManager;
	
} //ArchNoteManager

// default destructor
ArchNoteManager::~ArchNoteManager()
{
} //~ArchNoteManager


void ArchNoteManager::OnFingerMove(ArchFinger* finger)
{
	if(finger->curRegion != finger->lastRegion)
	{
		MIDI.sendNoteOff(finger->lastRegion->midiNote,0,1);
		MIDI.sendNoteOn(finger->curRegion->midiNote,127,1);
	}
}
void ArchNoteManager::OnFingerStart(ArchFinger* finger)
{
	MIDI.sendNoteOn(finger->curRegion->midiNote,127,1);
}
void ArchNoteManager::OnFingerStop(ArchFinger* finger)
{
	MIDI.sendNoteOff(finger->curRegion->midiNote,0,1);	
}


