/* 
* ArchLCD.cpp
*
* Created: 2/20/2015 10:42:13 AM
* Author: 7002815
*/


#include "ArchLCD.h"
#include "PrimaryDefines.h"

// default constructor
ArchLCD::ArchLCD()
{
	

	
	
} //ArchLCD

// default destructor
ArchLCD::~ArchLCD()
{
} //~ArchLCD


void ArchLCD::Initialize()
{
		// Setup for Master mode, pins 18/19, external pullups, 100kHz
		Wire.begin(I2C_MASTER, ORBITAL_I2C_ADDRESS, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_100);
		Wire.setOpMode(I2C_OP_MODE_IMM);
		
		char autoKeyTransCommand = 65;
		SendCommand(&autoKeyTransCommand,1);
		
}
void ArchLCD::ClearScreen()
{
	char clr = 0x58;
	SendCommand(&clr, 1);
	
		
}

void ArchLCD::SendCommand(char* parameters, int numParameters)
{
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	for( int i = 0; i < numParameters; i++)
	{
		Wire.write(parameters[i]);
	}
	Wire.endTransmission();
	
}


void ArchLCD::SendText(char* string)
{
		Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
		Wire.write(string);
		Wire.endTransmission();
}
void ArchLCD::SendChar(char byt)
{
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(byt);
	Wire.endTransmission();
}


//reads 1 key from the I2c key Buffer
//usages While(key = ReadKey()) { react to value of key press.}
char ArchLCD::ReadKey()
{
	Serial.println(Wire.requestFrom(ORBITAL_I2C_ADDRESS, 1));


	if(Wire.available())
	{
	
		return Wire.read();
	}
		
	return 'z';
}
