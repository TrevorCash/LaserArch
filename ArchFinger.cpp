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
	validity = MIN_FINGER_VALIDITY;
}//ArchFinger

// default destructor
ArchFinger::~ArchFinger()
{
} //~ArchFinger


void ArchFinger::Validate(uint32_t newTime, uint32_t newWidth)
{
	centerTime = newTime;
	timeWidth = newWidth;
	validity++;
	if(validity >= MAX_FINGER_VALIDITY)
		validity = MAX_FINGER_VALIDITY;
	
}

void ArchFinger::SuperValidate(uint32_t newTime, uint32_t newWidth)
{
	centerTime = newTime;
	timeWidth = newWidth;
	validity = MAX_FINGER_VALIDITY;
}


void ArchFinger::DeValidate()
{
		validity--;
		if(validity <= MIN_FINGER_VALIDITY)
		validity = MIN_FINGER_VALIDITY;
}
boolean ArchFinger::IsFullyValid()
{
	return (validity >= FINGER_VALIDITY_THRESH);
}