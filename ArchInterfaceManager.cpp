/* 
* ArchInterfaceManager.cpp
*
* Created: 2/20/2015 10:37:26 AM
* Author: 7002815
*/


#include "ArchInterfaceManager.h"
#include "ArchLCD.h"

// default constructor
ArchInterfaceManager::ArchInterfaceManager(ArchRegionManager* NewRegionManager)
{
	RegionManager = NewRegionManager;
} //ArchInterfaceManager

// default destructor
ArchInterfaceManager::~ArchInterfaceManager()
{
} //~ArchInterfaceManager

void ArchInterfaceManager::Initialize()
{
	OrbitalLCD->Initialize();
	OrbitalLCD->ClearScreen();
	
	MenuHome = DefineMenu_OperationMode();
	Menu = MenuHome;
	Menu->DrawMe();
	Cursor = Menu->getCursorHome();
	Cursor->setMode(LABEL_HOVER);
}

void ArchInterfaceManager::Update()
{
	uint8_t cmd;
	cmd = OrbitalLCD->ReadKey();
	if (cmd == LCD_UP)
	{
		if (Cursor->getMode() == LABEL_HOVER && Cursor->getUp() != NULL)
		{
			Cursor->setMode(LABEL_CLEAR);
			Cursor = Cursor->getUp();
			Cursor->setMode(LABEL_HOVER);
		}
		else if (Cursor->getMode() == LABEL_SELECTED)
		{
			Cursor->UpCommand();
			Cursor->UpdateLabel();
		}
	}
	else if(cmd == LCD_DOWN)
	{
		if (Cursor->getMode() == LABEL_HOVER && Cursor->getDown() != NULL)
		{
			Cursor->setMode(LABEL_CLEAR);
			Cursor = Cursor->getDown();
			Cursor->setMode(LABEL_HOVER);
		}
		else if (Cursor->getMode() == LABEL_SELECTED)
		{
			Cursor->DownCommand();
			Cursor->UpdateLabel();
		}
	}
	else if(cmd == LCD_LEFT)
	{
		if (Cursor->getMode() == LABEL_HOVER && Cursor->getLeft() != NULL)
		{
			Cursor->setMode(LABEL_CLEAR);
			Cursor = Cursor->getLeft();
			Cursor->setMode(LABEL_HOVER);
		}
		else if (Cursor->getMode() == LABEL_SELECTED)
		{
			Cursor->LeftCommand();
			Cursor->UpdateLabel();
		}
	}
	else if(cmd == LCD_RIGHT)
	{
		if (Cursor->getMode() == LABEL_HOVER && Cursor->getRight() != NULL)
		{
			Cursor->setMode(LABEL_CLEAR);
			Cursor = Cursor->getRight();
			Cursor->setMode(LABEL_HOVER);
		}
		else if (Cursor->getMode() == LABEL_SELECTED)
		{
			Cursor->RightCommand();
			Cursor->UpdateLabel();
		}
	}
	else if(cmd == LCD_ENTER)
	{
		if(Cursor->getType() == LABEL_MENU_PTR && Cursor->getMode() == LABEL_HOVER)
		{
			LCDMenu* tmp = Cursor->getNextMenu();
			OrbitalLCD->ClearScreen();
			tmp->setReturnMenu(Menu);
			Menu = Cursor->getNextMenu();
			Menu->CallEnterPull();
			Menu->DrawMe();
			Cursor = Menu->getCursorHome();
			Cursor->setMode(LABEL_HOVER);
		}
		else if ((Cursor->getType() >= 3) && Cursor->getMode() == LABEL_HOVER)
		{
			Cursor->setMode(LABEL_SELECTED);
			Cursor->setTempVal(Cursor->getBackVal());
		}
		else if ((Cursor->getType() >= 3) && Cursor->getMode() == LABEL_SELECTED)
		{
			Menu->CallEnterCommit();
			Cursor->setMode(LABEL_HOVER);
			Cursor->setBackVal(Cursor->getTempVal());
		}
	}
	else if (cmd == LCD_HOME)
	{
		OrbitalLCD->ClearScreen();
		Menu = MenuHome;
		Menu->DrawMe();
		Cursor = Menu->getCursorHome();
		Cursor->setMode(LABEL_HOVER);
	}
	else if (cmd == LCD_BACK)
	{
		OrbitalLCD->ClearScreen();
		Menu = Menu->getReturnMenu();
		if (Menu == NULL)
			Menu = MenuHome;
		Menu->DrawMe();
		Cursor = Menu->getCursorHome();
		Cursor->setMode(LABEL_HOVER);
	}
}

LCDMenu* ArchInterfaceManager::DefineMenu_PitchBendingMode() {return NULL;}

LCDMenu* ArchInterfaceManager::DefineMenu_OperationMode()
{
	//Define Menu Variables and Labels
	OpMode_OperationMode.Initialize(MENU_NONE, RegionManager);
	OpMode_Title.Initialize(OrbitalLCD, 1, 10, 0, LABEL_PLAIN_TEXT, "OPERATION MODES:");
	OpMode_Chromatic.Initialize(OrbitalLCD, 2, 10, 14, LABEL_MENU_PTR, "1) Chromatic");
	OpMode_Custom.Initialize(OrbitalLCD, 3, 10, 28, LABEL_MENU_PTR, "2) Custom Mapping");
	OpMode_ScaleMode.Initialize(OrbitalLCD, 4, 10, 42, LABEL_MENU_PTR, "3) Scale Mode");
	
	//Form the Draw Linked List for Menu
	OpMode_OperationMode.setDrawList(&OpMode_Title);
	OpMode_Title.setNext(&OpMode_Chromatic);
	OpMode_Chromatic.setNext(&OpMode_Custom);
	OpMode_Custom.setNext(&OpMode_ScaleMode);
	OpMode_ScaleMode.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	OpMode_OperationMode.setCursorHome(&OpMode_Chromatic);
	OpMode_Chromatic.setQuadPtr(&OpMode_ScaleMode, &OpMode_Custom, NULL, NULL);
	OpMode_Custom.setQuadPtr(&OpMode_Chromatic, &OpMode_ScaleMode, NULL, NULL);
	OpMode_ScaleMode.setQuadPtr(&OpMode_Custom, &OpMode_Chromatic, NULL, NULL);
	
	//Set up the MenuPtrs
	OpMode_Chromatic.setNextMenu(DefineMenu_ChromaticMode());
	OpMode_Custom.setNextMenu(DefineMenu_CustomMode());
	OpMode_ScaleMode.setNextMenu(DefineMenu_ScaleMode());
	
	return &OpMode_OperationMode;
}

LCDMenu* ArchInterfaceManager::DefineMenu_ChromaticMode()
{
	//Define Menu Variables and Labels
	ChromMode_ChromaticMode.Initialize(MENU_CHROMATIC, RegionManager);
	ChromMode_Title.Initialize(OrbitalLCD, 1, 10, 0, LABEL_PLAIN_TEXT, "CHROMATIC MODE:");
	ChromMode_NumRegionsTag.Initialize(OrbitalLCD, 2, 10, 14, LABEL_PLAIN_TEXT, "# of Regions: ");
	ChromMode_NumRegionsVal.Initialize(OrbitalLCD, 3, 110, 14, LABEL_VALUE_NUMBER, 30, 1, 5, 0, 99);
	ChromMode_StartNoteTag.Initialize(OrbitalLCD, 4, 10, 28, LABEL_PLAIN_TEXT, "Start Note: ");
	ChromMode_StartNoteVal.Initialize(OrbitalLCD, 5, 110, 28, LABEL_VALUE_NOTE, 0, 1, 12, 0, 127);
	
	//Form the Draw Linked List for Menu
	ChromMode_ChromaticMode.setDrawList(&ChromMode_Title);
	ChromMode_Title.setNext(&ChromMode_NumRegionsTag);
	ChromMode_NumRegionsTag.setNext(&ChromMode_NumRegionsVal);
	ChromMode_NumRegionsVal.setNext(&ChromMode_StartNoteTag);
	ChromMode_StartNoteTag.setNext(&ChromMode_StartNoteVal);
	ChromMode_StartNoteVal.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	ChromMode_ChromaticMode.setCursorHome(&ChromMode_NumRegionsVal);
	ChromMode_NumRegionsVal.setQuadPtr(&ChromMode_StartNoteVal, &ChromMode_StartNoteVal, NULL, NULL);
	ChromMode_StartNoteVal.setQuadPtr(&ChromMode_NumRegionsVal, &ChromMode_NumRegionsVal, NULL, NULL);
	
	//Set up the MenuPtrs
	ChromMode_NumRegionsVal.setNextMenu(NULL);
	ChromMode_StartNoteVal.setNextMenu(NULL);
	
	return &ChromMode_ChromaticMode;
}

LCDMenu* ArchInterfaceManager::DefineMenu_CustomMode()
{
	//Define Menu Variables and Labels
	CustMode_CustomMode.Initialize(MENU_CUSTOM, RegionManager);
	CustMode_Title.Initialize(OrbitalLCD, 1, 10, 0, LABEL_PLAIN_TEXT, "CUSTOM MODE:");
	CustMode_NumRegionsTag.Initialize(OrbitalLCD, 2, 10, 14, LABEL_PLAIN_TEXT, "# of Regions: ");
	CustMode_NumRegionsVal.Initialize(OrbitalLCD, 3, 110, 14, LABEL_VALUE_NUMBER, 24, 1, 5, 0, 99);
	CustMode_EditRegionTag.Initialize(OrbitalLCD, 4, 10, 28, LABEL_PLAIN_TEXT, "Edit Region: ");
	CustMode_EditRegionVal.Initialize(OrbitalLCD, 5, 110, 28, LABEL_VALUE_NUMBER, 0, 1, 5, 0, 99);
	CustMode_EditRegionGo.Initialize(OrbitalLCD, 6, 130, 28, LABEL_MENU_PTR, "Enter");
	
	//Form the Draw Linked List for Menu
	CustMode_CustomMode.setDrawList(&CustMode_Title);
	CustMode_Title.setNext(&CustMode_NumRegionsTag);
	CustMode_NumRegionsTag.setNext(&CustMode_NumRegionsVal);
	CustMode_NumRegionsVal.setNext(&CustMode_EditRegionTag);
	CustMode_EditRegionTag.setNext(&CustMode_EditRegionVal);
	CustMode_EditRegionVal.setNext(&CustMode_EditRegionGo);
	CustMode_EditRegionGo.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	CustMode_CustomMode.setCursorHome(&CustMode_NumRegionsVal);
	CustMode_NumRegionsVal.setQuadPtr(&CustMode_EditRegionVal, &CustMode_EditRegionVal, NULL, NULL);
	CustMode_EditRegionVal.setQuadPtr(&CustMode_NumRegionsVal, &CustMode_NumRegionsVal, NULL, &CustMode_EditRegionGo);
	CustMode_EditRegionGo.setQuadPtr(NULL, NULL, &CustMode_EditRegionVal, NULL);
	
	//Set Up the MenuPtrs
	CustMode_NumRegionsVal.setNextMenu(NULL);
	CustMode_EditRegionVal.setNextMenu(NULL);
	CustMode_EditRegionGo.setNextMenu(DefineMenu_CustomRegionMode());
	
	return &CustMode_CustomMode;
}

LCDMenu* ArchInterfaceManager::DefineMenu_CustomRegionMode()
{
	//Define Menu Variables and Labels
	CustReg_CustomRegionMode.Initialize(MENU_CUSTOM_REGION, RegionManager);
	CustReg_EditRegionTag.Initialize(OrbitalLCD, 1, 10, 0, LABEL_PLAIN_TEXT, "Edit Region: ");
	CustReg_EditRegionVal.Initialize(OrbitalLCD, 2, 110, 0, LABEL_VALUE_NUMBER, 0, 1, 5, 0, 99);
	CustReg_StartDegTag.Initialize(OrbitalLCD, 3, 10, 12, LABEL_PLAIN_TEXT, "Start Degree: ");
	CustReg_StartDegVal.Initialize(OrbitalLCD, 4, 110, 12, LABEL_VALUE_NUMBER, 0, 1, 10, REJECTION_ANGLE_MIN_DEGREES, REJECTION_ANGLE_MAX_DEGREES);
	CustReg_EndDegTag.Initialize(OrbitalLCD, 5, 10, 24, LABEL_PLAIN_TEXT, "End Degree: ");
	CustReg_EndDegVal.Initialize(OrbitalLCD, 6, 110, 24, LABEL_VALUE_NUMBER, 0, 1, 10, REJECTION_ANGLE_MIN_DEGREES, REJECTION_ANGLE_MAX_DEGREES);
	CustReg_NoteTag.Initialize(OrbitalLCD, 7, 10, 36, LABEL_PLAIN_TEXT, "Note Value: ");
	CustReg_NoteVal.Initialize(OrbitalLCD, 8, 110, 36, LABEL_VALUE_NOTE, 24, 1, 12, 0, 127);
	//CustReg_ColorTag.Initialize(OrbitalLCD, 9, 10, 48, LABEL_PLAIN_TEXT, "Color: ");
	//CustReg_ColorVal.Initialize(OrbitalLCD, 10, 110, 48, LABEL_VALUE_COLOR, 0, 1, 1, 0, 20);
	
	//Form the Draw Linked List for Menu
	CustReg_CustomRegionMode.setDrawList(&CustReg_EditRegionTag);
	CustReg_EditRegionTag.setNext(&CustReg_EditRegionVal);
	CustReg_EditRegionVal.setNext(&CustReg_StartDegTag);
	CustReg_StartDegTag.setNext(&CustReg_StartDegVal);
	CustReg_StartDegVal.setNext(&CustReg_EndDegTag);
	CustReg_EndDegTag.setNext(&CustReg_EndDegVal);
	CustReg_EndDegVal.setNext(&CustReg_NoteTag);
	CustReg_NoteTag.setNext(&CustReg_NoteVal);
	CustReg_NoteVal.setNext(NULL);
	//CustReg_ColorTag.setNext(&CustReg_ColorVal);
	//CustReg_ColorVal.setNext(NULL);	
	
	//Form the Cursor QuadPtr Linked List
	CustReg_CustomRegionMode.setCursorHome(&CustReg_StartDegVal);
	CustReg_StartDegVal.setQuadPtr(&CustReg_NoteVal, &CustReg_EndDegVal, NULL, NULL);
	CustReg_EndDegVal.setQuadPtr(&CustReg_StartDegVal, &CustReg_NoteVal, NULL, NULL);
	CustReg_NoteVal.setQuadPtr(&CustReg_EndDegVal, &CustReg_StartDegVal, NULL, NULL);
	//CustReg_ColorVal.setQuadPtr(&CustReg_NoteVal, &CustReg_StartDegVal, NULL, NULL);
	
	//Set Up Next Menu Ptrs
	CustReg_EditRegionVal.setNextMenu(NULL);
	CustReg_StartDegVal.setNextMenu(NULL);
	CustReg_EndDegVal.setNextMenu(NULL);
	CustReg_NoteVal.setNextMenu(NULL);
	//CustReg_ColorVal.setNextMenu(NULL);
	
	return &CustReg_CustomRegionMode;
}

LCDMenu* ArchInterfaceManager::DefineMenu_ScaleMode()
{
	//Define Menu Variables and Labels
	ScaleMode_ScaleMode.Initialize(MENU_SCALE, RegionManager);
	ScaleMode_Title.Initialize(OrbitalLCD, 1, 10, 0, LABEL_PLAIN_TEXT, "SCALE MODE:");
	ScaleMode_NumRegionsTag.Initialize(OrbitalLCD, 2, 10, 12, LABEL_PLAIN_TEXT, "# of Regions: ");
	ScaleMode_NumRegionsVal.Initialize(OrbitalLCD, 3, 110, 12, LABEL_VALUE_NUMBER, 30, 1, 5, 0, 99);
	ScaleMode_StartNoteTag.Initialize(OrbitalLCD, 4, 10, 24, LABEL_PLAIN_TEXT, "Start Note: ");
	ScaleMode_StartNoteVal.Initialize(OrbitalLCD, 5, 110, 24, LABEL_VALUE_NOTE, 0, 1, 12, 0, 127);
	ScaleMode_ScaleTag.Initialize(OrbitalLCD, 6, 10, 36, LABEL_PLAIN_TEXT, "Scale: ");
	ScaleMode_ScaleVal.Initialize(OrbitalLCD, 7, 110, 36, LABEL_VALUE_SCALE, SCALE_MAJOR, 1, 1, 1, 2);
	
	
	//Form the Draw Linked List for Menu
	ScaleMode_ScaleMode.setDrawList(&ScaleMode_Title);
	ScaleMode_Title.setNext(&ScaleMode_NumRegionsTag);
	ScaleMode_NumRegionsTag.setNext(&ScaleMode_NumRegionsVal);
	ScaleMode_NumRegionsVal.setNext(&ScaleMode_StartNoteTag);
	ScaleMode_StartNoteTag.setNext(&ScaleMode_StartNoteVal);
	ScaleMode_StartNoteVal.setNext(&ScaleMode_ScaleTag);
	ScaleMode_ScaleTag.setNext(&ScaleMode_ScaleVal);
	ScaleMode_ScaleVal.setNext(NULL);
	
	//Form the Cursor QuadPtr Linked List
	ScaleMode_ScaleMode.setCursorHome(&ScaleMode_NumRegionsVal);
	ScaleMode_NumRegionsVal.setQuadPtr(&ScaleMode_ScaleVal, &ScaleMode_StartNoteVal, NULL, NULL);
	ScaleMode_StartNoteVal.setQuadPtr(&ScaleMode_NumRegionsVal, &ScaleMode_ScaleVal, NULL, NULL);
	ScaleMode_ScaleVal.setQuadPtr(&ScaleMode_StartNoteVal, &ScaleMode_NumRegionsVal, NULL, NULL);
	
	//Set up the MenuPtrs
	ScaleMode_NumRegionsVal.setNextMenu(NULL);
	ScaleMode_StartNoteVal.setNextMenu(NULL);
	ScaleMode_ScaleVal.setNextMenu(NULL);
	
	return &ScaleMode_ScaleMode;
	
}