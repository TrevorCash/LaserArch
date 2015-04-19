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
#include "ArchMotor.h"
#include "ArchRegionScheme.h"

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
	

//functions
public:
	ArchRegionManager(float minDeg, float maxDeg, ArchMotor* motor);
	~ArchRegionManager();
	
	float minDeg;
	float maxDeg;
	
	//Initializes all regions based off the region scheme
	void Initialize(ArchRegionScheme& regionScheme);
	
	//modifies a regions span, using the given modify method to effect surrounding regions.  
	//returns success (may fail if using shift method)(failure will still move regions, but may remove clipped parts).
	boolean ModifyRegionSpan(ArchRegion* region, float newStartDeg, float newEndDeg, RegionModifyMethod method);
	
	//returns number of active regions
	uint16_t NumRegions(){return numRegions;}

	//returns the first region
	ArchRegion* FirstRegion(){return regionListFirst;}
		
	//returns the last region (O(n))
	ArchRegion* LastRegion(){return FindRegionById(numRegions - 1);}
	

	//use to access region list. (user must use pointer loop)
	ArchRegion* RegionList(){return regionListFirst;}
		
	//returns the region that contains the given angle, returns NULL if no region is found.	
	ArchRegion* FindRegionAtAngle(float angle);
	
	ArchRegion* FindRegionAtTick(uint32_t tick)
	{ 
		return FindRegionAtAngle(motor->AngleFromTicksLast(tick));
	}
	
	//returns the region with the specified id, the first region is id 0 (O(id))
	ArchRegion* FindRegionById(uint16_t id);
	
	//removed a region from the linked list, returns success.
	boolean RemoveRegion(ArchRegion* region);
	
	//cleans up all regions with a zero width...
	boolean CleanupZeroRegions();
	
	
	//prints the info of all regions.
	void PrintRegionInfo();
	
	
protected:
private:
	ArchRegion* regionListFirst;
	uint32_t numRegions;
	ArchRegion regionPool[MAX_REGIONS];
	
	ArchMotor* motor;
	
	ArchRegion* FindUnValidRegion();
	void ClearAllRegions();
	boolean ModifyRegionStart(ArchRegion* region, float newStartDeg, RegionModifyMethod method);
	boolean ModifyRegionEnd(ArchRegion* region, float newEndDeg, RegionModifyMethod method);
		

}; //ArchRegionManager

#endif //__ARCHREGIONMANAGER_H__
