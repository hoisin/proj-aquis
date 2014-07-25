#include "CResourceSubMesh.h"
#include "CSubMesh.h"


CResourceSubMesh::CResourceSubMesh(CSubMesh* pData) : m_pSubMesh(pData)
{
}


CResourceSubMesh::~CResourceSubMesh()
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
void CResourceSubMesh::VCleanUp()
{
	if(m_pSubMesh) {
		delete m_pSubMesh;
		m_pSubMesh = NULL;
	}
}