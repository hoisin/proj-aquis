#include "CModelTriangle.h"

CModelTriangle::CModelTriangle(float size, float red, float green, float blue) : 
	m_size(size), m_red(red), m_green(green), m_blue(blue)
{
	if(m_size <= 0)
		m_size = 1;
	
	if(m_red < 0)
		m_red = 0;

	if(m_green < 0)
		m_green = 0;

	if(m_blue < 0)
		m_blue = 0;
}


CModelTriangle::CModelTriangle(const CModelTriangle& other)
{
	m_size = other.m_size;
}


CModelTriangle::~CModelTriangle(void)
{
	VShutDown();
}


bool CModelTriangle::VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
		const std::string fileTextureName, const std::string fileModelName)
{
	return CModelBase::VInitialise(pDevice, pContext, fileTextureName, fileModelName);
}


void CModelTriangle::VShutDown(void)
{
	if(!m_pModelVertices.empty())
	{
		for(int i = 0; i < static_cast<int>(m_pModelVertices.size()); i++)
		{
			delete m_pModelVertices[i];
			m_pModelVertices[i] = NULL;
		}
	}

	// Clear all elements
	m_vIndices.clear();
	m_pModelVertices.clear();

	// Call base VShutDown()
	CModelBase::VShutDown();
}


bool CModelTriangle::VInitialiseBuffers(ID3D11Device* pDevice)
{
	VertexTypePC* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// Create the vertex array.
	vertices = new VertexTypePC[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for(int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = DirectX::XMFLOAT3(m_pModelVertices[i]->x, m_pModelVertices[i]->y, m_pModelVertices[i]->z);
		vertices[i].colour = DirectX::XMFLOAT4(m_pModelVertices[i]->r, m_pModelVertices[i]->g, m_pModelVertices[i]->b, m_pModelVertices[i]->a);
	}

	indices = new unsigned long[m_indexCount];

	// Load index data
	for(int i = 0; i < m_indexCount; i++)
		indices[i] = m_vIndices[i];

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexTypePC) * m_vertexCount;
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
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
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
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


bool CModelTriangle::VLoadModel(const std::string fileModelName)
{
	// Can hardcore this since its just a triangle (main purpose will be for testing)
	m_vertexCount = 3;
	m_indexCount = 3;

	m_pModelVertices.push_back(new ModelVertexTypePC);
	m_pModelVertices.push_back(new ModelVertexTypePC);
	m_pModelVertices.push_back(new ModelVertexTypePC);

	// Distance of each vertex from origin (0,0,0)
	float dist = m_size / 2;

	/*
		Used a simple approach for creating a triangle, therefore will probably not be equilateral.
		Think of placing the triangle in a square. Thats how the points are positioned.
		   1
		    * 
		   / \
		  /   \
	   2 *-----* 3
	*/
	// Top vertex
	m_pModelVertices[0]->x = 0;
	m_pModelVertices[0]->y = dist;
	m_pModelVertices[0]->z = 0;
	m_pModelVertices[0]->r = m_red;
	m_pModelVertices[0]->g = m_green;
	m_pModelVertices[0]->b = m_blue;

	// Bottom left vertex
	m_pModelVertices[0]->x = -dist;
	m_pModelVertices[0]->y = -dist;
	m_pModelVertices[0]->z = 0;
	m_pModelVertices[0]->r = m_red;
	m_pModelVertices[0]->g = m_green;
	m_pModelVertices[0]->b = m_blue;

	// Bottom right vertex
	m_pModelVertices[0]->x = dist;
	m_pModelVertices[0]->y = -dist;
	m_pModelVertices[0]->z = 0;
	m_pModelVertices[0]->r = m_red;
	m_pModelVertices[0]->g = m_green;
	m_pModelVertices[0]->b = m_blue;

	m_vIndices.push_back(0);
	m_vIndices.push_back(1);
	m_vIndices.push_back(2);


	return true;
}


