// LCDMenu.h

#ifndef _LCDMENU_h
#define _LCDMENU_h

#include "ArchInterfaceManager.h"

class LCDMenu
{
//variables
public:



protected:
private:

LCDLabels* DrawList;
LCDLabels* CursorHome;
LCDMenu* ReturnMenu;

uint8_t WhichMenuMode;


//functions
public:
//Constructors and Destructor
LCDMenu(uint8_t NewWhichMenuMode);
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
void CallEnterPull();
void CallEnterCommit();

protected:


private:

void ChromaticEnterPull();
void ChromaticEnterCommit();
void CustomEnterPull();
void CustomEnterCommit();
void CustomRegionEnterPull();
void CustomRegionEnterCommit();
void PitchBendingEnterPull();
void PitchBendingEnterCommit();

};

#endif