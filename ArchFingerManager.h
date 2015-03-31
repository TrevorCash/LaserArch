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


class ArchFingerManager
{

//functions
public:
	ArchFingerManager(ArchBlobManager* blobManager);
	~ArchFingerManager();

	void Update();//called from main loop;
	
	
	void OnFingerMoveX(uint32_t oldPos, uint32_t newPos, ArchFinger* finger);
	void OnFingerMoveY(uint32_t oldWidth, uint32_t newWidth, ArchFinger* finger);
	

protected:
	ArchBlobManager* blobManager;
private:
	ArchFingerManager( const ArchFingerManager &c );
	ArchFingerManager& operator=( const ArchFingerManager &c );
	
	ArchFinger fingerPool[MAX_FINGERS]; //memory for holding the fingers
	
	ArchFingerBlobConnection connectionLinks[MAX_BLOBS*MAX_FINGERS];
	
	uint8_t numActiveFingers;
	
	int32_t findUnValidFinger();
	int32_t findValidFinger();
	

}; //ArchFingerManager

#endif //__ARCHFINGERMANAGER_H__
