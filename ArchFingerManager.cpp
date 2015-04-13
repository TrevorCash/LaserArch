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
	
	fingerPool[0].validity = MAX_FINGER_VALIDITY;
	
	connectionLinksSize = 0;
} //ArchFingerManager

// default destructor
ArchFingerManager::~ArchFingerManager()
{
} //~ArchFingerManager


void ArchFingerManager::Update()
{
	
	//if(blobManager->IsLastBlobArrayUsed())
	//{
	//	return;
	//}
	//blobManager->UseLastBlobArray();
	
	//as long as we are referencing the blobs we want to "lock them" so they dont change midway through 
	//due to interupts!
	blobManager->LockLastBlobArray();
	
	connectionLinksSize = 0;
	
	
	int b1;
	ArchRawBlob* b1p = NULL;
	for(b1 = 0; b1 < blobManager->blobsArrayLastCycleSize; b1++)
	{
		b1p = &blobManager->lastBlobsArray[b1];
		int f1;
		ArchFinger* f1p = NULL;
		int f1_from_b1_closest = -1;
		uint32_t b1_f1_minDist = 0xFFFFFFFF;
		for(f1 = 0; f1 < MAX_FINGERS; f1++)
		{
				f1p = &fingerPool[f1];
				
				if(f1p->validity < FINGER_VALIDITY_THRESH)
					continue;
				
				
				//make sure the finger isnt already connected!
				int k;
				for(k = 0; k < connectionLinksSize; k++)
				{
					if(connectionLinks[k].pFinger == f1p)
					{
						k = -1;
						break;
					}
				}
				if(k == -1)
					continue;
					
					
				
				uint32_t dist = BlobFingerDist(b1p,f1p);
				if(dist < b1_f1_minDist)
				{
					f1_from_b1_closest = f1;
					b1_f1_minDist = dist;
				}
		}
		if(f1_from_b1_closest >= 0)
		{
			ArchFinger* f1_from_b1_closestp = &fingerPool[f1_from_b1_closest];
			f1_from_b1_closestp->centerTime = b1p->midTime;
			f1_from_b1_closestp->timeWidth = b1p->widthTime;
			connectionLinks[connectionLinksSize].distance = b1_f1_minDist;
			connectionLinks[connectionLinksSize].pBlob = b1p;
			connectionLinks[connectionLinksSize].pFinger = f1_from_b1_closestp;
			connectionLinksSize++;
			noteManager->OnFingerMove(f1_from_b1_closestp);
		}
	}
	
	
	
	blobManager->UnLockLastBlobArray();
}



