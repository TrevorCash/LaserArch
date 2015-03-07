/* 
* ArchLCD.h
*
* Created: 2/20/2015 10:42:14 AM
* Author: 7002815
*/


#ifndef __ARCHLCD_H__
#define __ARCHLCD_H__
#include <i2c_t3/i2c_t3.h>

//provides encapsulated access to the LCD unit via I2C.
//to be used by the ArchInterfaceManager Primarily.
class ArchLCD
{
//variables
public:
protected:
private:

//functions
public:
	ArchLCD();
	~ArchLCD();
	void Initialize();
	void ClearScreen();
protected:
private:
	ArchLCD( const ArchLCD &c );
	ArchLCD& operator=( const ArchLCD &c );

}; //ArchLCD

#endif //__ARCHLCD_H__
