/* 
* ArchFingerManager.cpp
*
* Created: 3/23/2015 5:34:21 PM
* Author: 7002815
*/


#include "ArchFingerManager.h"
#include "ArchRawBlob.h"
#include "ArchFingerBlobConnection.h"
#include "ArchMath.h"

// default constructor
ArchFingerManager::ArchFingerManager(ArchBlobManager* blobManager)
{
	this->blobManager = blobManager;
	
	numActiveFingers = 0;
} //ArchFingerManager

// default destructor
ArchFingerManager::~ArchFingerManager()
{
} //~ArchFingerManager


void ArchFingerManager::Update()
{
	//as long as we are referencing the blobs we want to "lock them" so they dont change midway through 
	//due to intterupts!
	blobManager->LockLastBlobArray();
	
	uint8_t numBlobs = blobManager->blobsArrayLastCycleSize;
	
	
	
	
	
	
	blobManager->UnLockLastBlobArray();
}


int32_t ArchFingerManager::findUnactiveFinger()
{
		int s;
		for(s = 0; s < MAX_FINGERS; s++)
		{
			if(!fingerPool[s].isActive)
				return s;
		}
		return -1;
}

int32_t ArchFingerManager::findActiveFinger()
{
		int s;
		for(s = 0; s < MAX_FINGERS; s++)
		{
			if(fingerPool[s].isActive)
			return s;
		}
		return -1;
}


void ArchFingerManager::OnFingerMoveX(uint32_t oldPos, uint32_t newPos, ArchFinger* finger)
{
	//notify NoteManager appropriatly
}
void ArchFingerManager::OnFingerMoveY(uint32_t oldWidth, uint32_t newWidth, ArchFinger* finger)
{
	//notify NoteManager appropriatly
}
