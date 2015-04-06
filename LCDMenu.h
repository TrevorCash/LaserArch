// LCDMenu.h

#ifndef _LCDMENU_h
#define _LCDMENU_h

#include "ArchLCD.h"

class LCDMenu
{
//variables
public:



protected:
private:

LCDLabels* DrawList;
LCDLabels* CursorHome;
LCDMenu* ReturnMenu;




//functions
public:
//Constructors and Destructor
LCDMenu();
~LCDMenu();

//Gets and Sets

void setDrawList(LCDLabels* NewDrawList);
LCDLabels* getDrawList();
void setCursorHome(LCDLabels* NewCursorHome);
LCDLabels* getCursorHome();
void setReturnMenu(LCDMenu* NewReturnMenu);
LCDMenu* getReturnMenu();

//Mid Level Commands
void DrawMe();


protected:



private:
};

#endif