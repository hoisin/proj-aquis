//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Main interfacing class for accessing/creating resources
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCEMANAGER_H__
#define __CRESOURCEMANAGER_H__

#include <map>
#include <string>
#include "IResource.h"

class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

private:
	std::map<std::string, IResource *> m_resourceMap;
};

#endif