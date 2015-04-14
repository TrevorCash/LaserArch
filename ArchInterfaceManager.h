/* 
* ArchInterfaceManager.h
*
* Created: 2/20/2015 10:37:26 AM
* Author: 7002815
*/

class ArchLCD;
class LCDMenu;
class LCDLabels;
class ArchRegionManager;

#ifndef __ARCHINTERFACEMANAGER_H__
#define __ARCHINTERFACEMANAGER_H__

#include <i2c_t3/i2c_t3.h>
#include "PrimaryDefines.h"
#include "MIDINoteDefines.h"

#ifndef __ARCHREGIONMANAGER_H__
#include "ArchRegionManager.h"
#define __ARCHREGIONMANAGER_H__
#endif

#ifndef _LCDLABELS_h
#include "LCDLabels.h"
#define _LCDLABELS_h
#endif

#ifndef _LCDMENU_h
#include "LCDMenu.h"
#define _LCDMENU_h
#endif

#ifndef __ARCHLCD_H__
#include "ArchLCD.h"
#define __ARCHLCD_H__
#endif

#ifndef _LCDMENUSETUP_h
#include "LCDMenuSetup.h"
#define _LCDMENUSETUP_h
#endif



//	
class ArchInterfaceManager
{
//variables
public:
	LCDMenu* MenuHome;
	LCDMenu* Menu;
	LCDLabels* Cursor;
	ArchLCD* OrbitalLCD;
protected:
private:

//functions
public:
	ArchInterfaceManager();
	~ArchInterfaceManager();
	void Initialize();
	void Update(ArchRegionManager* RegionManager);
protected:
private:
	ArchInterfaceManager( const ArchInterfaceManager &c );
	ArchInterfaceManager& operator=( const ArchInterfaceManager &c );

}; //ArchInterfaceManager

#endif //__ARCHINTERFACEMANAGER_H__
