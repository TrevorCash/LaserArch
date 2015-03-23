/* 
* ArchBlobManager.h
*
* Created: 2/20/2015 10:31:22 AM
* Author: 7002815
*/


#ifndef __ArchBlobManager_H__
#define __ArchBlobManager_H__


#include "ArchMotor.h"
#include "ArchRawBlob.h"
#include "PrimaryDefines.h"



class ArchBlobManager
{
//variables
public:
protected:
private:

//functions
public:
	ArchBlobManager(ArchMotor* pMotor);
	~ArchBlobManager();
	
	//main loop update - call at least at 60hz ish.
	void Update();
	
	void OnNoteInterupt(uint32_t currentTimerTime, boolean rising);
	void OnSyncInterupt(uint32_t currentTimerTime);
	
	uint32_t CurrentNumberOfBlobs()
	{
		return blobsArrayCurIndx + 1;
	}
	
	
	
public:
	ArchMotor* pMotor;
	ArchRawBlob blobsArray[MAX_BLOBS];
	ArchRawBlob lastBlobsArray[MAX_BLOBS];//final array that is refreshed on sync time.
	uint8_t blobsArrayCurIndx;
	uint8_t blobsArrayCurSize;
	uint8_t blobsArrayLastCycleSize;//size of the final array last cycle.
	boolean currentlyMidBlob;
}; //ArchBlobManager

#endif //__ArchBlobManager_H__
