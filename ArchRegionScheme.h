/* 
* ArchRegionScheme.h
*
* Created: 4/19/2015 11:46:03 AM
* Author: 7002815
*/


#ifndef __ARCHREGIONSCHEME_H__
#define __ARCHREGIONSCHEME_H__

#include "Arduino.h"
#include "MIDINoteDefines.h"

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
	ArchRegionScheme(ArchRegionSchemes schemeEnum = ChromaticScheme, uint8_t midiBaseNote = MIDI_C4, uint16_t numRegions = 25);
	~ArchRegionScheme();
	
	
	//based off the schemeType, the region's settings are altered based on the scheme (setting color, note, etc)
	//NOTE: BUT NOT SPAN - RIGHT NOW THAT IS STILL REGION MANAGER's JOB
	boolean AssignRegionAttributes(ArchRegion* region);
	void SetSchemeType(ArchRegionSchemes schemeEnum) { schemeType = schemeEnum; }
	void SetBaseNote(uint8_t note){midiBaseNote = note;}
	void SetNumRegions(uint16_t num){numRegions = num;}
		
	uint8_t GetBaseNote(){return midiBaseNote;}
	ArchRegionSchemes GetSchemeType(){return schemeType;}
	uint16_t GetNumRegions(){return numRegions;}
	
	ArchRegionSchemes schemeType;
	uint8_t midiBaseNote;
	uint16_t numRegions;
protected:
private:


}; //ArchRegionScheme

#endif //__ARCHREGIONSCHEME_H__
