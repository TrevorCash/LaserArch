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

	ArchFingerBlobConnection combs[MAX_FINGERS*MAX_BLOBS];

	//make all combinations...
	int f;
	int i = 0;
	for(f = 0; f < MAX_FINGERS; f++)
	{
		int b;
		for(b = 0; b < numBlobs; b++)
		{
			
			combs[i]->distance = abs(fingerPool[f].centerTime - blobManager->lastBlobsArray[b].midTime)/float(fingerPool[f].validity);
			combs[i]->pBlob = &blobManager->lastBlobsArray[b];
			combs[i]->pFinger = &fingerPool[f];
			i++;	
		}
	}
	
	//sort the connections.
	quick_sort_fingerCon(combs,i+1);
	
	
	ArchFingerBlobConnection usedList[MAX_FINGERS*MAX_BLOBS];//plenty big..
	int usedIdx = 0;
	int j;
	for(j = 0; j < (i+1); j++)
	{
		int h;
		boolean used = false;
		for(h = 0; h < (usedIdx+1); h++)
		{
			if((usedList[h]->pBlob || usedList->pFinger))
			{
				used = true;
			}
			
		}
		
		if(!used)
		{
			usedList[usedIdx] = combs[j];
			
			usedList[usedIdx]->pFinger.Validate(usedList[usedIdx]->pBlob.midTime, usedList[usedIdx]->pBlob.widthTime);
			if(usedList[usedIdx]->pFinger.IsFullyValid())
				noteManager->OnFingerStart(usedList[usedIdx]->pFinger);
		}
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

