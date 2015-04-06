// LCDMenuSetup.h

#ifndef _LCDMENUSETUP_h
#define _LCDMENUSETUP_h

#ifndef __ARCHLCD_H__
#define __ARCHLCD_H__
#include "ArchLCD.h"
#endif

LCDMenu* DefineMenu_OperationMode();
LCDMenu* DefineMenu_ChromaticMode();
LCDMenu* DefineMenu_CustomMappingMode();
LCDMenu* DefineMenu_PitchBendingMode();

#endif

