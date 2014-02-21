#include "CResourceMeshData.h"
#include "GfxDefs.h"


CResourceMeshData::CResourceMeshData(MeshData *pInData) : m_pMeshData(pInData)
{
}


CResourceMeshData::~CResourceMeshData(void)
{
	VCleanUp();
}


EResourceType CResourceMeshData::VGetType(void)
{
	return eResourceMeshData;
}


void CResourceMeshData::VCleanUp(void)
{
	if(m_pMeshData)
	{
		delete m_pMeshData;
		m_pMeshData = NULL;
	}
}


void* CResourceMeshData::VGetData(void)
{
	if(m_pMeshData)
	{
		return static_cast<void*>(m_pMeshData);
	}

	return NULL;
}
