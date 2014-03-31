#include "CResourceManager.h"
#include "CResourceMeshData.h"
#include "CResourceVertexBuffer.h"
#include "CMeshDataGenerator.h"


CResourceManager::CResourceManager() : m_pMeshGenerator(NULL)
{
}


CResourceManager::~CResourceManager()
{
	ShutDown();
}


//----------------------------------------------------------------------------------------------------
//
//	Initialise(..)
//
//	Description:
//	Initialises the resource manager
//
//----------------------------------------------------------------------------------------------------
bool CResourceManager::Initialise()
{
	m_pMeshGenerator = new CMeshDataGenerator;

	return true;
}


//----------------------------------------------------------------------------------------------------
//
//	CreateTriangle(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of triangle
//	type			-	type of vertices to use
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Call Mesh Generator to create triangle, then stores as a resource
//
//----------------------------------------------------------------------------------------------------
bool CResourceManager::CreateTriangle(const std::string &geometryID, float size, EVertexType type,
		const glm::vec4 &colour)
{
	// Generator mesh data
	MeshData *pNewMeshData = m_pMeshGenerator->CreateTriangle(geometryID, size, type, colour);

	// Attach to resource object
	CResourceMeshData *pNewResource = new CResourceMeshData(pNewMeshData);

	// Add to map.
	m_resourceMap.insert(std::pair<std::string, IResource*>(geometryID, pNewResource));
}


//----------------------------------------------------------------------------------------------------
//
//	CreateVertexBuffer(..)
//
//	Params:
//	vertexID		-	ID of resource to store in map
//	pData			-	loaded mesh data in memory
//
//	Description:
//	Loads/creates vertex buffer resource
//
//----------------------------------------------------------------------------------------------------
bool CResourceManager::CreateVertexBuffer(const std::string &vertexID, MeshData *pData)
{
	CResourceVertexBuffer *pNewResource = new CResourceVertexBuffer(pData);

	m_resourceMap.insert(std::pair<std::string, IResource*>(vertexID, pNewResource));

	return true;
}


//----------------------------------------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Description:
//	Cleans up stuff before closing
//
//----------------------------------------------------------------------------------------------------
void CResourceManager::ShutDown()
{
	if(m_pMeshGenerator)
	{
		delete m_pMeshGenerator;
		m_pMeshGenerator = NULL;
	}

	// Loop through all resources and remove
	std::map<std::string, IResource *>::iterator it = m_resourceMap.begin();

	for(; it != m_resourceMap.end(); it++)
	{
		it->second->VCleanUp();	// Won't need this if resources call the shutdown in the d'tor.
		delete it->second;
		it->second = NULL;
	}

}