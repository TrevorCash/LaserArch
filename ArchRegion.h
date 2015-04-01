/* 
* ArchRegion.h
*
* Created: 3/31/2015 11:08:43 AM
* Author: 7002815
*/


#ifndef __ARCHREGION_H__
#define __ARCHREGION_H__

#include "Arduino.h"

class ArchRegion
{
//variables
public:
	//These functions DO NOT EFFECT Surrounding regions. Look in ArchRegionManager for that.
	void UpdateAll(float startDeg, float endDeg, uint8_t red, uint8_t green, uint8_t blue);
	void UpdateSpan(float startDeg, float endDeg);
	void UpdateColors(uint8_t red, uint8_t green, uint8_t blue);
	
	
	void PrintInfo()
	{
		Serial.print("startDeg: ");
		Serial.println(startDeg);
		Serial.print("endDeg: ");
		Serial.println(endDeg);
	}
	
	boolean IsValid;
	
	//core
	uint32_t index;
	float startDeg;
	float endDeg;
	uint8_t colorRed;
	uint8_t colorGreen;
	uint8_t colorBlue;
	
	//computables
	float widthDeg;
	
	ArchRegion* prevRegion;
	ArchRegion* nextRegion;
	
protected:
private:


	
	

//functions
public:
	ArchRegion();
	~ArchRegion();
protected:
private:
	ArchRegion( const ArchRegion &c );
	ArchRegion& operator=( const ArchRegion &c );

}; //ArchRegion

#endif //__ARCHREGION_H__
