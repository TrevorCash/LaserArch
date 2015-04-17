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

public:
	ArchRegion();
	~ArchRegion();
	

	//These functions DO NOT EFFECT Surrounding regions. Use ArchRegionManager for that functionality.
	void SetAll(float startDeg, float endDeg, uint8_t midiNote, uint8_t red, uint8_t green, uint8_t blue);
	void SetSpan(float startDeg, float endDeg);
	void SetColors(uint8_t red, uint8_t green, uint8_t blue);
	void SetNote(uint8_t newMidiNote);
	
	uint8_t GetNote(){return midiNote;}
	void GetColors(uint8_t& red, uint8_t& green, uint8_t& blue)
	{
		red = this->colorRed;
		green = this->colorGreen;
		blue = this->colorBlue;
	}	
	float GetSpan(){return endDeg - startDeg;}
	
	//gets the angles of transition for fingers using hysteresis
	float GetTransitionAngleToNext();
	float GetTransitionAngleToPrev();
	
	
	
	
	//prints some useful info to the serial port..
	void PrintInfo()
	{
		Serial.print("startDeg: ");
		Serial.println(startDeg);
		Serial.print("endDeg: ");
		Serial.println(endDeg);
		Serial.print("midiNote: ");
		Serial.println(midiNote);
	}
	
	boolean IsValid;
	
	//core
	uint32_t index;
	float startDeg;
	float endDeg;
	uint8_t colorRed;
	uint8_t colorGreen;
	uint8_t colorBlue;
	uint8_t midiNote;
	
	uint8_t fingerCount;
	
	//computables
	float widthDeg;
	
	ArchRegion* prevRegion;
	ArchRegion* nextRegion;



}; //ArchRegion

#endif //__ARCHREGION_H__
