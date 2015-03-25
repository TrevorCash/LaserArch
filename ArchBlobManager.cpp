/* 
* ArchBlobManager.cpp
*
* Created: 2/20/2015 10:31:22 AM
* Author: 7002815
*/


#include "ArchBlobManager.h"

// default constructor
ArchBlobManager::ArchBlobManager(ArchMotor* pMotor)
{
	this->pMotor = pMotor;
	blobsArrayCurIndx = 0;
	blobsArrayCurSize = 0;
	blobsArrayLastCycleSize = 0;
	
	currentlyMidBlob = false;
	
	lastBlobArrayBlocking = false;
} //ArchBlobManager

// default destructor
ArchBlobManager::~ArchBlobManager()
{
} //~ArchBlobManager


void ArchBlobManager::Update()
{
	//compare persistant fingers with blobs and update accouringly.
}


void ArchBlobManager::LockLastBlobArray()
{
	lastBlobArrayBlocking = true;
}
void ArchBlobManager::UnLockLastBlobArray()
{
	lastBlobArrayBlocking = false;
}
boolean ArchBlobManager::IsLastBlobArrayLocked()
{
	return lastBlobArrayBlocking;
}



//called when there is a rising or falling edge out of the note comparitor.
//KEEP AS SHORT AS POSSIBLE! - its in an interupt!
void ArchBlobManager::OnNoteInterupt(uint32_t currentTimerTime, boolean rising)
{	
	//ignore activity outside of rejection
	if(currentTimerTime < pMotor->TicksFromAngleAve(REJECTION_ANGLE_MIN_DEGREES))
		return;
	if(currentTimerTime > pMotor->TicksFromAngleAve(REJECTION_ANGLE_MAX_DEGREES))
		return;
	
	//
	
	if(rising)
	{
		currentlyMidBlob = true;
		ArchRawBlob blob;
		blobsArray[blobsArrayCurIndx] = blob;
		blobsArray[blobsArrayCurIndx].Begin(currentTimerTime);
	}
	else if(!rising && currentlyMidBlob)// if falling
	{
		//end the current blob, and increment counter.
		blobsArray[blobsArrayCurIndx].End(currentTimerTime);
		blobsArrayCurIndx++;
		blobsArrayCurSize++;
		if(blobsArrayCurIndx >= MAX_BLOBS)
		{
			blobsArrayCurIndx = MAX_BLOBS - 1;
			blobsArrayCurSize = MAX_BLOBS;
		}
		currentlyMidBlob = false;
	}
}

void ArchBlobManager::OnSyncInterupt(uint32_t currentTimerTime)
{
	//save the current blobs into the "lastBlobArray" which is a buffer for holding the values 
	//of all the blobs last cycle - this should be used by any process in the mainloop program flow as
	//it is not continually changing. - this only updates if it ISNT LOCKED.  
	if(!lastBlobArrayBlocking)
	{
		blobsArrayLastCycleSize = blobsArrayCurSize;
		int i;
		for(i = 0; i < blobsArrayCurSize; i++)
		{
			lastBlobsArray[i] = blobsArray[i];
		}
	}
	
	
	//when we have a sync event we want to effectively clear out all current blobs (do this by resetting the counter)
	blobsArrayCurIndx = 0;
	blobsArrayCurSize = 0;
	currentlyMidBlob = false;
}