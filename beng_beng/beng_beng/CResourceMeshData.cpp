#include "CResourceMeshData.h"

CResourceMeshData::CResourceMeshData(MeshData *pData) : m_pMeshData(pData)
{
}


CResourceMeshData::~CResourceMeshData()
{
	VCleanUp();
}


EResourceType CResourceMeshData::VGetType()
{
	return eResourceMeshData;
}


void CResourceMeshData::VCleanUp()
{
	if(m_pMeshData)
	{
		delete m_pMeshData;
		m_pMeshData = NULL;
	}
}

