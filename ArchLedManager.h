/* 
* ArchLedManager.h
*
* Created: 3/31/2015 5:24:56 PM
* Author: 7002815
*/


#ifndef __ARCHLEDMANAGER_H__
#define __ARCHLEDMANAGER_H__

#include "ArchRegionManager.h"
#include "ArchFingerManager.h"

class ArchLedManager
{
//variables
public:
protected:
private:

//functions
public:
	ArchLedManager(ArchRegionManager* regionManager, ArchFingerManager* fingerManager);
	~ArchLedManager();
	
	void Update();
protected:
private:

}; //ArchLedManager

#endif //__ARCHLEDMANAGER_H__
