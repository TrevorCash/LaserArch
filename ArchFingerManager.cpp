/* 
* ArchFingerManager.cpp
*
* Created: 3/23/2015 5:34:21 PM
* Author: 7002815
*/


#include "ArchFingerManager.h"
#include "ArchRawBlob.h"

// default constructor
ArchFingerManager::ArchFingerManager(ArchBlobManager* blobManager)
{
	this->blobManager = blobManager;
	ActiveFingers = NULL;
	LastActiveFinger = NULL;
} //ArchFingerManager

// default destructor
ArchFingerManager::~ArchFingerManager()
{
} //~ArchFingerManager


void ArchFingerManager::Update()
{
	int b;
	ArchFinger* activeFinger;
	for(b = 0; b < blobManager->blobsArrayLastCycleSize; b++)
	{
		uint32_t closestTime = 99999999;
		ArchFinger* closestFinger = NULL;
		for(activeFinger = ActiveFingers; activeFinger != NULL; activeFinger = activeFinger->nextFinger)
		{
			uint32_t dist = abs(blobManager->blobsArrayLastCycleSize[b].midTime - activeFinger->centerTime);
			if( dist < closestTime && (blobManager->lastBlobsArray[b].closestFinger == NULL))
			{
				closestTime = dist;
				closestFinger = activeFinger;
				blobManager->lastBlobsArray[b].closestFinger = activeFinger;
				
			}
		}
		//if we havnt been able to link with the closest finger.
		if(closestFinger == NULL)
		{
			
		}
	}
}