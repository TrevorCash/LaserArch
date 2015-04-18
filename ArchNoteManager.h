/* 
* ArchNoteManager.h
*
* Created: 4/2/2015 3:04:37 PM
* Author: 7002815
*/


#ifndef __ARCHNOTEMANAGER_H__
#define __ARCHNOTEMANAGER_H__


#include "ArchRegionManager.h"
#include "ArchFinger.h"

class ArchNoteManager
{


//functions
public:
	ArchNoteManager(ArchRegionManager* regionManager);
	~ArchNoteManager();
	
	//called from the finger manager when interesting events occur on a finger..
	void OnFingerMove(ArchFinger* finger);
	void OnFingerStart(ArchFinger* finger);
	void OnFingerStop(ArchFinger* finger);
	
	
protected:
private:
	
	ArchRegionManager* regionManager;

}; //ArchNoteManager

#endif //__ARCHNOTEMANAGER_H__
