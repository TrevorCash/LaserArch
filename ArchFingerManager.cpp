/* 
* ArchFingerManager.cpp
*
* Created: 3/23/2015 5:34:21 PM
* Author: 7002815
*/


#include "ArchFingerManager.h"
#include "ArchRawBlob.h"

// default constructor
ArchFingerManager::ArchFingerManager(ArchBlobManager* blobManager)
{
	this->blobManager = blobManager;
	
	curFingerList = NULL;
} //ArchFingerManager

// default destructor
ArchFingerManager::~ArchFingerManager()
{
} //~ArchFingerManager


void ArchFingerManager::Update()
{
	
}