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
} //ArchRegionManager

// default destructor
ArchRegionManager::~ArchRegionManager()
{
} //~ArchRegionManager


void ArchRegionManager::Initialize(uint8_t numRegions, float startDeg, float endDeg)
{
	int i;
	float regionWidth = (endDeg - startDeg)/numRegions;
	ArchRegion* prevRegion = NULL;
	for(i = 0; i < numRegions; i++)
	{
		ArchRegion* newRegion = FindUnValidRegion();
		
		if(prevRegion == NULL)
			regionListFirst = newRegion;
			
		newRegion->IsValid = true;
		
		if(prevRegion)
			prevRegion->nextRegion = newRegion;
		
		newRegion->prevRegion = prevRegion;
		prevRegion = newRegion;
	
		newRegion->UpdateSpan(startDeg+(i*regionWidth), startDeg+((i+1)*regionWidth));
		if(i%2)
		{
			newRegion->UpdateColors(0,128,0);
		}
		else
		{
			newRegion->UpdateColors(0,0,128);
		}
	}
	
	
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