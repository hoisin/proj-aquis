/*
	Date: 31/01/2013
	Bunch of graphics types data, helper classes and functions
*/

#include <string>
#include <vector>
#include <D3D11.h>
#include <DirectXMath.h>

#pragma once
#ifndef __GFXDEFS_H__
#define __GFXDEFS_H__

/*
==============================================
	Old Vertex Structs (UNUSED)
==============================================
*/

// Vertex Type including: Position, normal and texture
struct VertexTypePC
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 colour;
};


// Vertex Type including: Position, normal and texture
struct VertexTypePNT
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texture;
};



/*
==============================================
	Vertex Structs
==============================================
*/
enum EVertexType
{
	eVertexPC,		// Position & colour
	eVertexPT,		// Position & texture coordinate
	eVertexPNC,		// Position, normal & colour
	eVertexPNT,		// Position, normal & texture coordinate
	eVertexPNTT,	// Position, normal, tangent, texture
	eVertexPNTBT,	// Position, normal, tangent, bi-tangent, texture
	eVertTypeCount
};


// Base type
struct SVertexType
{
	// Empty
};


struct SVertexTypePC : public SVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 colour;
};


struct SVertexTypePT : public SVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 textureCoord;
};


struct SVertexTypePNC : public SVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 colour;
};


struct SVertexTypePNT : public SVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texture;
};


// Helper method (not sure making this inline is a good idea)
inline int GetSizeOfVertexType(EVertexType type)
{
	switch(type)
	{
	case eVertexPC:
		return sizeof(SVertexTypePC);
		break;

	case eVertexPT:
		return sizeof(SVertexTypePT);
		break;

	case eVertexPNC:
		return sizeof(SVertexTypePNC);
		break;

	case eVertexPNT:
		return sizeof(SVertexTypePNT);
		break;

	default:
		return 0;
	}

	return 0;
}

/*
==============================================
	Old Model Structs (UNUSED)
==============================================
*/

// Model type includes: position & colour
struct ModelVertexTypePC
{
	float x, y, z;
	float r, g, b, a;
};



// Model type includes: position, normal and texture
struct ModelVertexTypePNT
{
	float x, y, z;
	float nx, ny, nz;
	float tu, tv;
};


/*
==============================================
	Matrix buffer
==============================================
*/

struct MatrixBufferTypeWVP
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};



/*
==============================================
	Matrix stack
==============================================
*/

class CD3DMatrixStack
{
private:
	std::vector<DirectX::XMFLOAT4X4> m_vMatrices;

public:
	CD3DMatrixStack(void) {};
	~CD3DMatrixStack(void) {};

	// Adds matrix to top of stack
	void Push(DirectX::XMFLOAT4X4 matrix)
	{
		m_vMatrices.push_back(matrix);
	}

	// Removes a matrix from the top of the stack and returns it
	DirectX::XMFLOAT4X4 Pop(void)
	{
		DirectX::XMFLOAT4X4 temp = m_vMatrices[(m_vMatrices.size() - 1)];
		m_vMatrices.pop_back();

		return temp;
	}

	// Clears stack
	void Empty(void)
	{
		m_vMatrices.clear();
	}

	// Gets the top matrix (doesn't remove it like pop)
	DirectX::XMFLOAT4X4 GetTop(void)
	{
		return m_vMatrices[(m_vMatrices.size() - 1)];
	}
};


/*
==============================================
	Mesh Data

	Note: Current structure is MEGA slow, will require refactoring
==============================================
*/

struct MeshData
{
	std::vector<SVertexType* >		m_pvVertices;		// Vertex array		NOTE: Don't use vector, increased performance when use pointer to array
	std::vector<unsigned long>		m_indices;			// Index array
	EVertexType						m_vertexType;		// Format of vertices

	// Introduce vertex and index count when optimising. std::vector will be replaced in favour of pointers pointing to new MyClass []

	MeshData(void) : m_pvVertices(NULL)
	{
	}

	~MeshData(void)
	{
		CleanUp();
	}

	void CleanUp(void)
	{
		for(int i = 0; i < (int)m_pvVertices.size(); i++)
		{
			delete m_pvVertices[i];
			m_pvVertices[i] = NULL;
		}

		m_pvVertices.clear();
	}
};


#endif