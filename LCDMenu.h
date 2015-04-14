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
LCDMenu(void (*NewEnterPull)(ArchRegionManager* RegionManager, LCDMenu* Menu), void (*NewEnterCommit)(ArchRegionManager* RegionManager, LCDMenu* Menu));
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
void (*CallEnterPull)(ArchRegionManager* RegionManager, LCDMenu* Menu);
void (*CallEnterCommit)(ArchRegionManager* RegionManager, LCDMenu* Menu);

protected:


private:
};

#endif