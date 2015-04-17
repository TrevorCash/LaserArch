/* 
* ArchRegion.cpp
*
* Created: 3/31/2015 11:08:42 AM
* Author: 7002815
*/


#include "ArchRegion.h"
#include "MIDINoteDefines.h"
#include "PrimaryDefines.h"

// default constructor
ArchRegion::ArchRegion()
{
	startDeg = -1.0;
	endDeg = -1.0;
	widthDeg = 0;
	colorRed = 255;
	colorGreen = 0;
	colorBlue = 0;
	midiNote = MIDI_C3; 
	fingerCount = 0;
	index = 0;
	
	IsValid = false;
	
	prevRegion = NULL;
	nextRegion = NULL;
} //ArchRegion

// default destructor
ArchRegion::~ArchRegion()
{
} //~ArchRegion


//updates all parameters!!  This DOES NOT EFFECT Surrounding regions. Look in ArchRegionManager for that.
void ArchRegion::SetAll(float startDeg, float endDeg, uint8_t midiNote, uint8_t red, uint8_t green, uint8_t blue)
{
	this->startDeg = startDeg;
	this->endDeg = endDeg;
	this->widthDeg = endDeg - startDeg;
	this->colorRed = red;
	this->colorGreen = green;
	this->colorBlue = blue;
	this->midiNote = midiNote;
}
void ArchRegion::SetSpan(float startDeg, float endDeg)
{
	SetAll(startDeg, endDeg, midiNote, colorRed, colorGreen, colorBlue);
}
void ArchRegion::SetColors(uint8_t red, uint8_t green, uint8_t blue)
{
	SetAll(startDeg, endDeg, midiNote, red, green, blue);
}

void ArchRegion::SetNote(uint8_t newMidiNote)
{
	SetAll(startDeg, endDeg, newMidiNote, colorRed, colorGreen, colorBlue);
}





//gets the angles of transition for fingers using hysteresis
float ArchRegion::GetTransitionAngleToNext()
{
	if(nextRegion)
	{
		if(nextRegion->GetSpan() < FINGER_REGION_HYSTERESIS_MAX_DEG/FINGER_REGION_HYSTERESIS_MIN_RATIO_OF_SPAN)
			return endDeg + nextRegion->GetSpan()*FINGER_REGION_HYSTERESIS_MIN_RATIO_OF_SPAN;
		else
			return endDeg + FINGER_REGION_HYSTERESIS_MAX_DEG;
	}
	else
	{
		return endDeg;
	}
}
float ArchRegion::GetTransitionAngleToPrev()
{
	if(prevRegion)
	{
		if(prevRegion->GetSpan() < FINGER_REGION_HYSTERESIS_MAX_DEG/FINGER_REGION_HYSTERESIS_MIN_RATIO_OF_SPAN)
		return startDeg - prevRegion->GetSpan()*FINGER_REGION_HYSTERESIS_MIN_RATIO_OF_SPAN;
		else
		return startDeg - FINGER_REGION_HYSTERESIS_MAX_DEG;
	}
	else
	{
		return startDeg;
	}	
}