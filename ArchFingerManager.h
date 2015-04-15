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
	uint16_t numActiveFingers;

	void Update();//called from main loop;

protected:
	ArchBlobManager* blobManager;
	ArchNoteManager* noteManager;
private:
	ArchFinger fingerPool[MAX_FINGERS]; //memory for holding the fingers
	
	
	ArchFingerBlobConnection connectionLinks[MAX_BLOBS*MAX_FINGERS];
	uint16_t connectionLinksCurIdx;
	
	uint32_t BlobFingerDist(ArchRawBlob* blob, ArchFinger* finger)
	{
		return abs(blob->midTime - finger->centerTime);
	}

}; //ArchFingerManager

#endif //__ARCHFINGERMANAGER_H__
