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
	ArchLedManager(OctoWS2811* ledObject, ArchRegionManager* regionManager, ArchFingerManager* fingerManager);
	~ArchLedManager();
	
	void Update();
	
	void Clear();
	
	uint8_t AngleToLedIdx(float angle)
	{
		
		//TODO - should work with LED_ANGLE_COVERAGE and Centering to account for the actually angle coverage of the ledstrip.
		float frac = 1.0 - (angle - regionManager->minDeg)/(regionManager->maxDeg - regionManager->minDeg);
		
		return frac*144;
	}
	
protected:
private:
ArchRegionManager* regionManager;
ArchFingerManager* fingerManager;
OctoWS2811* ledStrip;


}; //ArchLedManager

#endif //__ARCHLEDMANAGER_H__
