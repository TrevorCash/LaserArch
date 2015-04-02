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
	ArchFingerManager(ArchBlobManager* blobManager, ArchNoteManager* noteManager);
	~ArchFingerManager();

	void Update();//called from main loop;
	
	
	void OnFingerMove(uint32_t oldStart, uint32_t oldEnd, ArchFinger* finger);


protected:
	ArchBlobManager* blobManager;
	ArchNoteManager* noteManager;
private:
	ArchFinger fingerPool[MAX_FINGERS]; //memory for holding the fingers
	
	ArchFingerBlobConnection connectionLinks[MAX_BLOBS*MAX_FINGERS];
	
	uint8_t numActiveFingers;
	
	int32_t findUnValidFinger();
	int32_t findValidFinger();
	

}; //ArchFingerManager

#endif //__ARCHFINGERMANAGER_H__
