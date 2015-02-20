/* 
* ArchNoteRegionManager.h
*
* Created: 2/20/2015 10:31:22 AM
* Author: 7002815
*/


#ifndef __ARCHNOTEREGIONMANAGER_H__
#define __ARCHNOTEREGIONMANAGER_H__

//The Arch Note Region Manager Manages and Contains All ArchNoteRegion objects.
//External use of the manager includes
//	Setting Number of Note Regions
//	Access Functions for resizing/customizing regions
//	Access to current note region via current timer tick
//	Access to the next laser switch event for use in interupts.
//Internal functions of the manager include:
//	Maintanace of internal Linked list of regions
//	Fast lookup capability
//	

class ArchNoteRegionManager
{
//variables
public:
protected:
private:

//functions
public:
	ArchNoteRegionManager();
	~ArchNoteRegionManager();
protected:

}; //ArchNoteRegionManager

#endif //__ARCHNOTEREGIONMANAGER_H__
