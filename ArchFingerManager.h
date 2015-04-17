/* 
* ArchFingerManager.h
*
* Created: 3/23/2015 5:34:21 PM
* Author: 7002815
*/


#ifndef __ARCHFINGERMANAGER_H__
#define __ARCHFINGERMANAGER_H__

#include "ArchBlobManager.h"
#include "ArchFinger.h"
#include "Arduino.h"
#include "ArchFingerBlobConnection.h"
#include "ArchNoteManager.h"
#include "ArchMotor.h"

class ArchFingerManager
{

//functions
public:
	ArchFingerManager(ArchBlobManager* blobManager, ArchNoteManager* noteManager, ArchRegionManager* regionManager, ArchMotor* mainMotor);
	~ArchFingerManager();
	uint16_t numActiveFingers;
	boolean printFingerEvents;

	void Update();//called from main loop;
	
	//print all finger info
	void PrintFingerInfo()
	{
		Serial.println("Finger Pool Information:");
		int f;
		for(f = 0; f < MAX_FINGERS; f++)
		{
			Serial.print("Finger: ");
			Serial.println((int)&fingerPool[f]);
			Serial.print("Validity: ");
			Serial.println(fingerPool[f].validity);
			Serial.print("IsUsed: ");
			Serial.println(fingerPool[f].isUsed);
			Serial.print("HasStarted: ");
			Serial.println(fingerPool[f].hasStarted);
		}
	}

protected:
	ArchBlobManager* blobManager;
	ArchNoteManager* noteManager;
	ArchRegionManager* regionManager;
	ArchMotor* mainMotor;
private:
	ArchFinger fingerPool[MAX_FINGERS]; //memory for holding the fingers
	
	
	ArchFingerBlobConnection connectionLinks[MAX_BLOBS*MAX_FINGERS];
	uint16_t connectionLinksCurIdx;
	
	//the functions call other manager callback functions by design..
	void FingerStart(ArchFinger* finger);
	void FingerMove(ArchFinger* finger, ArchRawBlob* blob);
	void FingerStop(ArchFinger* finger);
	
	
	
}; //ArchFingerManager

#endif //__ARCHFINGERMANAGER_H__
