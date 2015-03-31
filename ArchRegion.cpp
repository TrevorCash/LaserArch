/* 
* ArchRegion.cpp
*
* Created: 3/31/2015 11:08:42 AM
* Author: 7002815
*/


#include "ArchRegion.h"

// default constructor
ArchRegion::ArchRegion()
{
	startDeg = -1.0;
	endDeg = -1.0;
	widthDeg = 0;
	colorRed = 255;
	colorGreen = 0;
	colorBlue = 0;
	
	prevRegion = NULL;
	nextRegion = NULL;
} //ArchRegion

// default destructor
ArchRegion::~ArchRegion()
{
} //~ArchRegion


//updates all parameters!!
void ArchRegion::UpdateAll(float startDeg, float endDeg, uint8_t red, uint8_t green, uint8_t blue)
{
	this->startDeg = startDeg;
	this->endDeg = endDeg;
	this->widthDeg = endDeg - startDeg;
	this->colorRed = red;
	this->colorGreen = green;
	this->colorBlue = blue;
}
void ArchRegion::UpdateSpan(float startDeg, float endDeg)
{
	UpdateAll(startDeg,endDeg,colorRed, colorGreen, colorBlue);
}

void ArchRegion::UpdateColors(uint8_t red, uint8_t green, uint8_t blue)
{
	UpdateAll(startDeg, endDeg,red, green, blue);
}