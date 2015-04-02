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
ArchLedManager::ArchLedManager(OctoWS2811* ledObject, ArchRegionManager* regionManager, ArchFingerManager* fingerManager)
{
	this->regionManager = regionManager;
	this->fingerManager = fingerManager;
	this->ledStrip = ledObject;
	
	
} //ArchLedManager

// default destructor
ArchLedManager::~ArchLedManager()
{
} //~ArchLedManager



void ArchLedManager::Update()
{
	int i;
	for (i=0; i < 144; i++) {
		ledStrip->setPixel(i, 0x0);
	}
	
	ArchRegion* curRegion = regionManager->RegionList();
	while(curRegion != NULL)
	{
		int pixStart = AngleToLedIdx(curRegion->startDeg);
		int pixEnd = AngleToLedIdx(curRegion->endDeg);
		
		int f;
		for(f = pixStart; f < pixEnd; f++)
		{
			//Serial.println(f);
			ledStrip->setPixel(f,curRegion->colorRed,curRegion->colorBlue,curRegion->colorGreen);
		
		}
		curRegion = curRegion->nextRegion;
	}
	
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