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
	
	
	return false;
}



boolean ArchRegionManager::ModifyRegionStart(ArchRegion* region, float newStartDeg, RegionModifyMethod method)
{
	if(region == NULL)
	return false;
	
	
	if(newStartDeg == region->startDeg)
		return true;
	
	//dont allow "flipping" of region.
	if(newStartDeg >= region->endDeg)
		return false;	
	
	//dont allow out of bounds
	if(newStartDeg < minDeg || newStartDeg > maxDeg)
		return false;


	//final - initial
	float startDelta = newStartDeg - region->startDeg;
	float oldStartDeg = region->startDeg;


	if(method == RegionSingle)
	{
		//change startdeg of this and prev region. as normal
		if(region->prevRegion)
		{
			//dont allow
			if(newStartDeg <= region->prevRegion->startDeg)
				return false;
				
			region->prevRegion->endDeg = newStartDeg;	
			
		}
		//Actually Set the start deg!
		region->startDeg = newStartDeg;
		return true;
	}
	else if(method == RegionLinearStretch)
	{
		uint8_t numRegionPrior = region->index;
		uint8_t numEdgesPrior = numRegionPrior - 1;
		
		//change startdeg of this and prev region. as normal
		if(region->prevRegion)
		{
			region->prevRegion->endDeg = newStartDeg;
			//Actually Set the start deg!
			region->startDeg = newStartDeg;
		}
		else
		{
			//Actually Set the start deg!
			region->startDeg = newStartDeg;
			return true;
		}
		
		if(numRegionPrior <= 1)
			return true;
			
		//now we know we have at least 2 regions behind us.	
		float shiftPercent = (newStartDeg/(maxDeg - minDeg))/(oldStartDeg/(maxDeg - minDeg));
		Serial.print("shift percent: ");
		Serial.println(shiftPercent);
		//ok lets do a loop down to 0
		ArchRegion* curRegion = region->prevRegion;
		while(curRegion)
		{
			Serial.println(curRegion->index);
			float n = curRegion->startDeg*shiftPercent;
			if(curRegion->prevRegion)
			{
				curRegion->startDeg = n;
				if(curRegion->prevRegion)
				{
					curRegion->prevRegion->endDeg = n;
				}	
			}
			
			curRegion = curRegion->prevRegion;
		}
		return true;	
	}
	
	return false;
}
boolean ArchRegionManager::ModifyRegionEnd(ArchRegion* region, float newEndDeg, RegionModifyMethod method)
{
	
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



void ArchRegionManager::PrintRegionInfo()
{
	Serial.println("Region Info:");
	ArchRegion* curRegion = regionListFirst;
	while(curRegion != NULL)
	{
		
		Serial.print("Region: ");
		Serial.println(curRegion->index);
		Serial.print("StartDeg: ");
		Serial.print(curRegion->startDeg);
		Serial.print("  EndDeg: ");
		Serial.println(curRegion->endDeg);
		
		curRegion = curRegion->nextRegion;
	}
	
}