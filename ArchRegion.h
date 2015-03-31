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
	void UpdateAll(float startDeg, float endDeg, uint8_t red, uint8_t green, uint8_t blue);
	void UpdateSpan(float startDeg, float endDeg);
	void UpdateColors(uint8_t red, uint8_t green, uint8_t blue);
	
	
	ArchRegion* prevRegion;
	ArchRegion* nextRegion;
	
protected:
private:

	//core
	float startDeg;
	float endDeg;
	uint8_t colorRed;
	uint8_t colorGreen;
	uint8_t colorBlue;
	
	
	//computables
	float widthDeg;

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