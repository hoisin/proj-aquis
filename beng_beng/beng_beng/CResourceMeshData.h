//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Resource class storing MeshData
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCEMESHDATA_H__
#define __CRESOURCEMESHDATA_H__

#include "IResource.h"

struct MeshData;

class CResourceMeshData : public IResource
{
public:
	CResourceMeshData(MeshData *pData);
	~CResourceMeshData();

	EResourceType VGetType() { return eResourceMeshData; }

	void VCleanUp();

public:
	MeshData *m_pMeshData;
};


#endif