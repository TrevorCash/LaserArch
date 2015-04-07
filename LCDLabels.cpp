// 
// 
// 

#include "LCDLabels.h"

////////////////////////////////////////////////////////////////////////////////
//						Constructors/Destructors							  //
////////////////////////////////////////////////////////////////////////////////

LCDLabels::LCDLabels(uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, char* NewFrontVal)
{
	ID = NewID;
	X1 = NewX1;
	Y1 = NewY1;
	
	Type = NewType;
	Mode = LABEL_CLEAR;
	setFrontVal(NewFrontVal);

	//Use if update to Firmware Version 8.3
	//VertAlign = 0;
	//HorizAlign = 0;
	//FontID = 1;
	//Background = 0;
	//CharSpacing = 2;
}
LCDLabels::LCDLabels(uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, uint16_t NewBackVal, uint8_t NewLittleInc, uint8_t NewBigInc, uint16_t NewMaxVal, uint16_t NewMinVal)
{
	ID = NewID;
	X1 = NewX1;
	Y1 = NewY1;
	
	Type = NewType;
	Mode = LABEL_CLEAR;
	setBackVal(NewBackVal);
	
	MinVal = NewMinVal;
	MaxVal = NewMaxVal;
	LittleInc = NewLittleInc;
	BigInc = NewBigInc;
	
	//VertAlign = 0;
	//HorizAlign = 0;
	//FontID = 1;
	//Background = 0;
	//CharSpacing = 2;	
}
LCDLabels::~LCDLabels()
{
}

////////////////////////////////////////////////////////////////////////////////
//						Gets/Sets											  //
////////////////////////////////////////////////////////////////////////////////

void LCDLabels::setType(uint8_t NewType)
{
	Type = NewType;
}

uint8_t LCDLabels::getType()
{
	return Type;
}

void LCDLabels::setMode(uint8_t NewMode)
{
	Mode = NewMode;
	IndicateMode();
}

uint8_t LCDLabels::getMode()
{
	return Mode;
}

void LCDLabels::setNextMenu(LCDMenu* NewNextMenu)
{
	NextMenu = NewNextMenu;
}
LCDMenu* LCDLabels::getNextMenu()
{
	return NextMenu;
}

void LCDLabels::setFrontVal(char* str)
{
	FrontVal = str;
	X2 = X1 + 7*FrontVal.length() + 2;
	Y2 = Y1 + 11;
}

const char* LCDLabels::getFrontVal()
{
	return FrontVal.c_str();
}

void LCDLabels::setBackVal(uint16_t NewBackVal)
{
	BackVal = NewBackVal;
	if (Type == LABEL_VALUE_NUMBER)
	{
		setFrontVal((String)(BackVal));
	}
	else if (Type == LABEL_VALUE_NOTE)
	{
		//Complicated Maybe
		FrontVal = "Place";
	}
}

uint16_t LCDLabels::getBackVal()
{
	return BackVal;
}

void LCDLabels::setLittleInc(uint8_t NewLittleInc)
{
	LittleInc = NewLittleInc;
}
uint8_t LCDLabels::getLittleInc()
{
	return LittleInc;
}
void LCDLabels::setBigInc(uint8_t NewBigInc)
{
	BigInc = NewBigInc;
}
uint8_t LCDLabels::getBigInc()
{
	return BigInc;
}
void LCDLabels::setMaxVal(uint16_t NewMaxVal)
{
	MaxVal = NewMaxVal;
}
uint16_t LCDLabels::getMaxVal()
{
	return MaxVal;
}
void LCDLabels::setMinVal(uint16_t NewMinVal)
{
	MinVal = NewMinVal;
}
uint16_t LCDLabels::getMinVal()
{
	return MinVal;
}


void LCDLabels::setQuadPtr(LCDLabels* NewUp, LCDLabels* NewDown, LCDLabels* NewLeft, LCDLabels* NewRight)
{
	Up = NewUp;
	Down= NewDown;
	Left = NewLeft;
	Right = NewRight;
}

LCDLabels* LCDLabels::getLeft()
{
	return Left;
}
LCDLabels* LCDLabels::getRight()
{
	return Right;
}
LCDLabels* LCDLabels::getUp()
{
	return Up;
}
LCDLabels* LCDLabels::getDown()
{
	return Down;
}

void LCDLabels::setNext(LCDLabels* NewNext)
{
	Next = NewNext;
}

LCDLabels* LCDLabels::getNext()
{
	return Next;
}

////////////////////////////////////////////////////////////////////////////////
//						Mid-Level Commands									  //
////////////////////////////////////////////////////////////////////////////////

void LCDLabels::InitializeLabel()
{
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(0xFE);
	Wire.write(0x79);
	Wire.write(X1+2);
	Wire.write(Y2-2);
	Wire.endTransmission();
	
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(FrontVal.c_str());
	Wire.endTransmission();
}

void LCDLabels::UpdateLabel()
{
	DrawFilledRect(0, X1, Y1, X2, Y2);
	InitializeLabel();
}

//void LCDLabels::InitializeLabel()
//{
	//Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	//Wire.write(0xFE);
	//Wire.write(45);
	//Wire.write(ID);
	//Wire.write(X1);
	//Wire.write(Y1);
	//Wire.write(X2);
	//Wire.write(Y2);
	//Wire.write(VertAlign);
	//Wire.write(HorizAlign);
	//Wire.write(FontID);
	//Wire.write(Background);
	//Wire.write(CharSpacing);
	//Wire.endTransmission();
//}

//void LCDLabels::UpdateLabel()
//{
	//Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	//Wire.write(0xFE);
	//Wire.write(0x2E);
	//Wire.write(ID);
	//Wire.write(FrontVal.c_str());
	//Wire.endTransmission();
//}

void LCDLabels::IndicateMode()
{
	if (Mode == LABEL_CLEAR)
	{
		DrawRect(0, X1, Y1, X2, Y2);
	}
	else if (Mode == LABEL_HOVER)
	{
		DrawLine(1, X1, Y2, X2, Y2);
	}
	else if (Mode == LABEL_SELECTED)
	{
		DrawRect(1, X1, Y1, X2, Y2);
	}
}

void LCDLabels::DrawLine(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2)
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

void LCDLabels::DrawRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2)
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

void LCDLabels::DrawFilledRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2)
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

////////////////////////////////////////////////////////////////////////////////
//						High-Level Commands									  //
////////////////////////////////////////////////////////////////////////////////

void LCDLabels::UpCommand()
{
	if (Type == LABEL_VALUE_NUMBER)
		setBackVal((BackVal+LittleInc <= MaxVal ? BackVal+LittleInc : MaxVal ));
	else if (Type == LABEL_VALUE_NOTE) {}
		//Something To Be Decided
}
void LCDLabels::DownCommand()
{
	if (Type == LABEL_VALUE_NUMBER)
		setBackVal((BackVal-LittleInc >= MinVal ? BackVal-LittleInc : MinVal ));
	else if (Type == LABEL_VALUE_NOTE) {}
	//Something To Be Decided
}
void LCDLabels::LeftCommand()
{
	if (Type == LABEL_VALUE_NUMBER)
		setBackVal((BackVal-BigInc >= MinVal ? BackVal-BigInc : MinVal ));
	else if (Type == LABEL_VALUE_NOTE) {}
	//Something To Be Decided
}
void LCDLabels::RightCommand()
{
	if (Type == LABEL_VALUE_NUMBER)
		setBackVal((BackVal+BigInc <= MaxVal ? BackVal+BigInc : MaxVal ));
	else if (Type == LABEL_VALUE_NOTE) {}
	//Something To Be Decided
}
void LCDLabels::EnterCommand()
{
	
}
