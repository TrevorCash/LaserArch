/* 
* ArchRegionScheme.h
*
* Created: 4/19/2015 11:46:03 AM
* Author: 7002815
*/


#ifndef __ARCHREGIONSCHEME_H__
#define __ARCHREGIONSCHEME_H__

#include "Arduino.h"

enum ArchRegionSchemes
{
	ChromaticScheme,			//Chromatic, with 2 alternating colors
	ChromaticPianoRollScheme,	//chromatic with indication of black vs white notes on a keyboard
	MajorScaleScheme,			//MajorScale Scheme
	MinorScaleScheme,			//MinorScale Scheme
	TriggerScheme				//TriggerScheme with somewhat random colors (for use with custom mode perhaps?)
};

class ArchRegion;

class ArchRegionScheme
{


//functions
public:
	ArchRegionScheme(ArchRegionSchemes schemeEnum, uint8_t midiBaseNote, uint16_t numRegions);
	~ArchRegionScheme();
	
	
	//based off the schemeType, the region's settings are altered based on the scheme (setting color, note, etc)
	//NOTE: BUT NOT SPAN - RIGHT NOW THAT IS STILL REGION MANAGER's JOB
	boolean AssignRegionAttributes(ArchRegion* region);
	
	ArchRegionSchemes schemeType;
	uint8_t midiBaseNote;
	uint16_t numRegions;
protected:
private:


}; //ArchRegionScheme

#endif //__ARCHREGIONSCHEME_H__
