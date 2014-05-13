#include "CResourceModelMesh.h"
#include "CModelMesh.h"


CResourceModelMesh::CResourceModelMesh(CModelMesh* pData) : m_pModelMesh(pData)
{
}


CResourceModelMesh::~CResourceModelMesh()
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
void CResourceModelMesh::VCleanUp()
{
	if(m_pModelMesh) {
		delete m_pModelMesh;
		m_pModelMesh = NULL;
	}
}