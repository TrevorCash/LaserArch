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
	isValid = false;
	
	nextFinger = NULL;
	prevFinger = NULL;
}//ArchFinger

// default destructor
ArchFinger::~ArchFinger()
{
} //~ArchFinger
