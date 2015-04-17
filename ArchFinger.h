/* 
* ArchFinger.h
*
* Created: 3/23/2015 5:43:11 PM
* Author: 7002815
*/


#ifndef __ARCHFINGER_H__
#define __ARCHFINGER_H__

#include "Arduino.h"
#include "ArchRegion.h"

class ArchFinger
{
//variables
public:
protected:
private:

//functions
public:
	ArchFinger();
	~ArchFinger();
	
	
	//low level, these are updated as often as the finger manager can update them.
	uint32_t centerTime; //center of the finger in time
	uint32_t timeWidth;//width of the finger in time
	
	uint32_t StartTime(){return (centerTime - timeWidth/2);}
	uint32_t EndTime(){return (centerTime + timeWidth/2);}
	
	uint32_t centerTimePrev;//center time previous 
	uint32_t timeWidthPrev;//width time previous
			
	ArchRegion* curRegion;
	ArchRegion* lastRegion;
		
	uint32_t initialCenterTime;//center time when the finger was first "started"
	uint32_t initialTimeWidth;//width time when the finger was first "started"
	

	//returns deltas from initial start action.
	int32_t deltaTimeFromStart(){return int32_t(centerTime - initialCenterTime);}
	int32_t deltaTimeWidthFromStart(){return int32_t(timeWidth - initialTimeWidth);}
	
	

	
	int32_t validity;
	
	boolean hasStarted;//
	
	boolean isUsed;
	
protected:
private:
	ArchFinger( const ArchFinger &c );
	ArchFinger& operator=( const ArchFinger &c );

}; //ArchFinger

#endif //__ARCHFINGER_H__
