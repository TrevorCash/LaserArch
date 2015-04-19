/* 
* ArchLCD.h
*
* Created: 2/20/2015 10:42:14 AM
* Author: 7002815
*/

#ifndef __ARCHLCD_H__
#define __ARCHLCD_H__

#include "ArchInterfaceManager.h"

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
	void DrawLabel(uint8_t X1, uint8_t Y1, const char* str);
	void DrawLine(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
	void DrawRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
	void DrawFilledRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
	
protected:
	
	

private:
	ArchLCD( const ArchLCD &c );
	ArchLCD& operator=( const ArchLCD &c );

}; //ArchLCD

#endif //__ARCHLCD_H__
