/* 
* ArchRegionManager.h
*
* Created: 3/31/2015 11:08:20 AM
* Author: 7002815
*/


#ifndef __ARCHREGIONMANAGER_H__
#define __ARCHREGIONMANAGER_H__

#include "ArchRegion.h"
#include "PrimaryDefines.h"

class ArchRegionManager
{
//variables
public:
protected:
private:

//functions
public:
	ArchRegionManager(float minDeg, float maxDeg);
	~ArchRegionManager();
	
	float minDeg;
	float maxDeg;
	
	//Initializes initially to a "checkerboard state" with some preset colors and behalviors.
	void Initialize(uint8_t numRegions, float startDeg, float endDeg);
	
	
protected:
private:
	
	ArchRegion regionPool[MAX_REGIONS];

}; //ArchRegionManager

#endif //__ARCHREGIONMANAGER_H__
