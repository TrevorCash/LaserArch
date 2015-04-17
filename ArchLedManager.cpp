/* 
* ArchLedManager.cpp
*
* Created: 3/31/2015 5:24:56 PM
* Author: 7002815
*/


#include "ArchLedManager.h"
#include "ArchRegion.h"
#include "OctoWS2811Trevor.h"

// default constructor
ArchLedManager::ArchLedManager(OctoWS2811* ledObject, ArchRegionManager* regionManager, ArchFingerManager* fingerManager, ArchMotor* mainMotor)
{
	this->regionManager = regionManager;
	this->fingerManager = fingerManager;
	this->ledStrip = ledObject;
	this->mainMotor = mainMotor;
	
	
} //ArchLedManager

// default destructor
ArchLedManager::~ArchLedManager()
{
} //~ArchLedManager



void ArchLedManager::Update()
{


	
	ArchRegion* curRegion = regionManager->RegionList();
	while(curRegion != NULL)
	{
		int pixStart = AngleToLedIdx(curRegion->startDeg);
		int pixEnd = AngleToLedIdx(curRegion->endDeg);
		
		int f;
		for(f = pixStart; f < pixEnd; f++)
		{
			//Serial.println(f);
			ledStrip->setPixel(f,curRegion->colorRed/4,curRegion->colorBlue/4,curRegion->colorGreen/4);
		
		}
		curRegion = curRegion->nextRegion;
	}
	
	//show some finger ghosting
	int f;
	for(f = 0; f < MAX_FINGERS; f++)
	{
		if(fingerManager->fingerPool[f].hasStarted && fingerManager->fingerPool[f].isUsed)
		{
			int pixStart = AngleToLedIdx(mainMotor->AngleFromTicksLast(fingerManager->fingerPool[f].StartTime()));
			int pixEnd = AngleToLedIdx(mainMotor->AngleFromTicksLast(fingerManager->fingerPool[f].EndTime()));
			
			
			int f;
			for(f = pixStart; f < pixEnd; f++)
			{
				ledStrip->setPixel(f,0,64,0);	
			}
		}
		
	}
	//wait till not busy and sho first (because the setpixels are non-blocking and we can free time).
	while(ledStrip->busy()){};
	ledStrip->show();
	
	
}


void ArchLedManager::Clear()
{
	int i;
	for (i=0; i < 144; i++) {
		ledStrip->setPixel(i, 0x0);
	}
}