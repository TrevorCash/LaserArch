#include "LCDMenu.h"
#include "LCDLabels.h"
#include "ArchInterfaceManager.h"

LCDMenu::LCDMenu()
{
	
}
LCDMenu::LCDMenu(uint8_t NewWhichMode, ArchRegionManager* NewRegionManager) 
{
	WhichMenuMode = NewWhichMode;
	RegionManager = NewRegionManager;
}
LCDMenu::~LCDMenu() {}

void LCDMenu::Initialize(uint8_t NewWhichMode, ArchRegionManager* NewRegionManager)
{
	WhichMenuMode = NewWhichMode;
	RegionManager = NewRegionManager;
}

////////////////////////////////////////////////////////////////////////////////
//						Gets/Sets											  //
////////////////////////////////////////////////////////////////////////////////

void LCDMenu::setDrawList(LCDLabels* NewDrawList)
{
	DrawList = NewDrawList;
}
LCDLabels* LCDMenu::getDrawList()
{
	return DrawList;
}

void LCDMenu::setCursorHome(LCDLabels* NewCursorHome)
{
	CursorHome = NewCursorHome;
}
LCDLabels* LCDMenu::getCursorHome()
{
	return CursorHome;
}

void LCDMenu::setReturnMenu(LCDMenu* NewReturnMenu)
{
	ReturnMenu = NewReturnMenu;
}
LCDMenu* LCDMenu::getReturnMenu()
{
	return ReturnMenu;
}

////////////////////////////////////////////////////////////////////////////////
//						Mid-Level											  //
////////////////////////////////////////////////////////////////////////////////

void LCDMenu::DrawMe()
{
	LCDLabels* ptr = DrawList;
	do
	{
		ptr->InitializeLabel();
		//ptr->UpdateLabel();
		ptr = ptr->getNext();
	} while (ptr != NULL);
}

void LCDMenu::CallEnterPull()
{
	if (WhichMenuMode == MENU_NONE)
		return;
	else if (WhichMenuMode == MENU_CHROMATIC)
		ChromaticEnterPull();
	else if (WhichMenuMode == MENU_CUSTOM)
		CustomEnterPull();
	else if (WhichMenuMode == MENU_CUSTOM_REGION)
		CustomRegionEnterPull();
}
void LCDMenu::CallEnterCommit()
{
	if (WhichMenuMode == MENU_NONE)
	return;
	else if (WhichMenuMode == MENU_CHROMATIC)
		ChromaticEnterCommit();
	else if (WhichMenuMode == MENU_CUSTOM)
		CustomEnterCommit();
	else if (WhichMenuMode == MENU_CUSTOM_REGION)
		CustomRegionEnterCommit();
}


////////////////////////////////////////////////////////////////////////////////
//						CommitPullFunctions									  //
////////////////////////////////////////////////////////////////////////////////

void LCDMenu::ChromaticEnterPull()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	
	NumRegionsVal->setTempVal(RegionManager->NumRegions());
	NumRegionsVal->setBackVal(RegionManager->NumRegions());
	
	StartNoteVal->setTempVal(RegionManager->FindRegionById(1)->GetNote());
	StartNoteVal->setBackVal(RegionManager->FindRegionById(1)->GetNote());
}
void LCDMenu::ChromaticEnterCommit()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	
	NumRegionsVal->setBackVal(NumRegionsVal->getTempVal());
	StartNoteVal->setBackVal(StartNoteVal->getTempVal());
	
	RegionManager->Initialize(NumRegionsVal->getTempVal(), StartNoteVal->getTempVal());
}
void LCDMenu::CustomEnterPull()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* EditRegionVal = NumRegionsVal->getDown();
	LCDLabels* EditRegionGo = EditRegionVal->getRight();
	
	NumRegionsVal->setTempVal(RegionManager->NumRegions());
	NumRegionsVal->setBackVal(RegionManager->NumRegions());
	
	EditRegionVal->setTempVal(1);
	EditRegionVal->setBackVal(1);
	EditRegionVal->setMinVal(1);
	EditRegionVal->setMaxVal(NumRegionsVal->getBackVal());
}
void LCDMenu::CustomEnterCommit()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* EditRegionVal = NumRegionsVal->getDown();
	LCDLabels* EditRegionGo = EditRegionVal->getRight();
	
	NumRegionsVal->setBackVal(NumRegionsVal->getTempVal());
	RegionManager->Initialize(NumRegionsVal->getBackVal(), RegionManager->FindRegionById(1)->GetNote());

	EditRegionVal->setMaxVal(NumRegionsVal->getBackVal());
	if (EditRegionVal->getBackVal() > EditRegionVal->getMaxVal())
	{
		EditRegionVal->setBackVal(EditRegionVal->getMaxVal());
		EditRegionVal->setTempVal(EditRegionVal->getMaxVal());
	}

}
void LCDMenu::CustomRegionEnterPull()
{
	LCDLabels* EditRegionVal = DrawList->getNext();
	LCDLabels* StartDegVal = CursorHome;
	LCDLabels* EndDegVal = StartDegVal->getDown();
	LCDLabels* NoteVal = EndDegVal->getDown();
	
	EditRegionVal->setBackVal(ReturnMenu->getCursorHome()->getDown()->getBackVal());
	StartDegVal->setBackVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->startDeg));
	StartDegVal->setTempVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->startDeg));
	EndDegVal->setBackVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->endDeg));
	EndDegVal->setTempVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal())->endDeg));
	NoteVal->setBackVal(RegionManager->FindRegionById(EditRegionVal->getBackVal())->GetNote());
	NoteVal->setTempVal(RegionManager->FindRegionById(EditRegionVal->getBackVal())->GetNote());
}
void LCDMenu::CustomRegionEnterCommit()
{
	LCDLabels* EditRegionVal = (DrawList->getNext());
	LCDLabels* StartDegVal = CursorHome;
	LCDLabels* EndDegVal = StartDegVal->getDown();
	LCDLabels* StartNote = EndDegVal->getDown();
}