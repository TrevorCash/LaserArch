// LCDMenuSetup.h

#ifndef _LCDMENUSETUP_h
#define _LCDMENUSETUP_h


#include "ArchLCD.h"
#include "LCDMenu.h"
#include "LCDLabels.h"


LCDMenu* DefineMenu_OperationMode();
LCDMenu* DefineMenu_ChromaticMode() {return NULL;}
LCDMenu* DefineMenu_CustomMappingMode() {return NULL;}
LCDMenu* DefineMenu_PitchBendingMode() {return NULL;}

LCDMenu* DefineMenu_OperationMode()
{
	//Define Menu Variables and Labels
	static LCDMenu OperationMode;
	static LCDLabels Title(1, 20, 60, 50, 70, LABEL_PLAIN_TEXT, LABEL_CLEAR, "Operation Modes");
	static LCDLabels Chromatic(2, 20, 50, 50, 60, LABEL_MENU_PTR, LABEL_CLEAR, "Chromatic");
	static LCDLabels CustomMapping(3, 20, 40, 50, 50, LABEL_MENU_PTR, LABEL_CLEAR, "Custom");
	static LCDLabels PitchBending(4, 20, 30, 50, 40, LABEL_MENU_PTR, LABEL_CLEAR, "Pitch Bending");
	
	//Form the Draw Linked List for Menu
	OperationMode.setDrawList(&Title);
	Title.setNext(&Chromatic);
	Chromatic.setNext(&CustomMapping);
	CustomMapping.setNext(&PitchBending);
	PitchBending.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	OperationMode.setCursorHome(&Chromatic);
	Chromatic.setQuadPtr(&PitchBending, &CustomMapping, NULL, NULL);
	CustomMapping.setQuadPtr(&Chromatic, &PitchBending, NULL, NULL);
	PitchBending.setQuadPtr(&CustomMapping, &Chromatic, NULL, NULL);
	
	//Set up the MenuPtrs
	Chromatic.setNextMenu(DefineMenu_ChromaticMode());
	CustomMapping.setNextMenu(DefineMenu_CustomMappingMode());
	PitchBending.setNextMenu(DefineMenu_PitchBendingMode());
	
	return &OperationMode;
}


#endif

