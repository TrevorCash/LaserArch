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
//enums
public:
	enum RegionModifyMethod
	{
		RegionSingle,
		RegionShift,
		RegionLinearStretch	
	};	
	
	
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
	
	//modifies a regions span, using the given modify method.  returns success (may fail if using shift method)(failure will still move regions, but may remove clipped parts).
	boolean ModifyRegionSpan(ArchRegion* region, float newStartDeg, float newEndDeg, RegionModifyMethod method);
	
	boolean ModifyRegionStart(ArchRegion* region, float newStartDeg, RegionModifyMethod method);
	boolean ModifyRegionEnd(ArchRegion* region, float newEndDeg, RegionModifyMethod method);
	
	
	
	//use to access region list. (user must use pointer loop)
	ArchRegion* RegionList(){return regionListFirst;}
		
	//returns the region that contains the given angle, returns NULL if no region is found.	
	ArchRegion* FindRegionAtAngle(float angle);
	
	void PrintRegionInfo();
	
	
protected:
private:
	ArchRegion* regionListFirst;
	uint32_t numRegions;
	ArchRegion regionPool[MAX_REGIONS];
	
	ArchRegion* FindUnValidRegion();

}; //ArchRegionManager

#endif //__ARCHREGIONMANAGER_H__
