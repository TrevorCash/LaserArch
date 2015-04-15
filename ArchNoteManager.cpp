/* 
* ArchNoteManager.cpp
*
* Created: 4/2/2015 3:04:36 PM
* Author: 7002815
*/


#include "ArchNoteManager.h"

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
	//Serial.print("Moving Finger: ");
	//Serial.println((int)finger);
	//Serial.println(finger->centerTime);
}
void ArchNoteManager::OnFingerStart(ArchFinger* finger)
{
	
	Serial.print("Start Finger: ");
	Serial.println((int)finger);
	
	
	finger->lastRegion = finger->curRegion;
	
	//find the region!
	ArchRegion* region = regionManager->FindRegionAtTick(finger->centerTime);
	if(!region) return;
	
	region->SetColors(255,0,0);
	
	//cross reference finger pos with region note...
	//finger.curnote = that note
	//midinoteon(that note)
}
void ArchNoteManager::OnFingerStop(ArchFinger* finger)
{
	Serial.print("Stop Finger: ");
	Serial.println((int)finger);
		
	
	ArchRegion* region = regionManager->FindRegionAtTick(finger->centerTime);
	if(!region) return;
	
	region->SetColors(0,0,255);

		
}


