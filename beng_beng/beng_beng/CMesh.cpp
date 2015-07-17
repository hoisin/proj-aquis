#include "CMesh.h"
#include "CSubMesh.h"



CMesh::CMesh(void)
{
}


CMesh::~CMesh(void)
{
	CleanUp();
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


unsigned int CMesh::GetSubMeshCount(void)
{
	return (unsigned int)m_vpSubMeshes.size();
}


void CMesh::SetPos(const glm::vec3& newPos)
{
	m_pos = newPos;
}


glm::vec3 CMesh::GetPos() const
{
	return m_pos;
}


void CMesh::CleanUp(void)
{
	for(unsigned int count = 0; count < (unsigned int)m_vpSubMeshes.size(); count++) {

		if(m_vpSubMeshes[count])
			delete m_vpSubMeshes[count];

		m_vpSubMeshes[count] = NULL;
	}

	m_vpSubMeshes.empty();
}

