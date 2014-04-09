#include "CResourceManager.h"
#include "CResourceMeshData.h"
#include "CResourceVertexBuffer.h"
#include "CResourceShader.h"
#include "CShader.h"
#include "CMeshDataGenerator.h"
#include "CVertexBuffer.h"


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
MeshData* CResourceManager::CreateTriangle(const std::string &geometryID, float size, EVertexType type,
		const glm::vec4 &colour)
{
	// Generator mesh data
	MeshData *pNewMeshData = m_pMeshGenerator->CreateTriangle(geometryID, size, type, colour);

	// Attach to resource object
	CResourceMeshData *pNewResource = new CResourceMeshData(pNewMeshData);

	// Add to map.
	m_resourceMap.insert(std::pair<std::string, IResource*>(geometryID, pNewResource));

	return pNewMeshData;
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
CVertexBuffer* CResourceManager::CreateVertexBuffer(const std::string &vertexID, MeshData *pData)
{
	CResourceVertexBuffer *pNewResource = new CResourceVertexBuffer(pData);

	m_resourceMap.insert(std::pair<std::string, IResource*>(vertexID, pNewResource));

	return pNewResource->m_pVertBuffer;
}


//----------------------------------------------------------------------------------------------------
//
//	CreateShader(..)
//
//	Params:
//	shaderID			-	ID of resource to store in map
//	vertexShaderFile	-	location of vertex shader
//	fragShaderFile		-	location of fragment shader
//	outHandle			-	output if required, pass as reference
//
//	Description:
//	Loads/creates a shader resource by taking vertex and fragment shader and compiling them
//
//----------------------------------------------------------------------------------------------------
unsigned int CResourceManager::CreateShader(const std::string &shaderID, const std::string &vertexShaderFile,
		const std::string &fragShaderFile)
{
	CShader *pNewShader = new CShader;

	GLuint outID;
	pNewShader->LoadShader(vertexShaderFile, fragShaderFile, outID);

	CResourceShader *pNewResource = new CResourceShader(pNewShader);

	m_resourceMap.insert(std::pair<std::string, IResource*>(shaderID, pNewResource));

	return pNewShader->GetShaderID();
}


IResource* CResourceManager::GetResource(const std::string &resourceID)
{
	std::map<std::string, IResource*>::iterator it = m_resourceMap.find("resourceID");

	if(it != m_resourceMap.end())
		return it->second;

	return NULL;
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