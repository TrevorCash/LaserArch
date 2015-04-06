/* 
* ArchLCD.h
*
* Created: 2/20/2015 10:42:14 AM
* Author: 7002815
*/


#ifndef __ARCHLCD_H__
#define __ARCHLCD_H__

#include <i2c_t3/i2c_t3.h>
#include "PrimaryDefines.h"

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
	
	//Low Level Commands
	void SendCommand(char* parameters, int numParameters);
	void SendText(char* string);
	void SendChar(char byt);
	void ClearScreen();
	char ReadKey();
	
	//Mid Level Commands
	void InitializeLabel(uint8_t ID, uint8_t LeftCord, uint8_t RightCord, uint8_t TopCord, uint8_t BottomCord, uint8_t VertAlign = 0, uint8_t HorizAlign = 0, uint16_t FontId = 1, uint8_t BackGround = 0, uint8_t CharSpacing = 2);
	void UpdateLabel(uint8_t ID, char* str);
	
protected:
	
	

private:
	ArchLCD( const ArchLCD &c );
	ArchLCD& operator=( const ArchLCD &c );

}; //ArchLCD

#endif //__ARCHLCD_H__
