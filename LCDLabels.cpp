#include "LCDLabels.h"
#include "i2c_t3.h"
#include "ArchLCD.h"

////////////////////////////////////////////////////////////////////////////////
//						Constructors/Destructors							  //
////////////////////////////////////////////////////////////////////////////////

LCDLabels::LCDLabels()
{
	//Nothing	
}
LCDLabels::LCDLabels(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, char* NewFrontVal)
{
	LCD = NewLCD;
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
LCDLabels::LCDLabels(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, uint16_t NewBackVal, uint8_t NewLittleInc, uint8_t NewBigInc, uint16_t NewMinVal, uint16_t NewMaxVal)
{
	LCD = NewLCD;
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
	else if (Type == LABEL_VALUE_COLOR)
		FrontVal = ColorToString(BackVal);
	else if (Type == LABEL_VALUE_SCALE)
		FrontVal = ScaleToString(BackVal);

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

void LCDLabels::Initialize(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, char* NewFrontVal)
{
	LCD = NewLCD;
	ID = NewID;
	X1 = NewX1;
	Y1 = NewY1;
	
	Type = NewType;
	Mode = LABEL_CLEAR;
	FrontVal = NewFrontVal;
	X2 = X1 + 7*FrontVal.length() + 2;
	Y2 = Y1 + 11;
}
void LCDLabels::Initialize(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, uint16_t NewBackVal, uint8_t NewLittleInc, uint8_t NewBigInc, uint16_t NewMinVal, uint16_t NewMaxVal)
{
	LCD = NewLCD;
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
	else if (Type == LABEL_VALUE_COLOR)
		FrontVal = MIDItoString(BackVal);
		
	X2 = X1 + 7*FrontVal.length() + 2;
	Y2 = Y1 + 11;

	LittleInc = NewLittleInc;
	BigInc = NewBigInc;
	MinVal = NewMinVal;
	MaxVal = NewMaxVal;
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
void LCDLabels::setLCD(ArchLCD* NewLCD)
{
	LCD = NewLCD;
}
ArchLCD* LCDLabels::getLCD()
{
	return LCD;
}


void LCDLabels::setFrontVal(String str)
{
	FrontVal = str;
	AutoResizeLabel();
}

String LCDLabels::getFrontVal()
{
	return FrontVal;
}

void LCDLabels::setBackVal(uint16_t NewBackVal)
{
	BackVal = NewBackVal;
	if (Type == LABEL_VALUE_NUMBER)
		setFrontVal((String)(BackVal));
	else if (Type == LABEL_VALUE_NOTE)
		setFrontVal(MIDItoString((uint8_t)(BackVal)));
	else if (Type == LABEL_VALUE_COLOR)
		setFrontVal(ColorToString(BackVal));
	else if (Type == LABEL_VALUE_SCALE)
		setFrontVal(ScaleToString(BackVal));
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
	else if (Type == LABEL_VALUE_COLOR)
		setFrontVal(ColorToString(TempVal));
	else if (Type == LABEL_VALUE_SCALE)
		setFrontVal(ScaleToString(TempVal));
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
void LCDLabels::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
	if (red == 255 && green == 0 && blue == 0)
		setBackVal(COLOR_RED);
	if (red == 255 && green == 102 & blue == 0)
		setBackVal(COLOR_ORANGE);
	if (red == 255 && green == 255 && blue == 0)
		setBackVal(COLOR_YELLOW);
	if (red == 0 && green == 255 && blue == 0)
		setBackVal(COLOR_GREEN);
	if (red == 0 && green == 0 && blue == 255)
		setBackVal(COLOR_BLUE);
	if (red == 85 && green == 26 && blue == 139)
		setBackVal(COLOR_PURPLE);
	if (red == 0 && green == 255 && blue == 255)
		setBackVal(COLOR_CYAN);
}
void LCDLabels::getRGB(uint8_t& red, uint8_t& green, uint8_t& blue)
{
	if (Type != LABEL_VALUE_COLOR)
		return;

	if (BackVal == COLOR_RED)
	{
		red = 255;
		green = 0;
		blue = 0;
	}
	else if (BackVal == COLOR_GREEN)
	{
		red = 0;
		green = 255;
		blue = 0;
	}
	else if (BackVal == COLOR_BLUE)
	{
		red = 0;
		green = 0;
		blue = 255;
	}
	else if (BackVal == COLOR_CYAN)
	{
		red = 0;
		green = 255;
		blue = 255;
	}
	else if (BackVal == COLOR_YELLOW)
	{
		red = 255;
		green = 255;
		blue = 0;
	}
	else if (BackVal == COLOR_ORANGE)
	{
		red = 0xFF;
		green = 0x66;
		blue = 0;
	}
	else if (BackVal == COLOR_PURPLE)
	{
		red = 85;
		green = 26;
		blue = 139;
	}

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

void LCDLabels::UpdateLabel()
{
	LCD->DrawFilledRect(0, X1, Y1, X2, Y2);
	LCD->DrawLabel(X1, Y1, FrontVal.c_str());
	IndicateMode();
}

void LCDLabels::ClearLabel()
{
	LCD->DrawFilledRect(0, X1, Y1, X2, Y2);
}

void LCDLabels::AutoResizeLabel()
{
	ClearLabel();
	X2 = X1 + 7*FrontVal.length() + 2;
	Y2 = Y1 + 11;
	LCD->DrawLabel(X1, Y1, FrontVal.c_str());
	IndicateMode();
}

void LCDLabels::IndicateMode()
{
	if (Mode == LABEL_CLEAR)
	{
		LCD->DrawRect(0, X1, Y1, X2, Y2);
	}
	else if (Mode == LABEL_HOVER)
	{
		LCD->DrawLine(1, X1, Y2, X2, Y2);
	}
	else if (Mode == LABEL_SELECTED)
	{
		LCD->DrawRect(1, X1, Y1, X2, Y2);
	}
}



////////////////////////////////////////////////////////////////////////////////
//						High-Level Commands									  //
////////////////////////////////////////////////////////////////////////////////

void LCDLabels::UpCommand()
{
	int tmp = int(TempVal)+LittleInc;
	if (tmp > MaxVal && Type)
		tmp = tmp - MaxVal + MinVal - 1;
	setTempVal(uint16_t(tmp));
}
void LCDLabels::DownCommand()
{
	int tmp = int(TempVal) - LittleInc;
	if (tmp < MinVal && Type)
		tmp = tmp + MaxVal - MinVal + 1;
	setTempVal(uint16_t(tmp));
}
void LCDLabels::LeftCommand()
{
	int tmp = int(TempVal) - BigInc;
	if (tmp < MinVal && Type != LABEL_VALUE_NOTE)
		tmp = tmp + MaxVal - MinVal +1 ;
	else if (tmp < MinVal && Type == LABEL_VALUE_NOTE)
		if (TempVal < 8)
			tmp = TempVal+120;
		else
			tmp = TempVal+108;
	setTempVal(uint16_t(tmp));
}
void LCDLabels::RightCommand()
{
	int tmp = int(TempVal)+BigInc;
	if (tmp > MaxVal && Type != LABEL_VALUE_NOTE)
		tmp = tmp - MaxVal + MinVal - 1;
	else if (tmp > MaxVal && Type == LABEL_VALUE_NOTE)
		tmp = tmp % 12;
	setTempVal(uint16_t(tmp));
}

////////////////////////////////////////////////////////////////////////////////
//						Private Commands									  //
////////////////////////////////////////////////////////////////////////////////

String LCDLabels::MIDItoString(uint8_t midi)
{
	if (midi > 127)
	{
		String str = "Error: " + String(midi);
		return str.c_str();
	}
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
	return str;
}


String LCDLabels::ColorToString(uint16_t color)
{
	String str;
	if (color == COLOR_RED)
		str = "Red";
	else if (color == COLOR_BLUE)
		str = "Blue";
	else if (color == COLOR_GREEN)
		str = "Green";
	else if (color == COLOR_CYAN)
		str = "Cyan";
	else if (color == COLOR_YELLOW)
		str = "Yellow";
	else if (color == COLOR_ORANGE)
		str = "Orange";
	else if (color == COLOR_PURPLE)
		str = "Purple";
	return str;
}

String LCDLabels::ScaleToString(uint16_t scale)
{
	String str;
	if (scale == ChromaticScheme)
	{
		str = "Chromatic";
	}
	else if (scale == MajorScaleScheme)
	{
		str = "Major";
	}
	else if (scale == MinorScaleScheme)
	{
		str = "Minor";
	}
	return str;
}