/* 
* ArchFinger.cpp
*
* Created: 3/23/2015 5:43:11 PM
* Author: 7002815
*/


#include "ArchFinger.h"
#include "PrimaryDefines.h"

// default constructor
ArchFinger::ArchFinger()
{
	centerTime = 0;
	timeWidth = 0;
	
	centerTimePrev = 0;
	timeWidthPrev = 0;
	
	curRegion = NULL;
	lastRegion = NULL;

	validity = MIN_FINGER_VALIDITY;
	isUsed = false;
	hasStarted = false;
}//ArchFinger

// default destructor
ArchFinger::~ArchFinger()
{
} //~ArchFinger


