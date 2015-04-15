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

class ArchFingerManager
{

//functions
public:
	ArchFingerManager(ArchBlobManager* blobManager, ArchNoteManager* noteManager, ArchRegionManager* regionManager);
	~ArchFingerManager();
	uint16_t numActiveFingers;
	boolean printFingerEvents;

	void Update();//called from main loop;

protected:
	ArchBlobManager* blobManager;
	ArchNoteManager* noteManager;
	ArchRegionManager* regionManager;
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
