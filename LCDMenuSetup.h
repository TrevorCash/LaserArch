// LCDMenuSetup.h

#ifndef _LCDMENUSETUP_h
#define _LCDMENUSETUP_h

#include "ArchInterfaceManager.h"

LCDMenu* DefineMenu_OperationMode();
LCDMenu* DefineMenu_ChromaticMode();
LCDMenu* DefineMenu_CustomMode();
LCDMenu* DefineMenu_CustomRegionMode();
LCDMenu* DefineMenu_PitchBendingMode();

void ChromaticEnterPull(ArchRegionManager* RegionManager, LCDMenu* Menu);
void ChromaticEnterCommit(ArchRegionManager* RegionManager, LCDMenu* Menu);
void CustomEnterPull(ArchRegionManager* RegionManager, LCDMenu* Menu);
void CustomEnterCommit(ArchRegionManager* RegionManager, LCDMenu* Menu);
void CustomRegionEnterPull(ArchRegionManager* RegionManager, LCDMenu* Menu);
void CustomRegionEnterCommit(ArchRegionManager* RegionManager, LCDMenu* Menu);
void PitchBendingEnterPull(ArchRegionManager* RegionManager, LCDMenu* Menu);
void PitchBendingEnterCommit(ArchRegionManager* RegionManager, LCDMenu* Menu);

#endif

