#include "CBufferManager.h"
#include "ErrorCodes.h"

CBufferManager::CBufferManager(void)
{
}


CBufferManager::~CBufferManager(void)
{
}


int CBufferManager::CreateVertexBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer)
{
	// If empty data, return error
	if(pData->vertexCount <= 0)
	{
		return ERROR_GFX_VERT_BUFFER_CREATE;
	}

	SVertexType* vertices = NULL;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	// Get vertex data
	vertices = pData->pVertices;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.ByteWidth = GetSizeOfVertexType(pData->vertexType) * pData->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	HRESULT result = pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, inBuffer);

	if(FAILED(result))
	{
		return ERROR_GFX_VERT_BUFFER_CREATE;
	}

	// Create buffer info
	SBufferInfo newInfo;

	// Generate name
	char bufferCntStr[10];
	sprintf(bufferCntStr, "%d", m_vertexBuffers.size());
	std::string vertBufferNum(bufferCntStr);
	newInfo.name = "vertex_buffer_" + vertBufferNum;

	// Store created buffer
	newInfo.buffer = *inBuffer;

	// Add to list
	m_vertexBuffers.push_back(newInfo);

	return true;
}


int CBufferManager::CreateInstanceBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer)
{
	return true;
}


int CBufferManager::CreateIndexBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer)
{
	// If invalid data, return false
	if(pData->indexCount <= 0)
	{
		return ERROR_GFX_VERT_BUFFER_CREATE;
	}

	unsigned long* indices;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;

	indices = pData->pIndices;
	
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * pData->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	HRESULT result = pDevice->CreateBuffer(&indexBufferDesc, &indexData, &inBuffer);

	if(FAILED(result))
	{
		return ERROR_GFX_INDEX_BUFFER_CREATE;
	}

	// Create buffer info
	SBufferInfo newInfo;

	// Generate name
	char bufferCntStr[10];
	sprintf(bufferCntStr, "%d", m_indexBuffers.size());
	std::string vertBufferNum(bufferCntStr);
	newInfo.name = "index_buffer_" + vertBufferNum;

	// Store created buffer
	newInfo.buffer = *inBuffer;

	// Add to list
	m_indexBuffers.push_back(newInfo);

	return ERROR_PASS;
}


void CBufferManager::ShutDown(void)
{
	std::vector<SBufferInfo>::iterator ita;

	for(ita = m_indexBuffers.begin(); ita != m_indexBuffers.end(); ita++)
	{
		ita->buffer->Release();
		ita->buffer = NULL;
	}

	for(ita = m_instanceBuffers.begin(); ita != m_instanceBuffers.end(); ita++)
	{
		ita->buffer->Release();
		ita->buffer = NULL;
	}

	for(ita = m_vertexBuffers.begin(); ita != m_vertexBuffers.end(); ita++)
	{
		ita->buffer->Release();
		ita->buffer = NULL;
	}
}

