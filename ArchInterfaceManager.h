/* 
* ArchInterfaceManager.h
*
* Created: 2/20/2015 10:37:26 AM
* Author: 7002815
*/


#ifndef __ARCHINTERFACEMANAGER_H__
#define __ARCHINTERFACEMANAGER_H__

//manages the user interface and lcd screen.
//provides access to the menu system.
//Perhaps internally.
//	GetCurrentMenu()
//	GetSubMenus()
//	NavigateToMenu()
//	NavigateBack()
//	SetLighting()...
//	
class ArchInterfaceManager
{
//variables
public:
protected:
private:

//functions
public:
	ArchInterfaceManager();
	~ArchInterfaceManager();
protected:
private:
	ArchInterfaceManager( const ArchInterfaceManager &c );
	ArchInterfaceManager& operator=( const ArchInterfaceManager &c );

}; //ArchInterfaceManager

#endif //__ARCHINTERFACEMANAGER_H__
