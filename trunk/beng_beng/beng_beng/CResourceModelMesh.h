//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Resource class which combines a collection of resource to define a model
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCEMODELMESH_H__
#define __CRESOURCEMODELMESH_H__

#include "IResource.h"

class CModelMesh;

class CResourceModelMesh : public IResource
{
public:
	CResourceModelMesh(CModelMesh *pData);
	~CResourceModelMesh();

	EResourceType VGetType() { return eResourceModelMesh; }

	void VCleanUp();

public:
	CModelMesh *m_pModelMesh;
};


#endif