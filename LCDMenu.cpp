#include "LCDMenu.h"

LCDMenu::LCDMenu() {}
LCDMenu::~LCDMenu() {}


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