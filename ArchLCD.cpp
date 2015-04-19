/*
* ArchLCD.cpp
*
* Created: 2/20/2015 10:42:13 AM
* Author: 7002815
*/


#include "ArchLCD.h"

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
		Wire.begin(I2C_MASTER, ORBITAL_I2C_ADDRESS, I2C_PINS_18_19, I2C_PULLUP_INT, I2C_RATE_1800);
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
//returns 0 if no key was pressed. else returns the keycode
char ArchLCD::ReadKey()
{
	char byte = 0x00;
	Wire.requestFrom(ORBITAL_I2C_ADDRESS, 1);
	if(Wire.available())
	{
		byte = Wire.readByte();
	}
		
	return byte;
}

void ArchLCD::DrawLabel(uint8_t X1, uint8_t Y1, const char* str)
{
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	Wire.write(0x79);
	Wire.write(X1+2);
	Wire.write(Y1+2);
	Wire.endTransmission();
	
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(str);
	Wire.endTransmission();
}

void ArchLCD::DrawLine(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2)
{
	//Set the Drawing Color
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	Wire.write(0x63);
	Wire.write(color);
	Wire.endTransmission();
	
	//Draw the Line
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	Wire.write(0x6C);
	Wire.write(X1);
	Wire.write(Y1);
	Wire.write(X2);
	Wire.write(Y2);
	Wire.endTransmission();
}

void ArchLCD::DrawRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2)
{
	//Draw the Rectangle
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	Wire.write(0x72);
	Wire.write(color);
	Wire.write(X1);
	Wire.write(Y1);
	Wire.write(X2);
	Wire.write(Y2);
	Wire.endTransmission();
}

void ArchLCD::DrawFilledRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2)
{
	//Draw the Rectangle
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	Wire.write(0x78);
	Wire.write(color);
	Wire.write(X1);
	Wire.write(Y1);
	Wire.write(X2);
	Wire.write(Y2);
	Wire.endTransmission();
}