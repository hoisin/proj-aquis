//--------------------------------------------------------------------------
//
//	29/02/2015
//
//	Mesh Manager
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#include "CMeshManager.h"
#include "CMesh.h"
#include "CSubMesh.h"

#include <string>


CMeshManager::CMeshManager(void)
{
}


CMeshManager::~CMeshManager(void)
{
	CleanUp();
}


CMesh* CMeshManager::CreateMesh(const glm::vec3& pos, const std::string& meshID)
{
	CMesh* pNewMesh = new CMesh;

	pNewMesh->SetPos(pos);

	m_mpMeshes.insert(std::pair<std::string, CMesh*>(meshID, pNewMesh));

	return pNewMesh;
}


CMesh* CMeshManager::GetMesh(const std::string& meshID)
{
	std::map<std::string, CMesh*>::iterator it = m_mpMeshes.find(meshID);

	if(it == m_mpMeshes.end())
		return NULL;

	return it->second;
}


void CMeshManager::RemoveMesh(const std::string& meshID)
{
	std::map<std::string, CMesh*>::iterator it = m_mpMeshes.find(meshID);

	if(it != m_mpMeshes.end()) {
		if(it->second) {
			delete it->second;
			it->second = NULL;
		}

		m_mpMeshes.erase(it);
	}
}


void CMeshManager::CleanUp()
{
	std::map<std::string, CMesh*>::iterator it;

	for(it = m_mpMeshes.begin(); it != m_mpMeshes.end(); it++)
	{
		if(it->second) {
			delete it->second;
			it->second = NULL;
		}
	}

	m_mpMeshes.empty();
}


