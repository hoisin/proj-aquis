#include "CBufferManager.h"
#include "ErrorCodes.h"

CBufferManager::CBufferManager(void)
{
}


CBufferManager::~CBufferManager(void)
{
	ClearVertexBuffers();
	ClearIndexBuffers();
}


bool CBufferManager::CreateVertexBuffer(ID3D11Device* pDevice, const std::string& nameID, 
	int bufferSize, void* pData, ID3D11Buffer** outBuffer)
{
	// If empty data, return error
	if(pData == NULL)
	{
		return false;
	}

	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.ByteWidth = bufferSize;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = pData;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	ID3D11Buffer* pNewBuffer = NULL;

	// Now create the vertex buffer.
	HRESULT result = pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &pNewBuffer);

	if(FAILED(result))
	{
		return false;
	}

	// Add to list
	m_vertexBuffers.insert(std::pair<std::string, ID3D11Buffer*>(nameID, pNewBuffer));

	outBuffer = &pNewBuffer;

	return true;
}


//int CBufferManager::CreateInstanceBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer)
//{
//	return true;
//}


bool CBufferManager::CreateIndexBuffer(ID3D11Device* pDevice, const std::string& nameID, int bufferSize,
	void* pData,  ID3D11Buffer** outBuffer)
{
	// If invalid data, return false
	if(pData == NULL)
	{
		return false;
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;

	
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = bufferSize;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = pData;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	ID3D11Buffer* pNewBuffer = NULL;

	// Create the index buffer.
	HRESULT result = pDevice->CreateBuffer(&indexBufferDesc, &indexData, &pNewBuffer);

	if(FAILED(result))
	{
		return false;
	}

	// Add to list
	m_indexBuffers.insert(std::pair<std::string, ID3D11Buffer*>(nameID, pNewBuffer));

	outBuffer = &pNewBuffer;

	return true;
}


ID3D11Buffer* CBufferManager::GetVertexBuffer(const std::string& nameID)
{
	std::map<std::string, ID3D11Buffer*>::iterator it = m_vertexBuffers.find(nameID);

	if(it != m_vertexBuffers.end())
	{
		return it->second;
	}

	return NULL;
}


ID3D11Buffer* CBufferManager::GetIndexBuffer(const std::string& nameID)
{
	std::map<std::string, ID3D11Buffer*>::iterator it = m_indexBuffers.find(nameID);

	if(it != m_indexBuffers.end())
	{
		return it->second;
	}

	return NULL;
}


void CBufferManager::FreeVertexBuffer(const std::string& nameID)
{
	std::map<std::string, ID3D11Buffer*>::iterator it = m_vertexBuffers.find(nameID);

	if(it != m_indexBuffers.end())
	{
		it->second->Release();
		it->second = NULL;
		m_vertexBuffers.erase(it);
	}
}


void CBufferManager::FreeIndexBufffer(const std::string& nameID)
{
	std::map<std::string, ID3D11Buffer*>::iterator it = m_indexBuffers.find(nameID);

	if(it != m_indexBuffers.end())
	{
		it->second->Release();
		it->second = NULL;
		m_indexBuffers.erase(it);
	}
}


void CBufferManager::ClearVertexBuffers(void)
{
	std::map<std::string, ID3D11Buffer*>::iterator ita;

	for(ita = m_vertexBuffers.begin(); ita != m_vertexBuffers.end(); ita++)
	{
		ita->second->Release();
		ita->second = NULL;
	}
}


void CBufferManager::ClearIndexBuffers(void)
{
	std::map<std::string, ID3D11Buffer*>::iterator ita;

	for(ita = m_indexBuffers.begin(); ita != m_indexBuffers.end(); ita++)
	{
		ita->second->Release();
		ita->second = NULL;
	}
}