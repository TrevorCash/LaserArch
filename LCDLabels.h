// Labels.h

#ifndef _LCDLABELS_h
#define _LCDLABELS_h

#include "ArchInterfaceManager.h"


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
	
	//Value Vairables
	String FrontVal;
	uint16_t BackVal;
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
LCDLabels(uint8_t NewID, uint8_t NewX1, uint8_t NewY1, uint8_t NewType, char* NewFrontVal);
LCDLabels(uint8_t NewID, uint8_t NewX, uint8_t NewY1, uint8_t NewType, uint16_t NewBackVal, uint8_t NewLittleInc, uint8_t NewBigInc, uint16_t NewMinVal, uint16_t NewMaxVal);
~LCDLabels();

//Gets and Sets

void setType(uint8_t NewMode);
uint8_t getType();
void setMode(uint8_t NewMode);
uint8_t getMode();
void setNextMenu(LCDMenu* NewNextMenu);
LCDMenu* getNextMenu();

void setFrontVal(const char* str);
inline void setFrontVal(String str) { setFrontVal(str.c_str()); }

const char* getFrontVal();
void setBackVal(uint16_t NewBackVal);
uint16_t getBackVal();
void setLittleInc(uint8_t NewLittleInc);
uint8_t getLittleInc();
void setBigInc(uint8_t NewBigInc);
uint8_t getBigInc();
void setMaxVal(uint16_t NewMaxVal);
uint16_t getMaxVal();
void setMinVal(uint16_t NewMinVal);
uint16_t getMinVal();

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
void DrawLine(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
void DrawRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
void DrawFilledRect(uint8_t color, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);

//High Level Commands
void UpCommand();
void DownCommand();
void LeftCommand();
void RightCommand();
void EnterCommand();
void (LCDLabels::*EnterPull)();
void (LCDLabels::*EnterCommit)();



protected:
private:
};

#endif

