// LCDMenu.h


#ifndef __LCDMENU_INCLUDE
#define __LCDMENU_INCLUDE

#include "Arduino.h"
#include "PrimaryDefines.h"


class LCDLabels;
class ArchRegionManager;

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
ArchRegionManager* RegionManager;


//functions
public:
//Constructors and Destructor
LCDMenu();
LCDMenu(uint8_t NewWhichMode, ArchRegionManager* NewRegionManager);
~LCDMenu();

void Initialize(uint8_t NewWhichMode, ArchRegionManager* NewRegionManager);

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