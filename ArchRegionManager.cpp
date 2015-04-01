/* 
* ArchRegionManager.cpp
*
* Created: 3/31/2015 11:08:20 AM
* Author: 7002815
*/


#include "ArchRegionManager.h"

// default constructor
ArchRegionManager::ArchRegionManager(float minDeg, float maxDeg)
{
	this->minDeg = minDeg;
	this->maxDeg = maxDeg;
	
	regionListFirst = NULL;
	numRegions = 0;
} //ArchRegionManager

// default destructor
ArchRegionManager::~ArchRegionManager()
{
} //~ArchRegionManager


void ArchRegionManager::Initialize(uint8_t numRegions, float startDeg, float endDeg)
{
	int i;
	this->numRegions = numRegions;
	float regionWidth = (endDeg - startDeg)/numRegions;
	ArchRegion* prevRegion = NULL;
	for(i = 0; i < numRegions; i++)
	{
		ArchRegion* newRegion = FindUnValidRegion();
		
		if(prevRegion == NULL)
			regionListFirst = newRegion;
			
		newRegion->IsValid = true;
		newRegion->index = i;
		
		if(prevRegion)
			prevRegion->nextRegion = newRegion;
		
		newRegion->prevRegion = prevRegion;
		prevRegion = newRegion;
	
		newRegion->UpdateSpan(startDeg+(i*regionWidth), startDeg+((i+1)*regionWidth));
		if(i%2)
		{
			newRegion->UpdateColors(0,32,0);
		}
		else
		{
			newRegion->UpdateColors(0,0,32);
		}
	}
	
	
}



boolean ArchRegionManager::ModifyRegionSpan(ArchRegion* region, float newStartDeg, float newEndDeg, RegionModifyMethod method)
{
	if(region == NULL)
		return false;
		
	
	if(newStartDeg == region->startDeg && newEndDeg == region->endDeg)
		return true;


	float startDelta = newStartDeg - region->startDeg;
	float endDelta = newEndDeg - region->endDeg;
	
	
	uint8_t numDownwardRegions = numRegions - region->index; 
	float downwardDelta = startDelta/numDownwardRegions;
	
	if(method == RegionLinearStretch)
	{
		//handle regions of lesser degrees (downward)
		if(region->prevRegion)
		{
			Serial.println("A");
			region->startDeg = newStartDeg;
			region->prevRegion->endDeg = newStartDeg;
			
			ArchRegion* curRegion = region->prevRegion;
			while(curRegion)
			{
				Serial.println("B");
				if(curRegion->index != 0)
				{
					Serial.println("C");
					curRegion->startDeg += downwardDelta;
				}
				if(curRegion->prevRegion)
				{
					Serial.println("D");
					curRegion->prevRegion->endDeg = curRegion->startDeg;
				}
				curRegion = curRegion->prevRegion;
			}
		
		}
		
			
	}
	else if(method == RegionShift)
	{
		//Not Implemented	
	}
	
	
	
	return true;
}






ArchRegion* ArchRegionManager::FindUnValidRegion()
{
	int r;
	for(r = 0; r < MAX_REGIONS; r++)
	{
		if(!regionPool[r].IsValid)
			return &regionPool[r];
	}
	
	return NULL;
}

ArchRegion* ArchRegionManager::FindRegionAtAngle(float angle)
{
	ArchRegion* curRegion = regionListFirst;
	while(curRegion != NULL)
	{
		//Serial.println(curRegion->startDeg);
		if(angle < curRegion->endDeg && angle >= curRegion->startDeg)
		{
			return curRegion;
		}
		curRegion = curRegion->nextRegion;
	}
	
	return NULL;
}