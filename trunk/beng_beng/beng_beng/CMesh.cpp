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


CSubMesh* CMesh::GetSubMesh(unsigned int index)
{
	if(index < m_vpSubMeshes.size())
		return m_vpSubMeshes[index];

	return NULL;
}


void CMesh::SetPos(const glm::vec3& newPos)
{
	pos = newPos;
}


glm::vec3 CMesh::GetPos() const
{
	return pos;
}

