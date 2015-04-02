/* 
* ArchRegionManager.cpp
*
* Created: 3/31/2015 11:08:20 AM
* Author: 7002815
*/


#include "ArchRegionManager.h"

// default constructor
ArchRegionManager::ArchRegionManager(float minDeg, float maxDeg, ArchMotor* motor)
{
	this->minDeg = minDeg;
	this->maxDeg = maxDeg;
	
	this->motor = motor;
	
	regionListFirst = NULL;
	numRegions = 0;
} //ArchRegionManager

// default destructor
ArchRegionManager::~ArchRegionManager()
{
} //~ArchRegionManager


void ArchRegionManager::Initialize(uint8_t numReqRegions)
{
	if(numReqRegions < 1)
		return;
	
	ClearAllRegions();
	
	int i;
	this->numRegions = numReqRegions;
	float regionWidth = (maxDeg - minDeg)/numReqRegions;
	ArchRegion* prevRegion = NULL;
	for(i = 0; i < numReqRegions; i++)
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
	
		newRegion->UpdateSpan(minDeg+(i*regionWidth), minDeg+((i+1)*regionWidth));

		newRegion->UpdateColors((i%2)*32 + 32,((i+1)%3)*32,(i%4)*32);
		
	}
	
	
}



boolean ArchRegionManager::ModifyRegionSpan(ArchRegion* region, float newStartDeg, float newEndDeg, RegionModifyMethod method)
{
	boolean startSuccess = ModifyRegionStart(region, newStartDeg, method);
	
	boolean endSuccess = ModifyRegionEnd(region, newEndDeg, method);
	
	CleanupZeroRegions();
	
	return startSuccess || endSuccess;
}



boolean ArchRegionManager::ModifyRegionStart(ArchRegion* region, float newStartDeg, RegionModifyMethod method)
{
	if(region == NULL)
		return false;
	
	//you cant change the start of the first region.  It must stay bound to minDeg..
	if(!region->prevRegion)
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
		
		//dont allow ecplising of previous region.
		if(newStartDeg <= region->prevRegion->startDeg)
			return false;
				
		region->prevRegion->endDeg = newStartDeg;	
		
		//Actually Set the start deg!
		region->startDeg = newStartDeg;
		return true;
	}
	else if(method == RegionLinearStretch)
	{
		uint8_t numRegionPrior = region->index;
		uint8_t numEdgesPrior = numRegionPrior - 1;
		
		//change startdeg of this and prev region. as normal
		region->prevRegion->endDeg = newStartDeg;
		//Actually Set the start deg!
		region->startDeg = newStartDeg;
		
		
		if(numRegionPrior <= 1)
			return true;
			
		//now we know we have at least 2 regions behind us.	
		float shiftPercent = (newStartDeg - minDeg)/(oldStartDeg - minDeg);
		//ok lets do a loop down to 0
		ArchRegion* curRegion = region->prevRegion;
		while(curRegion)
		{
			float n = shiftPercent*(curRegion->startDeg - minDeg) + minDeg;
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
	if(region == NULL)
		return false;
	
	//you cant change the end of the first region.  It must stay bound to maxDeg..
	if(!region->nextRegion)
		return false;
	
	if(newEndDeg == region->endDeg)
		return true;
	
	//dont allow "flipping" of region.
	if(newEndDeg < region->startDeg)
		return false;
	
	//dont allow out of bounds
	if(newEndDeg < minDeg || newEndDeg > maxDeg)
		return false;


	//final - initial
	float endDelta = newEndDeg - region->endDeg;
	float oldEndDeg = region->endDeg;


	if(method == RegionSingle)
	{
		
		//dont allow ecplising of next region.
		if(newEndDeg > region->nextRegion->endDeg)
			return false;
		
		region->nextRegion->startDeg = newEndDeg;
		
		//Actually Set the end deg!
		region->endDeg = newEndDeg;
		return true;
	}
	else if(method == RegionLinearStretch)
	{
		uint8_t numRegionAfter = numRegions - region->index - 1;
		uint8_t numEdgesAfter = numRegionAfter - 1;
		
		//change enddeg of this and next region. as normal
		region->nextRegion->startDeg = newEndDeg;
		//Actually Set the start deg!
		region->endDeg = newEndDeg;
		
		
		if(numRegionAfter <= 1)
			return true;
		
		//now we know we have at least 2 regions ahead of us.
		float shiftPercent = (maxDeg - newEndDeg)/(maxDeg - oldEndDeg);
		//ok lets do a loop down to 0
		ArchRegion* curRegion = region->nextRegion;
		while(curRegion)
		{
			float n = maxDeg - shiftPercent*(maxDeg - curRegion->endDeg);
			if(curRegion->nextRegion)
			{
				curRegion->endDeg = n;
				curRegion->nextRegion->startDeg = n;

			}
			
			curRegion = curRegion->nextRegion;
		}
		return true;
	}
	
	return false;
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



boolean ArchRegionManager::RemoveRegion(ArchRegion* region)
{
	if(region == NULL)
		return false;
	
	if(numRegions <= 1)
		return false;	
		
		
	ArchRegion* curRegion = region->nextRegion;
	while(curRegion)
	{
		curRegion->index--;
		curRegion = curRegion->nextRegion;	
	}

	
	if(!region->prevRegion)
	{
		regionListFirst = region->nextRegion;
		region->nextRegion->startDeg = region->startDeg;
		region->nextRegion->prevRegion = NULL;
		
	}
	else if(!region->nextRegion)
	{
		region->prevRegion->endDeg = region->endDeg;
		region->prevRegion->nextRegion = NULL;
	}
	else
	{
		
		float midDeg = (region->endDeg + region->startDeg)*0.5;
		region->nextRegion->startDeg = midDeg;
		region->prevRegion->endDeg = midDeg;
		
		region->prevRegion->nextRegion = region->nextRegion;
		region->nextRegion->prevRegion = region->prevRegion;
		
	}
	
	region->nextRegion = NULL;
	region->prevRegion = NULL;
	numRegions--;
	
	return true;
}


//gets rid of linked list behalvior on all regions
void ArchRegionManager::ClearAllRegions()
{
	regionListFirst = NULL;
	numRegions = 0;
	int r;
	for(r = 0; r < MAX_REGIONS; r++)
	{
		regionPool[r].prevRegion = NULL;
		regionPool[r].nextRegion = NULL;
		
	}
	
}

boolean ArchRegionManager::CleanupZeroRegions()
{
	ArchRegion* curRegion = regionListFirst;
	while(curRegion)
	{
		
		if((curRegion->endDeg - curRegion->startDeg) < MIN_REGION_SIZE_DEG)
		{
			ArchRegion* temp = curRegion;
			curRegion = curRegion->nextRegion;
			RemoveRegion(temp);
		}
		else
			curRegion = curRegion->nextRegion;
	}
	
}