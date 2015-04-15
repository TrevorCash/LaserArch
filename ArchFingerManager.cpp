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
ArchFingerManager::ArchFingerManager(ArchBlobManager* blobManager, ArchNoteManager* noteManager)
{
	this->blobManager = blobManager;
	this->noteManager = noteManager;
	
	numActiveFingers = 0;
	connectionLinksCurIdx = 0;
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
			
			uint32_t dist = abs(bp->midTime - fp->centerTime);	
			
			connectionLinks[connectionLinksCurIdx].pBlob = bp;
			connectionLinks[connectionLinksCurIdx].pFinger= fp;
			connectionLinks[connectionLinksCurIdx].distance = dist;
			connectionLinksCurIdx++;
			
		}
	}
	
	//Sort the connections List by distance
	quick_sort_fingerCon(connectionLinks, connectionLinksCurIdx);
	
	
	int c;
	for(c = 0; c < connectionLinksCurIdx; c++)
	{
		ArchFingerBlobConnection* cp = &connectionLinks[c];
		
		if(cp->pFinger->isUsed || cp->pBlob->isUsed)
			continue;
			
		cp->pFinger->isUsed = true;
		cp->pBlob->isUsed = true;
		
		cp->pFinger->centerTime = cp->pBlob->midTime;
		cp->pFinger->timeWidth = cp->pBlob->widthTime;
		
		//call manager callbacks...
		noteManager->OnFingerMove(cp->pFinger);
	
		cp->pFinger->centerTimePrev = cp->pFinger->centerTime;
		cp->pFinger->timeWidthPrev = cp->pFinger->timeWidth;
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
					fingerPool[f].hasStarted = true;
					noteManager->OnFingerStart(&fingerPool[f]);
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
					fingerPool[f].hasStarted = false;
					noteManager->OnFingerStop(&fingerPool[f]);	
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



