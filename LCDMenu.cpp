#include "LCDMenu.h"
#include "LCDLabels.h"
#include "ArchLCD.h"
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
	if (ptr == NULL)
		return;
	do
	{
		ptr->setMode(LABEL_CLEAR);
		ptr->getLCD()->DrawLabel(ptr->getX1(), ptr->getY1(), ptr->getFrontVal().c_str());
		ptr = ptr->getNext();
	} while (ptr != NULL);
}

void LCDMenu::CallEnterPull()
{
	if (WhichMenuMode == MENU_OPMODE)
		OpModeEnterPull();
	else if (WhichMenuMode == MENU_CHROMATIC)
		ChromaticEnterPull();
	else if (WhichMenuMode == MENU_CUSTOM)
		CustomEnterPull();
	else if (WhichMenuMode == MENU_CUSTOM_REGION)
		CustomRegionEnterPull();
	else if (WhichMenuMode == MENU_SCALE)
		ScaleEnterPull();
}
void LCDMenu::CallEnterCommit()
{
	if (WhichMenuMode == MENU_OPMODE)
		OpModeEnterCommit();
	else if (WhichMenuMode == MENU_CHROMATIC)
		ChromaticEnterCommit();
	else if (WhichMenuMode == MENU_CUSTOM)
		CustomEnterCommit();
	else if (WhichMenuMode == MENU_CUSTOM_REGION)
		CustomRegionEnterCommit();
	else if (WhichMenuMode == MENU_SCALE)
		ScaleEnterCommit();
}


////////////////////////////////////////////////////////////////////////////////
//						CommitPullFunctions									  //
////////////////////////////////////////////////////////////////////////////////

void LCDMenu::OpModeEnterPull()
{
	LCDLabels* ChromaticMode = CursorHome;
	LCDLabels* CustomMode = ChromaticMode->getDown();
	LCDLabels* ScaleMode = CustomMode->getDown();
	
	//ChromaticMode->setMode(LABEL_CLEAR);
	//CustomMode->setMode(LABEL_CLEAR);
	//ScaleMode->setMode(LABEL_CLEAR);
}
void LCDMenu::OpModeEnterCommit()
{
	
}

void LCDMenu::ChromaticEnterPull()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	
	NumRegionsVal->setTempVal(RegionManager->NumRegions());
	NumRegionsVal->setBackVal(RegionManager->NumRegions());
	
	StartNoteVal->setTempVal(RegionManager->FirstRegion()->GetNote());
	StartNoteVal->setBackVal(RegionManager->FirstRegion()->GetNote());
	
	NumRegionsVal->setMode(LABEL_CLEAR);
	StartNoteVal->setMode(LABEL_CLEAR);
	
	ArchRegionScheme Scheme(ChromaticScheme, StartNoteVal->getTempVal(), NumRegionsVal->getTempVal());
	RegionManager->Initialize(Scheme);
}
void LCDMenu::ChromaticEnterCommit()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	ArchRegionScheme Scheme(ChromaticScheme, StartNoteVal->getTempVal(), NumRegionsVal->getTempVal());
	
	NumRegionsVal->setBackVal(NumRegionsVal->getTempVal());
	StartNoteVal->setBackVal(StartNoteVal->getTempVal());
	
	RegionManager->Initialize(Scheme);
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
	if (RegionManager->GetSchemeType() != TriggerScheme)
	{
		ArchRegionScheme Scheme(TriggerScheme, RegionManager->FindRegionById(0)->GetNote(), NumRegionsVal->getTempVal());
		RegionManager->Initialize(Scheme);
	}
}
void LCDMenu::CustomEnterCommit()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* EditRegionVal = NumRegionsVal->getDown();
	LCDLabels* EditRegionGo = EditRegionVal->getRight();
	ArchRegionScheme Scheme(TriggerScheme, RegionManager->FindRegionById(1)->GetNote(), NumRegionsVal->getTempVal());
	
	NumRegionsVal->setBackVal(NumRegionsVal->getTempVal());
	RegionManager->Initialize(Scheme);

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
	LCDLabels* ColorVal = NoteVal->getDown();
	uint8_t red, green, blue;
	
	EditRegionVal->setBackVal(ReturnMenu->getCursorHome()->getDown()->getBackVal());
	StartDegVal->setBackVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->startDeg));
	StartDegVal->setTempVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->startDeg));
	EndDegVal->setBackVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->endDeg));
	EndDegVal->setTempVal(uint16_t(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->endDeg));
	NoteVal->setBackVal(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->GetNote());
	NoteVal->setTempVal(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->GetNote());
	
	RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->GetColors(red, green, blue);
	ColorVal->setColor(red, green, blue);
	ColorVal->setTempVal(ColorVal->getBackVal());
}
void LCDMenu::CustomRegionEnterCommit()
{
	LCDLabels* EditRegionVal = (DrawList->getNext());
	LCDLabels* StartDegVal = CursorHome;
	LCDLabels* EndDegVal = StartDegVal->getDown();
	LCDLabels* NoteVal = EndDegVal->getDown();
	LCDLabels* ColorVal = NoteVal->getDown();
	uint8_t red, green, blue;
	ArchRegion* Region = RegionManager->FindRegionById(EditRegionVal->getBackVal()-1);
	ArchRegion* FirstRegion = RegionManager->FirstRegion();
	ArchRegion* LastRegion = RegionManager->LastRegion();
	bool result = true;
	
	if (StartDegVal->getBackVal() != StartDegVal->getTempVal())
	{		
		result = RegionManager->ModifyRegionSpanStart(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1),
		StartDegVal->getTempVal(),
		ArchRegionManager::RegionLinearStretch);

		if (result)
			StartDegVal->setBackVal(StartDegVal->getTempVal());
		else
			StartDegVal->setTempVal(StartDegVal->getBackVal());
		
	}
	else if (EndDegVal->getBackVal() != EndDegVal->getTempVal())
	{
		result = RegionManager->ModifyRegionSpanEnd(RegionManager->FindRegionById(EditRegionVal->getBackVal()-1),
		EndDegVal->getTempVal(),
		ArchRegionManager::RegionLinearStretch);

		if (result)
			EndDegVal->setBackVal(EndDegVal->getTempVal());
		else
			EndDegVal->setTempVal(EndDegVal->getBackVal());
	}
	else if (NoteVal->getBackVal() != NoteVal->getTempVal())
	{
		NoteVal->setBackVal(NoteVal->getTempVal());
		RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->SetNote(NoteVal->getBackVal());
	}
	else if (ColorVal->getBackVal() != ColorVal->getTempVal())
	{
		ColorVal->setBackVal(ColorVal->getTempVal());
		ColorVal->getRGB(red, green, blue);
		RegionManager->FindRegionById(EditRegionVal->getBackVal()-1)->SetColors(red, green, blue);	
	}
	
	if (result)
	{
		EditRegionVal->setBackVal(Region->index+1);
		EditRegionVal->setTempVal(Region->index+1);
		
	}
}

void LCDMenu::ScaleEnterPull()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	LCDLabels* ScaleVal = StartNoteVal->getDown();
	
	NumRegionsVal->setTempVal(RegionManager->NumRegions());
	NumRegionsVal->setBackVal(RegionManager->NumRegions());
	
	StartNoteVal->setTempVal(RegionManager->FirstRegion()->GetNote());
	StartNoteVal->setBackVal(RegionManager->FirstRegion()->GetNote());
	
	ScaleVal->setTempVal(RegionManager->GetSchemeType());
	ScaleVal->setBackVal(RegionManager->GetSchemeType());
	
	if (ScaleVal->getBackVal() < ScaleVal->getMinVal() || ScaleVal->getBackVal() > ScaleVal->getMaxVal())
	{
		ScaleVal->setTempVal(MajorScaleScheme);
		ScaleVal->setBackVal(MajorScaleScheme);
	}
	
	NumRegionsVal->setMode(LABEL_CLEAR);
	StartNoteVal->setMode(LABEL_CLEAR);
	ScaleVal->setMode(LABEL_CLEAR);	
	
	ArchRegionScheme Scheme((ArchRegionSchemes)ScaleVal->getBackVal(), StartNoteVal->getBackVal(), NumRegionsVal->getBackVal());
	RegionManager->Initialize(Scheme);
}
void LCDMenu::ScaleEnterCommit()
{
	LCDLabels* NumRegionsVal = CursorHome;
	LCDLabels* StartNoteVal = NumRegionsVal->getDown();
	LCDLabels* ScaleVal = StartNoteVal->getDown();
	
	NumRegionsVal->setBackVal(NumRegionsVal->getTempVal());
	StartNoteVal->setBackVal(StartNoteVal->getTempVal());
	ScaleVal->setBackVal(ScaleVal->getTempVal());
	
	
	ArchRegionScheme Scheme((ArchRegionSchemes)ScaleVal->getBackVal(), StartNoteVal->getBackVal(), NumRegionsVal->getBackVal());
	RegionManager->Initialize(Scheme);
	
}