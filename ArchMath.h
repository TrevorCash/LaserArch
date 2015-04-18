/*
 * ArchMath.h
 *
 * Created: 2/17/2015 10:17:41 AM
 *  Author: 7002815
 */ 

//CONTAINS convienience math for the laser arch.


#ifndef ARCHMATH_H_
#define ARCHMATH_H_

#define ARCH_PIT_TICK_HERTZ 5000000//5 Megahertz from k20 data sheet
#define ARCH_PIT_TICK_PERIOD_NS 200//200 nano seconds = 1/(5megahertz)

#define ARCH_PIT_TIMER_FROM_NANOSEC(NSEC) (NSEC/ARCH_PIT_TICK_PERIOD_NS)
#define ARCH_PIT_TIMER_FROM_USEC(USEC) (USEC/(ARCH_PIT_TICK_PERIOD_NS/(1000.0)))
#define ARCH_PIT_TIMER_FROM_MSEC(MSEC) (MSEC/(ARCH_PIT_TICK_PERIOD_NS/(1000000.0)))

#include "ArchFingerBlobConnection.h"

//quick sort from http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
void quick_sort_int(int *a, int n);
void quick_sort_fingerCon(ArchFingerBlobConnection *a, int n);





//midi music scales utils
enum MusicScales
{
	MajorScale,
	MinorScale,
	ChromaticScale	
};
uint8_t GetMidiScaleValue(uint8_t baseNote, uint8_t stepOffset, MusicScales scaleType);



#endif /* ARCHMATH_H_ */