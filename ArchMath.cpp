/*
 * ArchMath.cpp
 *
 * Created: 3/25/2015 12:53:53 PM
 *  Author: 7002815
 */ 

#include "ArchMath.h"

//quick sort from http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
void quick_sort_int(int *a, int n) {
	int i, j, p, t;
	if (n < 2)
	return;
	p = a[n / 2];
	for (i = 0, j = n - 1;; i++, j--) {
		while (a[i] < p)
		i++;
		while (p < a[j])
		j--;
		if (i >= j)
		break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	quick_sort_int(a, i);
	quick_sort_int(a + i, n - i);
}



void quick_sort_fingerCon(ArchFingerBlobConnection *a, int n)
{
	int i, j, p;
	ArchFingerBlobConnection t;
	if (n < 2)
	return;
	p = a[n / 2].distance;
	for (i = 0, j = n - 1;; i++, j--) {
		while (a[i].distance < p)
		i++;
		while (p < a[j].distance)
		j--;
		if (i >= j)
		break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	quick_sort_fingerCon(a, i);
	quick_sort_fingerCon(a + i, n - i);	
}






//midi scale tools
uint8_t GetMidiScaleValue(uint8_t baseNote, uint8_t stepOffset, MusicScales scaleType)
{
	const int NUM_STEPS_IN_MAJOR_SCALE = 7;
	const int MajorScaleLookupTable[NUM_STEPS_IN_MAJOR_SCALE] = {2, 2, 1, 2, 2, 2, 1};
	
	const int NUM_STEPS_IN_MINOR_SCALE = 7;
	const int MinorScaleLookupTable[NUM_STEPS_IN_MINOR_SCALE] = {2, 1, 2, 2, 1, 2, 2};
	
	int* table;
	int numSteps;
	
	if(scaleType == MajorScale)
	{
		table = (int*)MajorScaleLookupTable;
		numSteps = NUM_STEPS_IN_MINOR_SCALE;
	}
	else if(scaleType == MinorScale)
	{
		table = (int*)MinorScaleLookupTable;
		numSteps = NUM_STEPS_IN_MINOR_SCALE;
	}
	else if(scaleType == ChromaticScale)
	{
		return baseNote + stepOffset;
	}
	
	int curNote = baseNote;
	int stepCount = 0;
	int tableIdx = 0;
	while(stepCount < (stepOffset))
	{
		stepCount++;
		curNote += *(table + tableIdx);
		tableIdx++;
		if(tableIdx == numSteps)
			tableIdx = 0;
	}
	
	return curNote;
	
}



boolean GetMidiIsOctaveOf(uint8_t note1, uint8_t note2)
{
	if(note1%12 == note2%12)
		return true;
	
	return false;
	
}