/* 
* ArchNoteRegionManager.cpp
*
* Created: 2/20/2015 10:31:22 AM
* Author: 7002815
*/


#include "ArchNoteRegionManager.h"

// default constructor
ArchNoteRegionManager::ArchNoteRegionManager(ArchMotor* pMotor)
{
	this->pMotor = pMotor;
	blobsArrayCurIndx = 0;
	currentlyMidBlob = false;
} //ArchNoteRegionManager

// default destructor
ArchNoteRegionManager::~ArchNoteRegionManager()
{
} //~ArchNoteRegionManager


void ArchNoteRegionManager::Update()
{
	//compare persistant fingers with blobs and update accouringly.
}





//called when there is a rising or falling edge out of the note comparitor.
//KEEP AS SHORT AS POSSIBLE! - its in an interupt!
void ArchNoteRegionManager::OnNoteInterupt(uint32_t currentTimerTime, boolean rising)
{
	ArchRawBlob blob;
	blobsArray[blobsArrayCurIndx] = blob;
	if(rising)
	{
		currentlyMidBlob = true;
		blobsArray[blobsArrayCurIndx].Begin(currentTimerTime);
	}
	else if(!rising && currentlyMidBlob)// if falling
	{
		//end the current blob, and increment counter.
		blobsArray[blobsArrayCurIndx].End(currentTimerTime);
		blobsArrayCurIndx++;
		if(blobsArrayCurIndx >= MAX_BLOBS)
			blobsArrayCurIndx = 0;
	}
}

void ArchNoteRegionManager::OnSyncInterupt(uint32_t currentTimerTime)
{
	//Serial.println(blobsArrayCurIndx + 1);
	
	//when we have a sync event we want to effectively clear out all current blobs (do this by resetting the counter)
	blobsArrayCurIndx = 0;
	
}