// LCDMenuSetup.h

#include "LCDMenuSetup.h"


LCDMenu* DefineMenu_PitchBendingMode() {return NULL;}

LCDMenu* DefineMenu_OperationMode()
{
	//Define Menu Variables and Labels
	static LCDMenu OperationMode(NULL, NULL);
	static LCDLabels Title(1, 10, 0, LABEL_PLAIN_TEXT, "OPERATION MODES:");
	static LCDLabels Chromatic(2, 10, 14, LABEL_MENU_PTR, "1) Chromatic");
	static LCDLabels Custom(3, 10, 28, LABEL_MENU_PTR, "2) Custom Mapping");
	static LCDLabels PitchBending(4, 10, 42, LABEL_MENU_PTR, "3) Pitch Bending");
	
	//Form the Draw Linked List for Menu
	OperationMode.setDrawList(&Title);
	Title.setNext(&Chromatic);
	Chromatic.setNext(&Custom);
	Custom.setNext(&PitchBending);
	PitchBending.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	OperationMode.setCursorHome(&Chromatic);
	Chromatic.setQuadPtr(&PitchBending, &Custom, NULL, NULL);
	Custom.setQuadPtr(&Chromatic, &PitchBending, NULL, NULL);
	PitchBending.setQuadPtr(&Custom, &Chromatic, NULL, NULL);
	
	//Set up the MenuPtrs
	Chromatic.setNextMenu(DefineMenu_ChromaticMode());
	Custom.setNextMenu(DefineMenu_CustomMode());
	PitchBending.setNextMenu(DefineMenu_PitchBendingMode());
	
	return &OperationMode;
}

LCDMenu* DefineMenu_ChromaticMode()
{
	//Define Menu Variables and Labels
	static LCDMenu ChromaticMode(ChromaticEnterPull, ChromaticEnterCommit);
	static LCDLabels Title(1, 10, 0, LABEL_PLAIN_TEXT, "CHROMATIC MODE:");
	static LCDLabels NumRegionsTag(2, 10, 14, LABEL_PLAIN_TEXT, "# of Regions: ");
	static LCDLabels NumRegionsVal(3, 110, 14, LABEL_VALUE_NUMBER, 30, 1, 5, 0, 99);
	static LCDLabels StartNoteTag(4, 10, 28, LABEL_PLAIN_TEXT, "Start Note: ");
	static LCDLabels StartNoteVal(5, 110, 28, LABEL_VALUE_NOTE, 0, 1, 12, 0, 127);
	
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

LCDMenu* DefineMenu_CustomMode()
{
	//Define Menu Variables and Labels
	static LCDMenu CustomMode(CustomEnterPull, CustomEnterCommit);
	static LCDLabels Title(1, 10, 0, LABEL_PLAIN_TEXT, "CUSTOM MODE:");
	static LCDLabels NumRegionsTag(2, 10, 14, LABEL_PLAIN_TEXT, "# of Regions: ");
	static LCDLabels NumRegionsVal(3, 110, 14, LABEL_VALUE_NUMBER, 24, 1, 5, 0, 99);
	static LCDLabels EditRegionTag(4, 10, 28, LABEL_PLAIN_TEXT, "Edit Region: ");
	static LCDLabels EditRegionVal(5, 110, 28, LABEL_VALUE_NUMBER, 0, 1, 5, 0, 99);
	static LCDLabels EditRegionGo(6, 130, 28, LABEL_MENU_PTR, "Enter");
	
	//Form the Draw Linked List for Menu
	CustomMode.setDrawList(&Title);
	Title.setNext(&NumRegionsTag);
	NumRegionsTag.setNext(&NumRegionsVal);
	NumRegionsVal.setNext(&EditRegionTag);
	EditRegionTag.setNext(&EditRegionVal);
	EditRegionVal.setNext(&EditRegionGo);
	EditRegionGo.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	CustomMode.setCursorHome(&NumRegionsVal);
	NumRegionsVal.setQuadPtr(&EditRegionVal, &EditRegionVal, NULL, NULL);
	EditRegionVal.setQuadPtr(&NumRegionsVal, &NumRegionsVal, NULL, &EditRegionGo);
	EditRegionGo.setQuadPtr(NULL, NULL, &EditRegionVal, NULL);
	
	//Set Up the MenuPtrs
	NumRegionsVal.setNextMenu(NULL);
	EditRegionVal.setNextMenu(NULL);
	EditRegionGo.setNextMenu(DefineMenu_CustomRegionMode());
	
	return &CustomMode;
}

LCDMenu* DefineMenu_CustomRegionMode()
{
	//Define Menu Variables and Labels
	static LCDMenu CustomRegionMode(CustomRegionEnterPull, CustomRegionEnterCommit);
	static LCDLabels EditRegionTag(1, 10, 0, LABEL_PLAIN_TEXT, "Edit Region: ");
	static LCDLabels EditRegionVal(2, 110, 0, LABEL_VALUE_NUMBER, 0, 1, 5, 0, 99);
	static LCDLabels StartDegTag(3, 10, 14, LABEL_PLAIN_TEXT, "Start Degrees: ");
	static LCDLabels StartDegVal(4, 110, 14, LABEL_VALUE_NUMBER, 0, 1, 10, 0, 180);
	static LCDLabels EndDegTag(5, 10, 28, LABEL_PLAIN_TEXT, "End Degrees: ");
	static LCDLabels EndDegVal(6, 110, 28, LABEL_VALUE_NUMBER, 0, 1, 10, 0, 180);
	static LCDLabels NoteTag (7, 10, 42, LABEL_PLAIN_TEXT, "Note Value: ");
	static LCDLabels NoteVal (8, 110, 42, LABEL_VALUE_NOTE, 24, 1, 12, 0, 127);
	
	//Form the Draw Linked List for Menu
	CustomRegionMode.setDrawList(&EditRegionTag);
	EditRegionTag.setNext(&EditRegionVal);
	EditRegionVal.setNext(&StartDegTag);
	StartDegTag.setNext(&StartDegVal);
	StartDegVal.setNext(&EndDegTag);
	EndDegTag.setNext(&EndDegVal);
	EndDegVal.setNext(&NoteTag);
	NoteTag.setNext(&NoteVal);
	NoteVal.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	CustomRegionMode.setCursorHome(&StartDegVal);
	StartDegVal.setQuadPtr(&NoteVal, &EndDegVal, NULL, NULL);
	EndDegVal.setQuadPtr(&StartDegVal, &NoteVal, NULL, NULL);
	NoteVal.setQuadPtr(&EndDegVal, &StartDegVal, NULL, NULL);
	
	//Set Up Next Menu Ptrs
	EditRegionVal.setNextMenu(NULL);
	StartDegVal.setNextMenu(NULL);
	EndDegVal.setNextMenu(NULL);
	NoteVal.setNextMenu(NULL);
	
	return &CustomRegionMode;
}

void ChromaticEnterPull(ArchRegionManager* RegionManager, LCDMenu* Menu)
{
	LCDLabels* NumRegionsVal = Menu->getCursorHome();
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	
	NumRegionsVal->setTempVal(RegionManager->NumRegions());
	NumRegionsVal->setBackVal(RegionManager->NumRegions());
	
	StartNoteVal->setTempVal(RegionManager->FindRegionById(1)->GetNote());
	StartNoteVal->setBackVal(RegionManager->FindRegionById(1)->GetNote());	
}
void ChromaticEnterCommit(ArchRegionManager* RegionManager, LCDMenu* Menu)
{
	LCDLabels* NumRegionsVal = Menu->getCursorHome();
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	
	NumRegionsVal->setBackVal(NumRegionsVal->getTempVal());
	StartNoteVal->setBackVal(StartNoteVal->getTempVal());
	
	RegionManager->Initialize(NumRegionsVal->getTempVal(), StartNoteVal->getTempVal());
}
void CustomEnterPull(ArchRegionManager* RegionManager, LCDMenu* Menu)
{
	LCDLabels* NumRegionsVal = Menu->getCursorHome();
	LCDLabels* EditRegionVal = NumRegionsVal->getDown();
	LCDLabels* EditRegionGo = EditRegionVal->getRight();
	
	NumRegionsVal->setTempVal(RegionManager->NumRegions());
	NumRegionsVal->setBackVal(RegionManager->NumRegions());
	
	EditRegionVal->setTempVal(1);
	EditRegionVal->setBackVal(1);
	EditRegionVal->setMinVal(1);
	EditRegionVal->setMaxVal(NumRegionsVal->getBackVal());
}
void CustomEnterCommit(ArchRegionManager* RegionManager, LCDMenu* Menu)
{
	LCDLabels* NumRegionsVal = Menu->getCursorHome();
	LCDLabels* EditRegionVal = NumRegionsVal->getDown();
	LCDLabels* EditRegionGo = EditRegionVal->getRight();
	
	NumRegionsVal->setBackVal(NumRegionsVal->getTempVal());
	//RegionManager->Initialize(NumRegionsVal->getBackVal(), RegionManager->FindRegionById(1)->GetNote());

	EditRegionVal->setMaxVal(NumRegionsVal->getBackVal());
	if (EditRegionVal->getBackVal() > EditRegionVal->getMaxVal())
	{
		EditRegionVal->setBackVal(EditRegionVal->getMaxVal());
		EditRegionVal->setTempVal(EditRegionVal->getMaxVal());
	}

}
void CustomRegionEnterPull(ArchRegionManager* RegionManager, LCDMenu* Menu)
{
	LCDLabels* EditRegionVal = (Menu->getDrawList())->getNext();
	LCDLabels* StartDegVal = Menu->getCursorHome();
	LCDLabels* EndDegVal = StartDegVal->getDown();
	LCDLabels* NoteVal = EndDegVal->getDown();
	
	EditRegionVal->setBackVal(Menu->getReturnMenu()->getCursorHome()->getDown()->getBackVal());
	StartDegVal->setBackVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->startDeg));
	StartDegVal->setTempVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->startDeg));
	EndDegVal->setBackVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->endDeg));
	EndDegVal->setTempVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->endDeg));
	NoteVal->setBackVal(RegionManager->FindRegionById(EditRegionVal->getBackVal())->GetNote());
	NoteVal->setTempVal(RegionManager->FindRegionById(EditRegionVal->getBackVal())->GetNote());
	Serial.println("Helllllo");
}
void CustomRegionEnterCommit(ArchRegionManager* RegionManager, LCDMenu* Menu)
{
	LCDLabels* EditRegionVal = (Menu->getDrawList())->getNext();
	LCDLabels* StartDegVal = Menu->getCursorHome();
	LCDLabels* EndDegVal = StartDegVal->getDown();
	LCDLabels* StartNote = EndDegVal->getDown();
}