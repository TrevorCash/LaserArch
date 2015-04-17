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
#include "ArchNoteManager.h"

// default constructor
ArchFingerManager::ArchFingerManager(ArchBlobManager* blobManager, ArchNoteManager* noteManager, ArchRegionManager* regionManager)
{
	this->blobManager = blobManager;
	this->noteManager = noteManager;
	this->regionManager = regionManager;
	
	numActiveFingers = 0;
	connectionLinksCurIdx = 0;
	
	
	printFingerEvents = false;
} //ArchFingerManager

// default destructor
ArchFingerManager::~ArchFingerManager()
{
} //~ArchFingerManager


void ArchFingerManager::Update()
{
	
	if(blobManager->IsLastBlobArrayUsed())
	{
		return;
	}
	blobManager->UseLastBlobArray();
	
	//as long as we are referencing the blobs we want to "lock them" so they dont change midway through 
	//due to interupts!
	blobManager->LockLastBlobArray();
	
	
	//prepare for the pass
	connectionLinksCurIdx = 0;
	int f;
	for(f = 0; f < MAX_FINGERS; f++)
	{
		fingerPool[f].isUsed = false;
	}
		
	
	
	
	
	//Setup Connections For This Pass
	int b;
	for(b = 0; b < blobManager->blobsArrayLastCycleSize; b++)
	{
		ArchRawBlob* bp = &blobManager->lastBlobsArray[b];
		bp->isUsed = false;
		int f;
		for(f = 0; f < MAX_FINGERS; f++)
		{
			ArchFinger* fp = &fingerPool[f];
			if(!fp->validity)
				continue;
			
			uint32_t dist = abs(int32_t(bp->midTime - fp->centerTime));	
			
			connectionLinks[connectionLinksCurIdx].pBlob = bp;
			connectionLinks[connectionLinksCurIdx].pFinger= fp;
			connectionLinks[connectionLinksCurIdx].distance = dist;
			connectionLinksCurIdx++;
			
		}
	}
	
	//Sort the connections List by distance
	quick_sort_fingerCon(connectionLinks, connectionLinksCurIdx);
	
	
	//print connection links for varification
	
	
	
	
	int c;
	//Serial.println("Printing Connections Found:");
	for(c = 0; c < connectionLinksCurIdx; c++)
	{
		ArchFingerBlobConnection* cp = &connectionLinks[c];
		
		//Serial.print(c);
		//Serial.print(" ");
		//Serial.print(cp->distance);
		//Serial.print(" ");
		//Serial.print(cp->pBlob->isUsed);
		//Serial.print(" ");
		//Serial.println(cp->pFinger->isUsed);

		
		if(cp->pFinger->isUsed || cp->pBlob->isUsed)
			continue;
			
		cp->pFinger->isUsed = true;
		cp->pBlob->isUsed = true;
		
		//move it!
		FingerMove(cp->pFinger, cp->pBlob);
	}
	
	
	//update validities of all fingers
	for(f = 0; f < MAX_FINGERS; f++)
	{
		if(fingerPool[f].isUsed)
		{
			fingerPool[f].validity++;
			
			if(fingerPool[f].validity == MAX_FINGER_VALIDITY)
			{
				//call manager callbacks for finger start
				if(!fingerPool[f].hasStarted)
				{
					FingerStart(&fingerPool[f]);
				}
						
			}
			else if(fingerPool[f].validity > MAX_FINGER_VALIDITY)
			{
				fingerPool[f].validity = MAX_FINGER_VALIDITY;
			}
		}
		else
		{
			fingerPool[f].validity--;
			if(fingerPool[f].validity == MIN_FINGER_VALIDITY)
			{
				numActiveFingers--;
				//call manager callbacks for finger stop
				if(fingerPool[f].hasStarted)
				{
					FingerStop(&fingerPool[f]);
				}
			}
			else if(fingerPool[f].validity < MIN_FINGER_VALIDITY)
			{
				fingerPool[f].validity = MIN_FINGER_VALIDITY;
			}
		}
	}
	
	//jump start new fingers if needed into positive validity
	if(numActiveFingers < blobManager->blobsArrayLastCycleSize)
	{
		int b;
		for(b = 0; b < blobManager->blobsArrayLastCycleSize; b++)
		{
			if(blobManager->lastBlobsArray[b].isUsed)
				continue;
			
			//look for non-active fingers in the the pool
			int f;
			for(f = 0; f < MAX_FINGERS; f++)
			{
				if(fingerPool[f].validity == 0)//we found one!
				{
					numActiveFingers++;
					fingerPool[f].validity = 1;
				
					//physically set the finger close the the blob so next pass he gets a good connection
					fingerPool[f].centerTime = blobManager->lastBlobsArray[b].midTime;
					fingerPool[f].timeWidth = blobManager->lastBlobsArray[b].widthTime;
					fingerPool[f].centerTimePrev = fingerPool[f].centerTime;
					fingerPool[f].timeWidthPrev = fingerPool[f].timeWidth;
					
					//for good measure
					fingerPool[f].isUsed = true;
					blobManager->lastBlobsArray[b].isUsed = true;
					
					break;
				
				}
			
			}	
		}
	}
	
	
	
	blobManager->UnLockLastBlobArray();
}



void ArchFingerManager::FingerStart(ArchFinger* finger)
{
	
	finger->hasStarted = true;
	
	//map the finger to it's starting region
	finger->curRegion = regionManager->FindRegionAtTick(finger->centerTime);
	finger->lastRegion = finger->curRegion;
	
	//increment the number of finger in the region
	finger->curRegion->fingerCount++;
	
	if(printFingerEvents)
	{
		Serial.print("FingerStart: ");
		Serial.println((int)finger);
	}
	
	noteManager->OnFingerStart(finger);
	
	
}
void ArchFingerManager::FingerMove(ArchFinger* finger, ArchRawBlob* blob)
{	
	
	finger->centerTimePrev = finger->centerTime;
	finger->timeWidthPrev = finger->timeWidth;
		
	finger->centerTime = blob->midTime;
	finger->timeWidth = blob->widthTime;
	
	if(finger->hasStarted)
	{
		

		//switch regions with some hysteresis(TODO)
		finger->lastRegion = finger->curRegion;
		finger->lastRegion->fingerCount--;
		finger->curRegion = regionManager->FindRegionAtTick(finger->centerTime);
		finger->curRegion->fingerCount++;

		//if(printFingerEvents)
		//{
			//Serial.print("FingerMove: ");
			//Serial.print((int)finger);
			//Serial.print(" to position: ");
			//Serial.println(finger->centerTime);
		//}
	
		//call manager callbacks...
		noteManager->OnFingerMove(finger);
	}
}
void ArchFingerManager::FingerStop(ArchFinger* finger)
{
	finger->hasStarted = false;

	if(printFingerEvents)
	{
		Serial.print("FingerStop: ");
		Serial.println((int)finger);
	}

	finger->curRegion->fingerCount--;
	
	noteManager->OnFingerStop(finger);
	
	finger->curRegion = NULL;

}