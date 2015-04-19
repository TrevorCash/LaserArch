/* 
* ArchInterfaceManager.h
*
* Created: 2/20/2015 10:37:26 AM
* Author: 7002815
*/


#ifndef __ARCHINTERFACEMANAGER_H__
#define __ARCHINTERFACEMANAGER_H__

#include <i2c_t3/i2c_t3.h>
#include "PrimaryDefines.h"
#include "MIDINoteDefines.h"
#include "ArchRegionManager.h"



class ArchLCD;

#include "LCDLabels.h"
#include "LCDMenu.h"


class ArchInterfaceManager
{
//variables
public:

	LCDMenu* MenuHome;
	LCDMenu* Menu;
	LCDLabels* Cursor;
	ArchLCD* OrbitalLCD;

	//Operation Mode Variables
	LCDMenu OpMode_OperationMode;
	LCDLabels OpMode_Title;
	LCDLabels OpMode_Chromatic;
	LCDLabels OpMode_Custom;
	LCDLabels OpMode_ScaleMode;
	
	//Chromatic Mode Variables
	LCDMenu ChromMode_ChromaticMode;
	LCDLabels ChromMode_Title;
	LCDLabels ChromMode_NumRegionsTag;
	LCDLabels ChromMode_NumRegionsVal;
	LCDLabels ChromMode_StartNoteTag;
	LCDLabels ChromMode_StartNoteVal;
	
	//Custom Mode Variables
	LCDMenu CustMode_CustomMode;
	LCDLabels CustMode_Title;
	LCDLabels CustMode_NumRegionsTag;
	LCDLabels CustMode_NumRegionsVal;
	LCDLabels CustMode_EditRegionTag;
	LCDLabels CustMode_EditRegionVal;
	LCDLabels CustMode_EditRegionGo;
	
	//Custom Region Mode Variables
	LCDMenu CustReg_CustomRegionMode;
	LCDLabels CustReg_EditRegionTag;
	LCDLabels CustReg_EditRegionVal;
	LCDLabels CustReg_StartDegTag;
	LCDLabels CustReg_StartDegVal;
	LCDLabels CustReg_EndDegTag;
	LCDLabels CustReg_EndDegVal;
	LCDLabels CustReg_NoteTag;
	LCDLabels CustReg_NoteVal;
	LCDLabels CustReg_ColorTag;
	LCDLabels CustReg_ColorVal;
	
	//Scale Mode Variables
	LCDMenu ScaleMode_ScaleMode;
	LCDLabels ScaleMode_Title;
	LCDLabels ScaleMode_NumRegionsTag;
	LCDLabels ScaleMode_NumRegionsVal;
	LCDLabels ScaleMode_StartNoteTag;
	LCDLabels ScaleMode_StartNoteVal;
	LCDLabels ScaleMode_ScaleTag;
	LCDLabels ScaleMode_ScaleVal;	

protected:
private:




//functions
public:
	ArchInterfaceManager(ArchRegionManager* NewRegionManager);
	~ArchInterfaceManager();
	void Initialize();
	void Update();

protected:
private:

	ArchRegionManager* RegionManager;

	LCDMenu* DefineMenu_OperationMode();
	LCDMenu* DefineMenu_ChromaticMode();
	LCDMenu* DefineMenu_CustomMode();
	LCDMenu* DefineMenu_CustomRegionMode();
	LCDMenu* DefineMenu_PitchBendingMode();
	LCDMenu* DefineMenu_ScaleMode();

public:


	
	
}; //ArchInterfaceManager

#endif //__ARCHINTERFACEMANAGER_H__
