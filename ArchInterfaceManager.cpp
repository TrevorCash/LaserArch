/* 
* ArchInterfaceManager.cpp
*
* Created: 2/20/2015 10:37:26 AM
* Author: 7002815
*/


#include "ArchInterfaceManager.h"

// default constructor
ArchInterfaceManager::ArchInterfaceManager()
{

} //ArchInterfaceManager

// default destructor
ArchInterfaceManager::~ArchInterfaceManager()
{
} //~ArchInterfaceManager

void ArchInterfaceManager::Initialize()
{
	OrbitalLCD->Initialize();
	OrbitalLCD->ClearScreen();
	Serial.print("\nClear Screen: ");
	Serial.print(uint32_t(MenuHome));
	
	MenuHome = DefineMenu_OperationMode();
	Menu = MenuHome;
	Menu->DrawMe();
	Serial.println("Success");
	Cursor = Menu->getCursorHome();
	Cursor->setMode(LABEL_HOVER);
}

void ArchInterfaceManager::Update(ArchRegionManager* RegionManager)
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
			if (Menu->CallEnterPull != NULL)
				Menu->CallEnterPull(RegionManager, Menu);
			Menu->DrawMe();
			Cursor = Menu->getCursorHome();
			Cursor->setMode(LABEL_HOVER);
		}
		else if ((Cursor->getType() == LABEL_VALUE_NUMBER || Cursor->getType() == LABEL_VALUE_NOTE) 
			   && Cursor->getMode() == LABEL_HOVER)
		{
			Cursor->setMode(LABEL_SELECTED);
			Cursor->setTempVal(Cursor->getBackVal());
		}
		else if ((Cursor->getType() == LABEL_VALUE_NUMBER || Cursor->getType() == LABEL_VALUE_NOTE)
		&& Cursor->getMode() == LABEL_SELECTED)
		{
			if (Menu->CallEnterCommit != NULL)
				Menu->CallEnterCommit(RegionManager, Menu);
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
		Serial.println("Cleared");
		Menu = Menu->getReturnMenu();
		if (Menu == NULL)
			Menu = MenuHome;
		Serial.println((int)(Menu));
		Menu->DrawMe();
		Serial.println("Drawn");
		Cursor = Menu->getCursorHome();
		Cursor->setMode(LABEL_HOVER);
	}
}