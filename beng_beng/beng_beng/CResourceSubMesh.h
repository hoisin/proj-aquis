//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Resource class which combines a collection of resource to define a model
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCESUBMESH_H__
#define __CRESOURCESUBMESH_H__

#include "IResource.h"

class CSubMesh;

class CResourceSubMesh : public IResource
{
public:
	CResourceSubMesh(CSubMesh *pData);
	~CResourceSubMesh();

	EResourceType VGetType() { return eResourceSubMesh; }

	void VCleanUp();

public:
	CSubMesh *m_pSubMesh;
};


#endif