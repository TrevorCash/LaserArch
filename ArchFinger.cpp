/* 
* ArchFinger.cpp
*
* Created: 3/23/2015 5:43:11 PM
* Author: 7002815
*/


#include "ArchFinger.h"

// default constructor
ArchFinger::ArchFinger()
{
	centerTime = 0;
	timeWidth = 0;
	isActive = false;
}//ArchFinger

// default destructor
ArchFinger::~ArchFinger()
{
} //~ArchFinger



void ArchFinger::Start(uint32_t time, uint32_t width)
{
	centerTime = time;	
	timeWidth = width;
	isActive = true;
}
void ArchFinger::Update(uint32_t newTime, uint32_t newWidth)
{
	centerTime = newTime;
	timeWidth = newWidth;
}
void ArchFinger::End()
{
	isActive = false;
}