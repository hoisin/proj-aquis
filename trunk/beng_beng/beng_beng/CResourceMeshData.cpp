#include "CResourceMeshData.h"
#include "GfxDefs.h"

CResourceMeshData::CResourceMeshData(MeshData *pData) : m_pMeshData(pData)
{
}


CResourceMeshData::~CResourceMeshData()
{
	VCleanUp();
}


//------------------------------------------------------------------
//
//	VCleanUp(..)
//
//	Performs any clean up required
//
//------------------------------------------------------------------
void CResourceMeshData::VCleanUp()
{
	if(m_pMeshData) {
		delete m_pMeshData;
		m_pMeshData = NULL;
	}
}
