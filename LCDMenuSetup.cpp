// LCDMenuSetup.h

#include "LCDMenuSetup.h"

LCDMenu* DefineMenu_CustomMappingMode() {return NULL;}
LCDMenu* DefineMenu_PitchBendingMode() {return NULL;}

LCDMenu* DefineMenu_OperationMode()
{
	//Define Menu Variables and Labels
	static LCDMenu OperationMode;
	static LCDLabels Title(1, 10, 0, LABEL_PLAIN_TEXT, "OPERATION MODES:");
	static LCDLabels Chromatic(2, 10, 14, LABEL_MENU_PTR, "1) Chromatic");
	static LCDLabels CustomMapping(3, 10, 28, LABEL_MENU_PTR, "2) Custom Mapping");
	static LCDLabels PitchBending(4, 10, 42, LABEL_MENU_PTR, "3) Pitch Bending");
	
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

LCDMenu* DefineMenu_ChromaticMode()
{
	static LCDMenu ChromaticMode;
	
	//Define Menu Variables and Labels
	static LCDLabels Title(1, 10, 0, LABEL_PLAIN_TEXT, "CHROMATIC MODE:");
	static LCDLabels NumRegionsTag(2, 10, 14, LABEL_PLAIN_TEXT, "# of Regions: ");
	static LCDLabels NumRegionsVal(3, 110, 14, LABEL_VALUE_NUMBER, 24, 1, 5, 0, 99);
	static LCDLabels StartNoteTag(4, 10, 28, LABEL_PLAIN_TEXT, "Start Note: ");
	static LCDLabels StartNoteVal(5, 110, 28, LABEL_VALUE_NOTE, "C#");
	
	//Form the Draw Linked List for Menu
	ChromaticMode.setDrawList(&Title);
	Title.setNext(&NumRegionsTag);
	NumRegionsTag.setNext(&NumRegionsVal);
	NumRegionsVal.setNext(&StartNoteTag);
	StartNoteTag.setNext(&StartNoteVal);
	StartNoteVal.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	ChromaticMode.setCursorHome(&NumRegionsVal);
	NumRegionsVal.setQuadPtr(&StartNoteVal, &StartNoteVal, NULL, NULL);
	StartNoteVal.setQuadPtr(&NumRegionsVal, &NumRegionsVal, NULL, NULL);
	
	//Set up the MenuPtrs
	NumRegionsVal.setNextMenu(NULL);
	StartNoteVal.setNextMenu(NULL);
	
	return &ChromaticMode;
}