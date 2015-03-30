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
	
	connectedSize = 0;
	unConnectedSize = MAX_BLOBS*MAX_FINGERS;
} //ArchFingerManager

// default destructor
ArchFingerManager::~ArchFingerManager()
{
} //~ArchFingerManager


void ArchFingerManager::Update()
{
	blobManager->LockLastBlobArray();
	
	
	//for each FINGER
		//make table of distances to each blob. with reference to the blob paired with the distance.
	
	
	//compare the currently active "blobs" with currently active "fingers"
	uint8_t b;
	for(b = 0; b < blobManager->blobsArrayLastCycleSize; b++)
	{
		int f;
		for(f = 0; f < MAX_FINGERS; f++)	
		{ 
			if(fingerPool[f].isActive)
			{
				connectionLinks[b*f].distance = abs(fingerPool[f].centerTime - blobManager->lastBlobsArray[b].midTime);
				connectionLinks[b*f].pBlob = &blobManager->lastBlobsArray[b];
				connectionLinks[b*f].pFinger = &fingerPool[f];
			}
		}
	}
	
	//sort the connections by distance for only the active connections
	quick_sort_fingerCon(connectionLinks,blobManager->blobsArrayLastCycleSize*connectedSize);
	
	//since the list is sorted the lowest distances are on the top and we can move the fingers to their closest blob instantly!
	int i;
	for(i = 0; i < blobManager->blobsArrayLastCycleSize*numActiveFingers; i++)
	{
		connectionLinks[i].pFinger->centerTime = connectionLinks[i].pBlob->midTime;
		connectionLinks[i].pFinger->timeWidth = connectionLinks[i].pBlob->widthTime;
		
		//MOVEMENT NOTIFICATION TO OTHER SUBSYSTEMS HERE!
		
		
		if(i > (blobManager->blobsArrayLastCycleSize - 1))
		{
			//remove this finger from active list
			ArchFinger* problemFinger = connectionLinks[i]->pFinger;
			
			//add to inactive list
			lastInActiveFinger->nextFinger = problemFinger;
			lastInActiveFinger = problemFinger;
			numInActiveFingers++;
			
			//remove from active list
			lastActiveFinger = problemFinger->nextFinger;
			problemFinger->prevFinger.nextFinger = problemFinger->nextFinger;
			numActiveFingers--;
		}
		else if(i > (numActiveFingers - 1))
		{
			//add finger to active list
			ArchFinger* newFinger = lastInActiveFinger;
			
			lastInActiveFinger = lastActiveFinger->prevFinger;
			
			
		}
	}
	
	
	
	
	//print for testing...
	int f;
	//Serial.println("Finger centers:");
	for(f = 0; f < numActiveFingers; f++)
	{
		Serial.print("Finger: ");
		Serial.println(f);
		Serial.println(fingerPool[f].centerTime);
	}
	
	
	
	
	*/
	
	
	
	blobManager->UnLockLastBlobArray();
}




void ArchFingerManager::OnFingerMoveX(uint32_t oldPos, uint32_t newPos, ArchFinger* finger)
{
	//notify NoteManager appropriatly
}
void ArchFingerManager::OnFingerMoveY(uint32_t oldWidth, uint32_t newWidth, ArchFinger* finger)
{
	//notify NoteManager appropriatly
}
