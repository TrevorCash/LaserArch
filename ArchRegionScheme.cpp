/* 
* ArchRegionScheme.cpp
*
* Created: 4/19/2015 11:46:02 AM
* Author: 7002815
*/


#include "ArchRegionScheme.h"
#include "ArchMath.h"

// default constructor
ArchRegionScheme::ArchRegionScheme(ArchRegionSchemes schemeEnum, uint8_t midiBaseNote, uint16_t numRegions)
{
	schemeType = schemeEnum;
	this->midiBaseNote = midiBaseNote;
	this->numRegions = numRegions;
} //ArchRegionScheme

// default destructor
ArchRegionScheme::~ArchRegionScheme()
{
} //~ArchRegionScheme





boolean ArchRegionScheme::AssignRegionAttributes(ArchRegion* region)
{
	if(schemeType == ChromaticScheme)
	{
		region->SetNote(midiBaseNote + region->index);
		region->SetColors((region->index%2)*255, 0, ((region->index + 1)%2)*255);
	}
	else if(schemeType == ChromaticPianoRollScheme)
	{
		region->SetNote(midiBaseNote + region->index);
		region->SetColors((region->index%2)*255, 0, ((region->index + 1)%2)*255);
	}
	else if(schemeType == MajorScaleScheme)
	{
		uint8_t note = GetMidiScaleValue(midiBaseNote, region->index, MajorScale);
		region->SetNote(note);
		if(GetMidiIsOctaveOf(midiBaseNote, note))
			region->SetColors(255, 0, 0);
		else
			region->SetColors(0, ((region->index + 1)%2)*255, ((region->index)%2)*255);
	}
	else if(schemeType == MinorScaleScheme)
	{
		
		
	}
	else if(schemeType == TriggerScheme)
	{
		
		
	}
	else 
		return false;
		
	return true;
}