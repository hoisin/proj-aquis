#include "CModelCube.h"

CModelCube::CModelCube(float size, int tessellation) : m_size(size), m_tessellation(tessellation)
{
	if(m_size <= 0)
		m_size = 1;

	if(m_tessellation < 1)
		m_tessellation = 1;
}


CModelCube::CModelCube(const CModelCube& other)
{
	m_size = other.m_size;
	m_tessellation = other.m_tessellation;
}


CModelCube::~CModelCube(void)
{
	VShutDown();
}


bool CModelCube::VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
		const std::string fileTextureName, const std::string fileModelName)
{
	return CModelBase::VInitialise(pDevice, pContext, fileTextureName, fileModelName);
}


void CModelCube::VShutDown(void)
{
	if(!m_pModelVertices.empty())
	{
		for(int i = 0; i < m_pModelVertices.size(); i++)
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


bool CModelCube::VInitialiseBuffers(ID3D11Device* pDevice)
{
	VertexTypePNT* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// Create the vertex array.
	vertices = new VertexTypePNT[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for(int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = DirectX::XMFLOAT3(m_pModelVertices[i]->x, m_pModelVertices[i]->y, m_pModelVertices[i]->z);
		vertices[i].normal = DirectX::XMFLOAT3(m_pModelVertices[i]->nx, m_pModelVertices[i]->ny, m_pModelVertices[i]->nz);
		vertices[i].texture = DirectX::XMFLOAT2(m_pModelVertices[i]->tu, m_pModelVertices[i]->tv);
	}

	// Load index data
	for(int i = 0; i < m_indexCount; i++)
		indices[i] = m_vIndices[i];

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexTypePNT) * m_vertexCount;
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


bool CModelCube::VLoadModel(const std::string fileModelName)
{
	// Number of vertices on one side of the cube
	int faceVerts = (m_tessellation + 1) * (m_tessellation + 1);

	// Total number of vertices of the cube
	int totalVerts = faceVerts * 6;

	m_vertexCount = totalVerts;
	m_indexCount = (m_tessellation * m_tessellation) * 2;

	// Create empty vertices
	for(int i = 0; i < m_vertexCount; i++)
		m_pModelVertices.push_back(new ModelVertexTypePNT);

	/*
		m_tessellation * m_tessellation = number of faces / cells on a face of cube
		6 = number of faces on cube
		2 = 2 triangles per face
		3 = 3 indices per triangle
	*/
	int numIndices = ((m_tessellation * m_tessellation * 6) * 2) * 3;

	for(int j = 0; j < numIndices; j++)
		m_vIndices.push_back(int(0));

	// Cube generated of length size centred at (0,0,0)
	// ------------- Begin Cube Generation -------------

	// Calc space inbetween vertices (same for x and y directions)
	float incrementDist = m_size / m_tessellation;

	// ---Vertex/Index Generation---
	int vertexCoutner = 0;

	// Front face
	for(int y = 0; y < (m_tessellation + 1); y++)
	{
		float xStart = -(m_size / 2);
		float yStart = m_size / 2;
		float zStart = -(m_size / 2);

		for(int x = 0; x < (m_tessellation + 1); x++)
		{
			m_pModelVertices[vertexCoutner]->x = xStart + (x * incrementDist);
			m_pModelVertices[vertexCoutner]->y = yStart - (y * incrementDist);
			m_pModelVertices[vertexCoutner]->z = zStart;
			m_pModelVertices[vertexCoutner]->nx = 0.0;
			m_pModelVertices[vertexCoutner]->ny = 0.0;
			m_pModelVertices[vertexCoutner]->nz = -1.0;
			m_pModelVertices[vertexCoutner]->tu = (float)x / (float)(m_tessellation + 1);
			m_pModelVertices[vertexCoutner]->tu = (float)y / (float)(m_tessellation + 1);

			vertexCoutner++;
		}
	}

	// bottom face
	for(int y = 0; y < (m_tessellation + 1); y++)
	{
		float xStart = -(m_size / 2);
		float yStart = -(m_size / 2);
		float zStart = -(m_size / 2);

		for(int x = 0; x < (m_tessellation + 1); x++)
		{
			m_pModelVertices[vertexCoutner]->x = xStart + (x * incrementDist);
			m_pModelVertices[vertexCoutner]->y = yStart;
			m_pModelVertices[vertexCoutner]->z = zStart + (y * incrementDist);
			m_pModelVertices[vertexCoutner]->nx = 0.0;
			m_pModelVertices[vertexCoutner]->ny = -1.0;
			m_pModelVertices[vertexCoutner]->nz = 0.0;
			m_pModelVertices[vertexCoutner]->tu = (float)x / (float)(m_tessellation + 1);
			m_pModelVertices[vertexCoutner]->tu = (float)y / (float)(m_tessellation + 1);

			vertexCoutner++;
		}
	}

	// Left face
	for(int y = 0; y < (m_tessellation + 1); y++)
	{
		float xStart = -(m_size / 2);
		float yStart = m_size / 2;
		float zStart = m_size / 2;

		for(int x = 0; x < (m_tessellation + 1); x++)
		{
			m_pModelVertices[vertexCoutner]->x = xStart;
			m_pModelVertices[vertexCoutner]->y = yStart - (y * incrementDist);
			m_pModelVertices[vertexCoutner]->z = zStart - (x * incrementDist);
			m_pModelVertices[vertexCoutner]->nx = -1.0;
			m_pModelVertices[vertexCoutner]->ny = 0.0;
			m_pModelVertices[vertexCoutner]->nz = 0.0;
			m_pModelVertices[vertexCoutner]->tu = (float)x / (float)(m_tessellation + 1);
			m_pModelVertices[vertexCoutner]->tu = (float)y / (float)(m_tessellation + 1);

			vertexCoutner++;
		}
	}

	// Back face
	for(int y = 0; y < (m_tessellation + 1); y++)
	{
		float xStart = m_size / 2;
		float yStart = m_size / 2;
		float zStart = m_size / 2;

		for(int x = 0; x < (m_tessellation + 1); x++)
		{
			m_pModelVertices[vertexCoutner]->x = xStart - (x * incrementDist);
			m_pModelVertices[vertexCoutner]->y = yStart - (y * incrementDist);
			m_pModelVertices[vertexCoutner]->z = zStart;
			m_pModelVertices[vertexCoutner]->nx = 0.0;
			m_pModelVertices[vertexCoutner]->ny = 0.0;
			m_pModelVertices[vertexCoutner]->nz = 1.0;
			m_pModelVertices[vertexCoutner]->tu = (float)x / (float)(m_tessellation + 1);
			m_pModelVertices[vertexCoutner]->tu = (float)y / (float)(m_tessellation + 1);

			vertexCoutner++;
		}
	}

	// Right face
	for(int y = 0; y < (m_tessellation + 1); y++)
	{
		float xStart = m_size / 2;
		float yStart = m_size / 2;
		float zStart = -(m_size / 2);

		for(int x = 0; x < (m_tessellation + 1); x++)
		{
			m_pModelVertices[vertexCoutner]->x = xStart;
			m_pModelVertices[vertexCoutner]->y = yStart - (y * incrementDist);
			m_pModelVertices[vertexCoutner]->z = zStart + (x * incrementDist);
			m_pModelVertices[vertexCoutner]->nx = 1.0;
			m_pModelVertices[vertexCoutner]->ny = 0.0;
			m_pModelVertices[vertexCoutner]->nz = 0.0;
			m_pModelVertices[vertexCoutner]->tu = (float)x / (float)(m_tessellation + 1);
			m_pModelVertices[vertexCoutner]->tu = (float)y / (float)(m_tessellation + 1);

			vertexCoutner++;
		}
	}

	// Top face
	for(int y = 0; y < (m_tessellation + 1); y++)
	{
		float xStart = -(m_size / 2);
		float yStart = m_size / 2;
		float zStart = (m_size / 2);

		for(int x = 0; x < (m_tessellation + 1); x++)
		{
			m_pModelVertices[vertexCoutner]->x = xStart + (x * incrementDist);
			m_pModelVertices[vertexCoutner]->y = yStart;
			m_pModelVertices[vertexCoutner]->z = zStart - (y * incrementDist);
			m_pModelVertices[vertexCoutner]->nx = 0.0;
			m_pModelVertices[vertexCoutner]->ny = 1.0;
			m_pModelVertices[vertexCoutner]->nz = 0.0;
			m_pModelVertices[vertexCoutner]->tu = (float)x / (float)(m_tessellation + 1);
			m_pModelVertices[vertexCoutner]->tu = (float)y / (float)(m_tessellation + 1);

			vertexCoutner++;
		}
	}

	int indexCounter = 0;
	int vIndex = 0;
	int numVertsX = m_tessellation + 1;

	// 6 faces in total so loop
	for(int i = 0; i < 6; i++)
	{
		// Loops for generating indices for a face
		for (int y = 0; y < m_tessellation; y++)
		{
			for (int x = 0; x < m_tessellation; x++)
			{
				// first triangle
				m_vIndices[indexCounter++] = vIndex;
				m_vIndices[indexCounter++] = vIndex + numVertsX;
				m_vIndices[indexCounter++] = vIndex + numVertsX + 1;

				// second triangle
				m_vIndices[indexCounter++] = vIndex;
				m_vIndices[indexCounter++] = vIndex + numVertsX + 1;
				m_vIndices[indexCounter++] = vIndex + 1;

				vIndex++;
			}
			vIndex++;
		}
	}

	return true;
}


