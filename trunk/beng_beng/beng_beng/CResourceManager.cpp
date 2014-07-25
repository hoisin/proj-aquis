#include "CResourceManager.h"
#include "CResourceMeshData.h"
#include "CResourceVertexBuffer.h"
#include "CResourceIndexBuffer.h"
#include "CResourceShader.h"
#include "CResourceTexture2D.h"
#include "CResourceSubMesh.h"
#include "CMeshDataGenerator.h"
#include "CTextureLoader.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CTexture2D.h"
#include "CSubMesh.h"


CResourceManager::CResourceManager() : m_pMeshGenerator(NULL), m_pTextureLoader(NULL)
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
	m_pTextureLoader = new CTextureLoader;

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
//	CreateQuad(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of quad
//	type			-	type of vertices to use
//	colour			-	colour of quad if vertex type supports colour
//
//	Description:
//	Call Mesh Generator to create 2D quad, then stores as a resource
//
//----------------------------------------------------------------------------------------------------
MeshData* CResourceManager::CreateQuad(const std::string &geometryID, float size, EVertexType type,
		const glm::vec4 &colour)
{
	// Generator mesh data
	MeshData *pNewMeshData = m_pMeshGenerator->CreateQuad(geometryID, size, type, colour);

	// Attach to resource object
	CResourceMeshData *pNewResource = new CResourceMeshData(pNewMeshData);

	// Add to map.
	m_resourceMap.insert(std::pair<std::string, IResource*>(geometryID, pNewResource));

	return pNewMeshData;
}


//----------------------------------------------------------------------------------------------------
//
//	CreatePlane(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of quad
//	type			-	type of vertices to use
//	numFaces		-   defines the polycount
//	colour			-	colour of quad if vertex type supports colour
//
//	Description:
//	Call Mesh Generator to create 2D quad, then stores as a resource
//
//----------------------------------------------------------------------------------------------------
MeshData* CResourceManager::CreatePlane(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces,
		const glm::vec4 &colour)
{
	// Generator mesh data
	MeshData *pNewMeshData = m_pMeshGenerator->CreatePlane(geometryID, size, type, numFaces, colour);

	// Attach to resource object
	CResourceMeshData *pNewResource = new CResourceMeshData(pNewMeshData);

	// Add to map.
	m_resourceMap.insert(std::pair<std::string, IResource*>(geometryID, pNewResource));

	return pNewMeshData;
}


//----------------------------------------------------------------------------------------------------
//
//	CreateCube(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of cube
//	numFaces		-	Number of cells
//	type			-	type of vertices to use
//	colour			-	colour of quad if vertex type supports colour
//
//	Description:
//	Call Mesh Generator to create cube, then stores as a resource
//
//----------------------------------------------------------------------------------------------------
MeshData* CResourceManager::CreateCube(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces,
		const glm::vec4 &colour)
{
	MeshData *pNewMeshData = m_pMeshGenerator->CreateCube(geometryID,
		size, type, numFaces, colour);

	CResourceMeshData *pNewResource = new CResourceMeshData(pNewMeshData);

	m_resourceMap.insert(std::pair<std::string, IResource*>(geometryID, pNewResource));

	return pNewMeshData;
}


//----------------------------------------------------------------------------------------------------
//
//	CreateSphere(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of cube
//	subDivs			-	number of subdivisions (If 0 circle has 3 subdivions)
//	type			-	type of vertices to use
//	colour			-	colour of quad if vertex type supports colour
//
//	Description:
//	Call Mesh Generator to create sphere, then stores as a resource
//
//----------------------------------------------------------------------------------------------------
MeshData* CResourceManager::CreateSphere(const std::string &geometryID, float size, EVertexType type, unsigned int subDivs,
		const glm::vec4 &colour)
{
	MeshData *pNewMeshData = m_pMeshGenerator->CreateSphere(geometryID,
		size, type, subDivs, colour);

	CResourceMeshData *pNewResource = new CResourceMeshData(pNewMeshData);

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
//	CreateIndexBuffer(..)
//
//	Params:
//	vertexID		-	ID of resource to store in map
//	pData			-	loaded mesh data in memory
//
//	Description:
//	Loads/creates index buffer resource
//
//----------------------------------------------------------------------------------------------------
CIndexBuffer* CResourceManager::CreateIndexBuffer(const std::string &indexID, MeshData *pData)
{
	CResourceIndexBuffer *pNewResource = new CResourceIndexBuffer(pData);

	m_resourceMap.insert(std::pair<std::string, IResource*>(indexID, pNewResource));

	return pNewResource->m_pIdxBuffer;
}


//----------------------------------------------------------------------------------------------------
//
//	CreateTexture2D(..)
//
//	Params:
//	textureID		-	ID of resource to store in map
//	fileName		-	location of file
//
//	Description:
//	Loads/creates texture resource
//
//----------------------------------------------------------------------------------------------------
CTexture2D* CResourceManager::CreateTexture2D(const std::string &textureID, const std::string &fileName)
{
	unsigned char* pData = NULL;
	unsigned int width = 0;
	unsigned int height = 0;

	CTexture2D *pNewTexture = new CTexture2D;

	// Assume we only load BMPs for now
	if(m_pTextureLoader->LoadBMP(fileName, width, height, &pData)) {
		pNewTexture->LoadTexture(width, height, GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, pData);

		CResourceTexture2D *pNewResource = new CResourceTexture2D(pNewTexture);

		m_resourceMap.insert(std::pair<std::string, IResource*>(textureID, pNewResource));
	} else {
		delete pNewTexture;
		pNewTexture = NULL;
	}

	// Clean up loaded data
	if(pData) {
		delete [] pData;
		pData = NULL;
	}

	return pNewTexture;
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
CShader* CResourceManager::CreateShader(const std::string &shaderID, const std::string &vertexShaderFile,
		const std::string &fragShaderFile)
{
	CShader *pNewShader = new CShader;

	GLuint outID;
	pNewShader->LoadShader(vertexShaderFile, fragShaderFile, outID);

	CResourceShader *pNewResource = new CResourceShader(pNewShader);

	m_resourceMap.insert(std::pair<std::string, IResource*>(shaderID, pNewResource));

	return pNewShader;
}


//----------------------------------------------------------------------------------------------------
//
//	CreateSubMesh(..)
//
//	Params:
//	modelMeshID	-	ID of the resource to store in the map
//	meshID		-	Reference ID to stored Mesh Data
//	vertexID	-	Reference ID to stored vertex buffer
//	indexID		-	Reference ID to stored index buffer
//	shaderID	-	Reference ID to stored shader
//	textureID	-	Reference ID to stored texture
//
//	Description:
//	Creates a model mesh
//
//----------------------------------------------------------------------------------------------------
CSubMesh* CResourceManager::CreateSubMesh(const std::string &subMeshID, const std::string &meshDataID, const std::string &vertexID, 
	const std::string &indexID, const std::string &shaderID, const std::string &textureID)
{
	CSubMesh *pNewModelMesh = new CSubMesh(meshDataID, vertexID, indexID, shaderID, textureID);

	CResourceSubMesh *pNewResource = new CResourceSubMesh(pNewModelMesh);

	m_resourceMap.insert(std::pair<std::string, IResource*>(subMeshID, pNewResource));

	return pNewModelMesh;
}


IResource* CResourceManager::GetResource(const std::string &resourceID)
{
	std::map<std::string, IResource*>::iterator it = m_resourceMap.find(resourceID);

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
	if(m_pMeshGenerator) {
		delete m_pMeshGenerator;
		m_pMeshGenerator = NULL;
	}

	// Loop through all resources and remove
	std::map<std::string, IResource *>::iterator it = m_resourceMap.begin();

	for(; it != m_resourceMap.end(); it++) {
		it->second->VCleanUp();	// Won't need this if resources call the shutdown in the d'tor.
		delete it->second;
		it->second = NULL;
	}

}