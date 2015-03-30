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
	blobManager->LockLastBlobArray();
	
	uint8_t numBlobs = blobManager->blobsArrayLastCycleSize;
	
	//for each FINGER
		//make table of distances to each blob. with reference to the blob paired with the distance.
	
	
	//compare the currently active "blobs" with currently active "fingers"
	uint8_t b;
	for(b = 0; b < numBlobs; b++)
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
	blobManager->UnLockLastBlobArray();

	Serial.println("mark a");
	//sort the connections by distance for only the active connections
	quick_sort_fingerCon(connectionLinks,numBlobs*numActiveFingers);
	
	Serial.println("mark b");
	//now that the existing connections are sorted, snap the active fingers to their new positions and invoke callbacks etc.
	int c;
	for(c = 0; c < numActiveFingers; c++)
	{
		connectionLinks[c].pFinger->centerTime = connectionLinks[c].pBlob->midTime;
	}
	
	
	//now evalute wether to make new fingers or delete finger.
	while(numBlobs != numActiveFingers)
	{
		Serial.println(numBlobs);
		Serial.println(numActiveFingers);
		if(numBlobs > numActiveFingers)
		{
			//add a finger.
		
			//find a free finger
			int32_t fingerIdx = findUnactiveFinger();
			if(fingerIdx >= 0)
			{
				fingerPool[fingerIdx].isActive = true;
				numActiveFingers++;
			}
			else
				break;
		
		
		}
		else if(numBlobs < numActiveFingers)
		{
			//find a used finger
			int32_t fingerIdx = findActiveFinger();
			if(fingerIdx >= 0)
			{
				fingerPool[fingerIdx].isActive = false;
				numActiveFingers--;
			}
			else
				break;
		}
		//else were good!
	}
	
	
	
	//test printing.
	//int j = 0;
	//Serial.print("numBLobs: ");
	//Serial.println(numBlobs);
	//Serial.print("numActiveFIngers: ");
	//Serial.println(numActiveFingers);
	//for(j = 0; j < numActiveFingers; j++)
	//{
		//Serial.print("Finger: "); Serial.println(j);
		//Serial.println(fingerPool[j].centerTime);
		//Serial.println(fingerPool[j].isActive);
	//}
	
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
