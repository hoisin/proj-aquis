#include "CD3DModel.h"
#include "CD3DBase.h"
#include "ErrorCodes.h"

CD3DModel::CD3DModel(void) :
	m_vertexBuffer(NULL),
	m_indexBuffer(NULL),
	m_pTexture(NULL),
	m_vertexCount(0),
	m_indexCount(0),
	m_vertexSize(0)
{
}


CD3DModel::CD3DModel(const CD3DModel& other) :
	m_vertexBuffer(NULL),
	m_indexBuffer(NULL),
	m_pTexture(NULL),
	m_vertexCount(0),
	m_indexCount(0),
	m_vertexSize(0)
{
	// For now don't do anything but same as default c'tor
}


CD3DModel::~CD3DModel(void)
{
	ShutDown();
}


/*
	Inits stuff...
*/
int CD3DModel::Initialise(CD3DBase* pD3d, MeshData* pData, const std::string& modelName, const std::string fileTextureName)
{
	// User friendly ID for reference
	m_name = modelName;
	m_vertType = pData->m_vertexType;

	int errorCode = ERROR_FAIL;

	// This is dependant on VLoadModel
	errorCode = VInitialiseBuffers(pD3d->GetDevice(), pData);
	if( !SUCCESS(errorCode) )
		return errorCode;

	// Called last as its independant to the other two calls
	errorCode = VLoadTexture(pD3d->GetDevice(), pD3d->GetContext(), fileTextureName);
	if( !SUCCESS(errorCode) )
		return errorCode;

	return ERROR_PASS;
}


void CD3DModel::ShutDown(void)
{
	VReleaseTexture();
	VShutDownBuffers();
}


void CD3DModel::Render(CD3DBase* pD3d)
{
	VRenderBuffers(pD3d->GetContext());
}


ID3D11ShaderResourceView* CD3DModel::GetTexture(void)
{
	return m_pTexture->GetTexture();
}


EVertexType CD3DModel::GetVertexType(void)
{
	return m_vertType;
}


int CD3DModel::VInitialiseBuffers(ID3D11Device* pDevice, MeshData* pData)
{
	// If invalid data, return false
	if((int)pData->m_pvVertices.size() <= 0 || (int)pData->m_indices.size() <= 0)
	{
		return ERROR_GFX_VERT_BUFFER_CREATE;
	}

	SVertexType* vertices = NULL;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// Load in vertex and index counts
	m_vertexCount = pData->m_pvVertices.size();
	m_indexCount = pData->m_indices.size();

	// Create the vertex array.
	//CopyVertexData(&vertices, pData);
	vertices = pData->m_pvVertices;

	indices = new unsigned long[m_indexCount];

	// Load index data
	for(int i = 0; i < m_indexCount; i++)
		indices[i] = pData->m_indices[i];

	// Get size of vertex in bytes
	m_vertexSize = GetSizeOfVertexType(pData->m_vertexType);

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.ByteWidth = m_vertexSize * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	HRESULT result = pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return ERROR_GFX_VERT_BUFFER_CREATE;
	}
	
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = pDevice->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return ERROR_GFX_INDEX_BUFFER_CREATE;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return ERROR_PASS;
}


void CD3DModel::VShutDownBuffers(void)
{
	if(m_indexBuffer)
		m_indexBuffer->Release();

	if(m_vertexBuffer)
		m_vertexBuffer->Release();

	m_indexBuffer = NULL;
	m_vertexBuffer = NULL;
}


void CD3DModel::VRenderBuffers(ID3D11DeviceContext* pContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = m_vertexSize; 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	pContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	pContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


int CD3DModel::VLoadTexture(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string fileTextureName)
{
	if(fileTextureName != "NULL")
	{
		m_pTexture = new CTexture;

		if(!m_pTexture->VInitialise(pDevice, pContext, fileTextureName))
			return ERROR_GFX_WIC_CREATE_TEXTURE;

		return ERROR_PASS;
	}

	return ERROR_GFX_WIC_CREATE_TEXTURE;
}


void CD3DModel::VReleaseTexture(void)
{
	if(m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = NULL;
	}
}


void CD3DModel::CopyVertexData(SVertexType** pVertices, MeshData* pData)
{
	if(pData->m_pvVertices.size() > 0)
	{
		switch(pData->m_vertexType)
		{
		case eVertexPC:
			SVertexTypePC* verticesPC;

			// Create the vertex array.
			verticesPC = new SVertexTypePC[m_vertexCount];

			// Load the vertex array and index array with data.
			for(int i = 0; i < m_vertexCount; i++)
			{
				SVertexTypePC* vertex = static_cast<SVertexTypePC*>(pData->m_pvVertices[i]);

				verticesPC[i].position = DirectX::XMFLOAT3(
					vertex->position.x, 
					vertex->position.y,
					vertex->position.z);

				verticesPC[i].colour = DirectX::XMFLOAT4(
					vertex->colour.x, 
					vertex->colour.y, 
					vertex->colour.z,
					vertex->colour.w);
			}

			*pVertices = verticesPC;

			break;

		case eVertexPT:
			SVertexTypePT* verticesPT;

			// Create the vertex array.
			verticesPT = new SVertexTypePT[m_vertexCount];

			// Load the vertex array and index array with data.
			for(int i = 0; i < m_vertexCount; i++)
			{
				SVertexTypePT* vertex = static_cast<SVertexTypePT*>(pData->m_pvVertices[i]);

				verticesPT[i].position = DirectX::XMFLOAT3(
					vertex->position.x, 
					vertex->position.y,
					vertex->position.z);

				verticesPT[i].textureCoord = DirectX::XMFLOAT2(
					vertex->textureCoord.x, 
					vertex->textureCoord.y);
			}

			*pVertices = verticesPT;

			break;

		case eVertexPNT:
			SVertexTypePNT* verticesPNT;

			// Create the vertex array.
			verticesPNT = new SVertexTypePNT[m_vertexCount];

			// Load the vertex array and index array with data.
			for(int i = 0; i < m_vertexCount; i++)
			{
				SVertexTypePNT* vertex = static_cast<SVertexTypePNT*>(pData->m_pvVertices[i]);

				verticesPNT[i].position = DirectX::XMFLOAT3(
					vertex->position.x, 
					vertex->position.y,
					vertex->position.z);

				verticesPNT[i].normal = DirectX::XMFLOAT3(
					vertex->normal.x, 
					vertex->normal.y, 
					vertex->normal.z);

				verticesPNT[i].texture = DirectX::XMFLOAT2(
					vertex->texture.x,
					vertex->texture.y);
			}

			*pVertices = verticesPNT;
			break;

		default:
			break;
		}
	}
}