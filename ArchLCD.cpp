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
}
void ArchLCD::ClearScreen()
{
	Serial.println("WUASDASD");
	Serial.println("WUASDASD");
Serial.println("WUASDASD");
Serial.println("WUASDASD");
	Serial.println("WUASDASD");
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	Wire.write(0x58);
	Wire.endTransmission();
}