#include "CMesh.h"
#include "CSubMesh.h"



CMesh::CMesh(void)
{
}


CMesh::~CMesh(void)
{
}


void CMesh::AddSubMesh(CSubMesh* pSubMesh)
{
	m_vpSubMeshes.push_back(pSubMesh);
}