// Labels.h

#ifndef __LCDLABELS_INCLUDE
#define __LCDLABELS_INCLUDE
	
#include "Arduino.h"
#include "PrimaryDefines.h"

class LCDMenu;
class ArchLCD;

class LCDLabels
{
//variables
public:
protected:
private:

	//Additional Variables
	uint8_t Type; // PtrNextMenu or ValueNumber or ValueNote or Plain text
	uint8_t Mode; // Navigation or Selected for Editing
	LCDMenu* NextMenu;
	ArchLCD* LCD;
	
	//Value Variables
	String FrontVal;
	uint16_t BackVal;
	uint16_t TempVal;
	uint8_t LittleInc;
	uint8_t BigInc;
	uint16_t MaxVal;
	uint16_t MinVal;
	
	//Directional Pointers
	LCDLabels* Up;	 // Rest For Navigation 
	LCDLabels* Down;
	LCDLabels* Left;
	LCDLabels* Right;
	LCDLabels* Next; // For Drawing
	
	//Initialization Variables
	uint8_t ID;
	uint8_t X1;
	uint8_t X2;
	uint8_t Y1;
	uint8_t Y2;
	
	//Not Used Unless We Update Firmware to 8.3
	uint8_t VertAlign;
	uint8_t HorizAlign;
	uint16_t FontID;
	uint8_t Background;
	uint8_t CharSpacing;

//functions
public:
//Constructors and Destructor
LCDLabels();
LCDLabels(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, char* NewFrontVal);
LCDLabels(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, uint16_t NewBackVal, uint8_t NewLittleInc, uint8_t NewBigInc, uint16_t NewMinVal, uint16_t NewMaxVal);
~LCDLabels();

void Initialize(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, char* NewFrontVal);
void Initialize(ArchLCD* NewLCD, uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, uint16_t NewBackVal, uint8_t NewLittleInc, uint8_t NewBigInc, uint16_t NewMinVal, uint16_t NewMaxVal);

//Gets and Sets

void setType(uint8_t NewMode);
uint8_t getType();
void setMode(uint8_t NewMode);
uint8_t getMode();
void setNextMenu(LCDMenu* NewNextMenu);
LCDMenu* getNextMenu();
void setLCD(ArchLCD* NewLCD);
ArchLCD* getLCD();

void setFrontVal(String str);

String getFrontVal();
void setBackVal(uint16_t NewBackVal);
uint16_t getBackVal();
void setTempVal(uint16_t NewTempVal);
uint16_t getTempVal();
void setLittleInc(uint8_t NewLittleInc);
uint8_t getLittleInc();
void setBigInc(uint8_t NewBigInc);
uint8_t getBigInc();
void setMaxVal(uint16_t NewMaxVal);
uint16_t getMaxVal();
void setMinVal(uint16_t NewMinVal);
uint16_t getMinVal();
void setColor(uint8_t red, uint8_t green, uint8_t blue);
void getRGB(uint8_t& red, uint8_t& green, uint8_t& blue);


uint8_t getX1();
uint8_t getY1();
uint8_t getX2();
uint8_t getY2();

void setQuadPtr(LCDLabels* NewUp, LCDLabels* NewDown, LCDLabels* NewLeft, LCDLabels* NewRight);
LCDLabels* getLeft();
LCDLabels* getRight();
LCDLabels* getUp();
LCDLabels* getDown();
void setNext(LCDLabels* NewNext);
LCDLabels* getNext();

//Mid Level Commands
void InitializeLabel();
void UpdateLabel();
void ClearLabel();
void AutoResizeLabel();
void IndicateMode();


//High Level Commands
void UpCommand();
void DownCommand();
void LeftCommand();
void RightCommand();
void EnterCommand();

protected:
private:
String MIDItoString(uint8_t midi);
String ColorToString(uint16_t color);
String ScaleToString(uint16_t scale);
};

#endif

