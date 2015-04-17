/* 
* ArchLedManager.h
*
* Created: 3/31/2015 5:24:56 PM
* Author: 7002815
*/


#ifndef __ARCHLEDMANAGER_H__
#define __ARCHLEDMANAGER_H__

#include "ArchRegionManager.h"
#include "ArchFingerManager.h"
#include "OctoWS2811Trevor.h"

class ArchLedManager
{
//variables
public:
protected:
private:

//functions
public:
	ArchLedManager(OctoWS2811* ledObject, ArchRegionManager* regionManager, ArchFingerManager* fingerManager, ArchMotor* mainMotor);
	~ArchLedManager();
	
	void Update();
	
	void Clear();
	
	uint8_t AngleToLedIdx(float angle)
	{
		float frac = (angle - regionManager->minDeg)/(regionManager->maxDeg - regionManager->minDeg);
		//Serial.println(frac);
		//Serial.println(uint8_t(frac*144.0));
		return (frac)*144.0;
	}
	
protected:
private:
ArchRegionManager* regionManager;
ArchFingerManager* fingerManager;
OctoWS2811* ledStrip;
ArchMotor* mainMotor;

}; //ArchLedManager

#endif //__ARCHLEDMANAGER_H__
