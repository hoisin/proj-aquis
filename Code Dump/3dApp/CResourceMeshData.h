//-----------------------------------------------------------
//
//	Date: 21/02/2014
//	Author: Matthew Tsang
//
//	Resource class holding Mesh data
//
//-----------------------------------------------------------

#ifndef __CRESOURCEMESHDATA_H__
#define __CRESOURCEMESHDATA_H__

#include "IResource.h"

struct MeshData;

class CResourceMeshData : public IResource
{
public:
	MeshData* m_pMeshData;

public:
	CResourceMeshData(MeshData *pInData);
	~CResourceMeshData(void);

	EResourceType VGetType(void);

	void VCleanUp(void);

	void* VGetData(void);
};


#endif