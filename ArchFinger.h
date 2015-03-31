/* 
* ArchFinger.h
*
* Created: 3/23/2015 5:43:11 PM
* Author: 7002815
*/


#ifndef __ARCHFINGER_H__
#define __ARCHFINGER_H__

#include "Arduino.h"

class ArchFinger
{
//variables
public:
protected:
private:

//functions
public:
	ArchFinger();
	~ArchFinger();
	
	uint32_t centerTime; //center of the finger in time
	uint32_t timeWidth;//width of the finger in time
	uint8_t validity;
	
	
	boolean IsFullyValid();
	void Validate(uint32_t newTime, uint32_t newWidth);
	void SuperValidate(uint32_t newTime, uint32_t newWidth);
	void DeValidate();
	
	
	
protected:
private:
	ArchFinger( const ArchFinger &c );
	ArchFinger& operator=( const ArchFinger &c );

}; //ArchFinger

#endif //__ARCHFINGER_H__
