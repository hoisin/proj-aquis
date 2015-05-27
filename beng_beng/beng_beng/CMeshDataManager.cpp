#include "CMeshDataManager.h"
#include "CMeshDataGenerator.h"
#include "GfxDefs.h"

#include <string>

CMeshDataManager::CMeshDataManager(void) : m_pMeshDataGenerator(NULL)
{
	m_pMeshDataGenerator = new CMeshDataGenerator;
}



CMeshDataManager::~CMeshDataManager(void)
{
	CleanUp();
}


bool CMeshDataManager::AddMeshData(MeshData* pNewMeshData, const std::string& meshDataID)
{
	std::map<std::string, MeshData*>::iterator it = m_mpMeshData.find(meshDataID);

	// Already an entry with same ID
	if(it != m_mpMeshData.end())
		return false;

	m_mpMeshData.insert(std::pair<std::string, MeshData*>(meshDataID, pNewMeshData));

	return true;
}


bool CMeshDataManager::CreatePlane(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions,
	const glm::vec4& colour)
{
	if (m_pMeshDataGenerator) {
		MeshData* pNewPlaneMesh = m_pMeshDataGenerator->CreatePlane(geometryID, size, type, subDivisions, colour);

		m_mpMeshData.insert(std::pair<std::string, MeshData*>(geometryID, pNewPlaneMesh));

		return true;
	}

	return false;
}


bool CMeshDataManager::CreateSphere(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions,
		const glm::vec4& colour)
{
	if(m_pMeshDataGenerator) {
		MeshData* pNewSphereMesh = m_pMeshDataGenerator->CreateSphere(geometryID, size,
			type, subDivisions, colour);

		m_mpMeshData.insert(std::pair<std::string, MeshData*>(geometryID, pNewSphereMesh));

		return true;
	}

	return false;
}


MeshData* CMeshDataManager::GetMeshData(const std::string& meshDataID)
{
	std::map<std::string, MeshData*>::iterator it = m_mpMeshData.find(meshDataID);

	// Already an entry with same ID
	if(it != m_mpMeshData.end())
		return it->second;

	return NULL;
}


bool CMeshDataManager::RemoveMeshData(const std::string& meshDataID)
{
	std::map<std::string, MeshData*>::iterator it = m_mpMeshData.find(meshDataID);

	if(it != m_mpMeshData.end()) {
		delete it->second;
		m_mpMeshData.erase(it);

		return true;
	}

	// else no such entry...
	return false;
}


std::map<std::string, MeshData*>* CMeshDataManager::GetMap(void)
{
	return &m_mpMeshData;
}


void CMeshDataManager::CleanUp(void)
{
	std::map<std::string, MeshData*>::iterator it;

	for(it = m_mpMeshData.begin(); it != m_mpMeshData.end(); it++) {
		if(it->second != NULL) {
			delete it->second;
			it->second = NULL;
		}
	}

	m_mpMeshData.empty();


	if(m_pMeshDataGenerator) {
		delete m_pMeshDataGenerator;
		m_pMeshDataGenerator = NULL;
	}
}


