/* 
* ArchRawBlob.h
*
* Created: 3/23/2015 8:50:48 AM
* Author: 7002815
*/


#ifndef __ARCHRAWBLOB_H__
#define __ARCHRAWBLOB_H__

#include "Arduino.h"
#include "ArchFinger.h"

//ArchRawBlob represents a single blob (or finger) in the arch space..
class ArchRawBlob
{
	//variables
	public:


	ArchRawBlob();
	~ArchRawBlob();
	boolean IsValid()
	{
		if(endTime == 0 || startTime == 0)
			return false;
		
		return true;
	}
	void Begin(uint32_t startSyncTimerTime)
	{
		startTime = startSyncTimerTime;
		
	}
	void End(uint32_t endSyncTimerTime)
	{
		endTime = endSyncTimerTime;
		midTime = (endTime + startTime)*0.5;
		widthTime = startTime - endTime;
	}
public:
	uint32_t startTime;
	uint32_t endTime;
	//calculatables based on startTime and endTime;
	uint32_t midTime;
	uint32_t widthTime;
	
	ArchFinger* closestFinger;

}; //ArchRawBlob

#endif //__ARCHRAWBLOB_H__
