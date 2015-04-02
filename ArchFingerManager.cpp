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
	//due to intterupts!
	blobManager->LockLastBlobArray();
	
	uint8_t numBlobs = blobManager->blobsArrayLastCycleSize;

	int f;
	uint32_t minDist = 0xFFFFFFFF;
	ArchRawBlob* minBlob = NULL;
	for(f = 0; f < MAX_FINGERS; f++)
	{
		if(!fingerPool[f].IsFullyValid()) continue;
		
		minDist = 0xFFFFFFFF;
		minBlob = NULL;
		
		int b;
		for(b = 0; b < numBlobs; b++)
		{
			if(blobManager->lastBlobsArray[b].closestFinger != NULL)
			{
				continue;
			}
			
			uint32_t dist = abs(blobManager->lastBlobsArray[b].midTime - fingerPool[f].centerTime);
			if(dist < minDist)
			{
				minDist = dist;
				minBlob = &blobManager->lastBlobsArray[b];
			}	
		}
		//Serial.print("F:"); Serial.println(f);
		//Serial.println((int)minBlob);
		
		if(minBlob != NULL)
		{
			////move finger.
			fingerPool[f].Validate(minBlob->midTime,minBlob->widthTime);
			noteManager->OnFingerMove(&fingerPool[f]);
			minBlob->closestFinger = &fingerPool[f];
		}
		else
		{
			fingerPool[f].DeValidate();
			if(!fingerPool[f].IsFullyValid())
			{
				noteManager->OnFingerStop(&fingerPool[f]);
			}
		}
	}
	
	int b;
	for(b = 0; b < numBlobs; b++)
	{
		if(blobManager->lastBlobsArray[b].closestFinger) 
			continue;
		
		int32_t f = findUnValidFinger();
		if(f >= 0 )
		{
			//turn finger on!
			fingerPool[f].SuperValidate(blobManager->lastBlobsArray[b].midTime, blobManager->lastBlobsArray[b].widthTime);
			noteManager->OnFingerStart(&fingerPool[f]);
			
			blobManager->lastBlobsArray[b].closestFinger = &fingerPool[f];
		}
		else
			break;
		
	}
	

	
	blobManager->UnLockLastBlobArray();
}


int32_t ArchFingerManager::findUnValidFinger()
{
		int s;
		for(s = 0; s < MAX_FINGERS; s++)
		{
			if(!fingerPool[s].IsFullyValid())
				return s;
		}
		return -1;
}

int32_t ArchFingerManager::findValidFinger()
{
		int s;
		for(s = 0; s < MAX_FINGERS; s++)
		{
			if(fingerPool[s].IsFullyValid())
			return s;
		}
		return -1;
}

