#include "CResourceManager.h"

CResourceManager::CResourceManager(CD3DBase *pD3DBase) : m_pD3DBase(pD3DBase),
	m_pMeshDataManager(NULL), m_pBufferManager(NULL), m_pTextureManager(NULL)
{
}


CResourceManager::~CResourceManager(void)
{
	ShutDown();
}


//----------------------------------------------------------------------
//
//	Description:
//	Creates whats needed for this manager
//
//----------------------------------------------------------------------
bool CResourceManager::Initialise(void)
{
	m_pMeshDataManager = new CMeshDataManager;
	m_pBufferManager = new CBufferManager;
	m_pTextureManager = new CTextureManager;

	return true;
}


//----------------------------------------------------------------------
//
//	Params:
//	cubeID			-	string ID used to store creates MeshData in a map
//	size			-	size of the cube
//	tessellation	-	increases amount of vertices generated
//	type			-	type of vertex to generate
//	colour			-	defines the colour to use if vertex type has colour
//
//	Description:
//	Creates and stores a MeshData in memory
//
//----------------------------------------------------------------------
MeshData* CResourceManager::CreateMeshDataCube(const std::string &cubeID, int size, int tessellation,
		EVertexType type, const DirectX::XMFLOAT4 &colour)
{
	if(m_pMeshDataManager)
	{
		return m_pMeshDataManager->CreateCube(cubeID, size, tessellation, type, colour);
	}

	return NULL;
}


//----------------------------------------------------------------------
//
//	Params:
//	vertexID	-	ID of vertex buffer to store in map
//	indexID		-	ID of index buffer to store in map
//	pMeshData	-	Pointer to model data
//	pOutVertBuf	-	Returns pointer to created vertex buffer
//	pOutIdxBuf	-	Returns pointer to created index buffer
//
//	Description:
//	Method creates vertex and index buffers from passed in MeshData containing
//	the model data
//
//----------------------------------------------------------------------
bool CResourceManager::CreateVertexIndexBuffers(const std::string &vertexID, const std::string &indexID,
	const MeshData *pMeshData, ID3D11Buffer *pOutVertBuf, ID3D11Buffer *pOutIdxBuf)
{
	ID3D11Device *pDevice = m_pD3DBase->GetDevice();
	
	// Create the vertex buffer
	if(!m_pBufferManager->CreateVertexBuffer(pDevice, vertexID, pMeshData->vertexCount, pMeshData->pVertices, &pOutVertBuf))
	{
		// Failed to create vertex buffer
		return false;
	}

	// Create the index buffer
	if(!m_pBufferManager->CreateIndexBuffer(pDevice, indexID, pMeshData->indexCount, pMeshData->pIndices, &pOutIdxBuf))
	{
		// Failed to create the index buffer
		return false;
	}

	return true;
}


//----------------------------------------------------------------------
//
//	Params:
//	textureID	-	ID of texture to store in map
//	fileName	-	Location of texture file
//	pOutTexture	-	Output pointer to the texture
//
//	Description:
//	Creates and stores a texture in memory.
//
//----------------------------------------------------------------------
bool CResourceManager::CreateTexture(const std::string &textureID, const std::string &fileName,
	ID3D11ShaderResourceView *pOutTexture)
{
	return m_pTextureManager->CreateTexture(m_pD3DBase, textureID, fileName, pOutTexture);
}


CMeshDataManager* CResourceManager::GetMeshDataManager(void)
{
	return m_pMeshDataManager;
}


CBufferManager* CResourceManager::GetBufferManager(void)
{
	return m_pBufferManager;
}


CTextureManager* CResourceManager::GetTextureManager(void)
{
	return m_pTextureManager;
}


void CResourceManager::ShutDown(void)
{
	// Note - Not this classes responsibility to clean up the CD3DBase object.
	// Therefore DO NOT DELETE!

	if(m_pTextureManager)
		delete m_pTextureManager;

	if(m_pBufferManager)
		delete m_pBufferManager;

	if(m_pMeshDataManager)
		delete m_pMeshDataManager;

	m_pTextureManager = NULL;
	m_pBufferManager = NULL;
	m_pMeshDataManager =  NULL;
}