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
	

protected:
	ArchBlobManager* blobManager;
private:
	ArchFingerManager( const ArchFingerManager &c );
	ArchFingerManager& operator=( const ArchFingerManager &c );
	
	ArchFinger fingerPool[MAX_FINGERS]; //memory for holding the fingers
	
	ArchFinger* activeFingersLL;
	uint8_t numActiveFingers;
	ArchFinger* lastActiveFinger;
	
	ArchFinger* inActiveFingersLL;
	uint8_t numInActiveFingers;
	ArchFinger* lastInActiveFinger;
	
	
	
	ArchFingerBlobConnection connectionLinks[MAX_FINGERS*MAX_BLOBS];

}; //ArchFingerManager

#endif //__ARCHFINGERMANAGER_H__
