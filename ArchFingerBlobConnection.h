/*
 * ArchFingerBlobConnection.h
 *
 * Created: 3/25/2015 1:01:27 PM
 *  Author: 7002815
 */ 


#ifndef ARCHFINGERBLOBCONNECTION_H_
#define ARCHFINGERBLOBCONNECTION_H_

#include "ArchFinger.h"
#include "ArchRawBlob.h"

struct ArchFingerBlobConnection
{
	uint32_t distance;
	ArchRawBlob* pBlob;
	ArchFinger*  pFinger;
};


#endif /* ARCHFINGERBLOBCONNECTION_H_ */