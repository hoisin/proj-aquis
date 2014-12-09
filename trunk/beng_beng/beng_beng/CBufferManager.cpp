#include "CBufferManager.h"


CBufferManager::CBufferManager()
{
}


CBufferManager::~CBufferManager()
{
}


CVertexBuffer* CBufferManager::CreateVertexBuffer(const std::string& vertexID, MeshData* pData)
{
	CVertexBuffer* pNewVertexBuffer = new CVertexBuffer;

	pNewVertexBuffer->LoadData(pData->pVertices, pData->vertexCount, pData->vertexType);

	m_vertexBufferMap.insert(std::pair<std::string, CVertexBuffer*>(vertexID, pNewVertexBuffer));

	return pNewVertexBuffer;
}


CIndexBuffer* CBufferManager::CreateIndexBuffer(const std::string& indexID, MeshData* pData)
{
	CIndexBuffer* pNewIndexBuffer = new CIndexBuffer;

	pNewIndexBuffer->LoadData(pData->pIndices, pData->indexCount);

	m_indexBufferMap.insert(std::pair<std::string, CIndexBuffer*>(indexID, pNewIndexBuffer));

	return pNewIndexBuffer;
}


CVertexBuffer* CBufferManager::GetVertexBuffer(const std::string& vertexID)
{
	std::map<std::string, CVertexBuffer*>::iterator it = m_vertexBufferMap.find(vertexID);

	if(it == m_vertexBufferMap.end())
		return NULL;

	return it->second;
}


CIndexBuffer* CBufferManager::GetIndexBuffer(const std::string& indexID)
{
	std::map<std::string, CIndexBuffer*>::iterator it = m_indexBufferMap.find(indexID);

	if(it == m_indexBufferMap.end())
		return NULL;

	return it->second;
}


void CBufferManager::CleanUp()
{
	std::map<std::string, CVertexBuffer*>::iterator vertexIt = m_vertexBufferMap.begin();
	std::map<std::string, CIndexBuffer*>::iterator indexIt = m_indexBufferMap.begin();

	for(; indexIt != m_indexBufferMap.end(); ++indexIt)
	{
		delete indexIt->second;
		indexIt->second = NULL;
	}

	for(; vertexIt != m_vertexBufferMap.end(); ++vertexIt)
	{
		delete vertexIt->second;
		vertexIt->second = NULL;
	}
}
