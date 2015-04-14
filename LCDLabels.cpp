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
	FrontVal = NewFrontVal;
	X2 = X1 + 7*FrontVal.length() + 2;
	Y2 = Y1 + 11;

	//Use if update to Firmware Version 8.3
	//VertAlign = 0;
	//HorizAlign = 0;
	//FontID = 1;
	//Background = 0;
	//CharSpacing = 2;
}
LCDLabels::LCDLabels(uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, uint16_t NewBackVal, uint8_t NewLittleInc, uint8_t NewBigInc, uint16_t NewMinVal, uint16_t NewMaxVal)
{
	ID = NewID;
	X1 = NewX1;
	Y1 = NewY1;
	
	Type = NewType;
	Mode = LABEL_CLEAR;
	BackVal = NewBackVal;
	if (Type == LABEL_VALUE_NUMBER)
		FrontVal = (String)(BackVal);
	else if (Type == LABEL_VALUE_NOTE)
		FrontVal = MIDItoString(BackVal);
	X2 = X1 + 7*FrontVal.length() + 2;
	Y2 = Y1 + 11;

	LittleInc = NewLittleInc;
	BigInc = NewBigInc;
	MinVal = NewMinVal;
	MaxVal = NewMaxVal;
	
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

void LCDLabels::setFrontVal(const char* str)
{
	FrontVal = str;
	AutoResizeLabel();
}

const char* LCDLabels::getFrontVal()
{
	return FrontVal.c_str();
}

void LCDLabels::setBackVal(uint16_t NewBackVal)
{
	BackVal = NewBackVal;
	if (Type == LABEL_VALUE_NUMBER)
		setFrontVal((String)(BackVal));
	else if (Type == LABEL_VALUE_NOTE)
		setFrontVal(MIDItoString((uint8_t)(TempVal)));
}

uint16_t LCDLabels::getBackVal()
{
	return BackVal;
}
void LCDLabels::setTempVal(uint16_t NewTempVal)
{
	TempVal = NewTempVal;
	if (Type == LABEL_VALUE_NUMBER)
		setFrontVal((String)(TempVal));
	else if (Type == LABEL_VALUE_NOTE)
		setFrontVal(MIDItoString((uint8_t)(TempVal)));
}
uint16_t LCDLabels::getTempVal()
{
	return TempVal;
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

uint8_t LCDLabels::getX1()
{
	return X1;
}
uint8_t LCDLabels::getY1()
{
	return Y1;
}
uint8_t LCDLabels::getX2()
{
	return X2;
}
uint8_t LCDLabels::getY2()
{
	return Y2;
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
	Wire.write(Y1+2);
	Wire.endTransmission();
	
	Wire.beginTransmission(ORBITAL_I2C_ADDRESS);
	Wire.write(FrontVal.c_str());
	Wire.endTransmission();
}

void LCDLabels::UpdateLabel()
{
	DrawFilledRect(0, X1, Y1, X2, Y2);
	InitializeLabel();
	IndicateMode();
}

void LCDLabels::ClearLabel()
{
	DrawFilledRect(0, X1, Y1, X2, Y2);
}

void LCDLabels::AutoResizeLabel()
{
	ClearLabel();
	X2 = X1 + 7*FrontVal.length() + 2;
	Y2 = Y1 + 11;
	InitializeLabel();
	IndicateMode();
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
		DrawLine(1, X1, Y2,X2, Y2);
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
	setTempVal((TempVal+LittleInc <= MaxVal ? TempVal+LittleInc : MaxVal ));
}
void LCDLabels::DownCommand()
{
	setTempVal((TempVal-LittleInc >= MinVal ? TempVal-LittleInc : MinVal ));
}
void LCDLabels::LeftCommand()
{
	setTempVal((TempVal-BigInc >= MinVal ? TempVal-BigInc : MinVal ));
}
void LCDLabels::RightCommand()
{
	setTempVal(((TempVal+BigInc) <= MaxVal ? TempVal+BigInc : MaxVal ));
}

////////////////////////////////////////////////////////////////////////////////
//						Private Commands									  //
////////////////////////////////////////////////////////////////////////////////

const char* LCDLabels::MIDItoString(uint8_t midi)
{
	if (midi > 127)
	return "Error";
	String str;
	if (midi % 12 == 0)
	str = "C";
	else if (midi % 12 == 1)
	str = "C#/Db";
	else if (midi % 12 == 2)
	str = "D";
	else if (midi % 12 == 3)
	str = "D#/Eb";
	else if (midi % 12 == 4)
	str = "E";
	else if (midi % 12 == 5)
	str = "F";
	else if (midi % 12 == 6)
	str = "F#/Gb";
	else if (midi % 12 == 7)
	str = "G";
	else if (midi % 12 == 8)
	str = "G#/Ab";
	else if (midi % 12 == 9)
	str = "A";
	else if (midi % 12 == 10)
	str = "A#/Bb";
	else if (midi % 12 == 11)
	str = "B";
	str += "-" + (String)((int)(midi/12));
	return str.c_str();
}