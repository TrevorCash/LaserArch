/* 
* ArchFingerManager.h
*
* Created: 3/23/2015 5:34:21 PM
* Author: 7002815
*/


#ifndef __ARCHFINGERMANAGER_H__
#define __ARCHFINGERMANAGER_H__

#include "ArchBlobManager.h"
#include "ArchFinger.h"


class ArchFingerManager
{

//functions
public:
	ArchFingerManager(ArchBlobManager* blobManager);
	~ArchFingerManager();

	void Update();//called from main loop;
	
	ArchFinger* InactiveFingers;
	ArchFinger* ActiveFingers;
	ArchFinger* LastActiveFinger;

protected:
	ArchBlobManager* blobManager;
private:
	ArchFingerManager( const ArchFingerManager &c );
	ArchFingerManager& operator=( const ArchFingerManager &c );

}; //ArchFingerManager

#endif //__ARCHFINGERMANAGER_H__
