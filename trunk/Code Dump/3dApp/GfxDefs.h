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
	Hardware buffer usage enumerate
==============================================
*/

enum EBufferUsage
{
	eBUSAGE_STATIC,
	eBUSAGE_DYNAMIC,
	eBUSAGE_WRITEONLY,
	eBUSAGE_TOTAL
};

/*
==============================================
	Old Vertex Structs (UNUSED) TO BE REMOVED...
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
	eVertexPNBT,	// Position, normal, bi-tangent, texture coordinate
	eVertexPNTT,	// Position, normal, tangent, texture coordinate
	eVertexPNBTT,	// Position, normal, tangent, bi-tangent, texture coordinate
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


struct SVertexTypePNBT : public SVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 biTangent;
	DirectX::XMFLOAT2 texture;
};


struct SVertexTypePNTT : public SVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 tangent;
	DirectX::XMFLOAT2 texture;
};


struct SVertexTypePNBTT : public SVertexType
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 biTangent;
	DirectX::XMFLOAT3 tangent;
	DirectX::XMFLOAT2 texture;
};


// Helper method
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

	case eVertexPNBT:
		return sizeof(SVertexTypePNBT);
		break;

	case eVertexPNTT:
		return sizeof(SVertexTypePNTT);
		break;

	case eVertexPNBTT:
		return sizeof(SVertexTypePNBTT);
		break;

	default:
		return -1;
	}

	// Should'nt reach here anyway
	return -1;
}


/*
==============================================
	Old Model Structs (UNUSED) REMOVE PLS
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
	Light buffer
==============================================
*/

struct LightBuffer
{
	DirectX::XMFLOAT4 lightColour;
	DirectX::XMFLOAT3 lightDirection;
	float lightIntensity;
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
==============================================
*/

struct MeshData
{
	//std::vector<SVertexType* >		m_pvVertices;		// Vertex array		NOTE: Don't use vector, increased performance when use pointer to array
	//std::vector<unsigned long>		m_indices;			// Index array
	SVertexType*			pVertices;
	unsigned long*			pIndices;
	int						vertexCount;
	int						indexCount;
	EVertexType				vertexType;		// Format of vertices

	// Allocates memory for buffer for specified vertex type
	MeshData(EVertexType vertType, int vertCount, int idxCount)
	{
		vertexCount = vertCount;
		indexCount = idxCount;
		vertexType = vertType;

		// Create vertex array depending on type
		switch(vertType)
		{
		case eVertexPC:
			pVertices = new SVertexTypePC[vertCount];
			break;

		case eVertexPT:
			pVertices = new SVertexTypePT[vertCount];
			break;

		case eVertexPNC:
			pVertices = new SVertexTypePNC[vertCount];
			break;

		case eVertexPNT:
			pVertices = new SVertexTypePNT[vertCount];
			break;

		case eVertexPNBT:
			pVertices = new SVertexTypePNBT[vertCount];
			break;

		case eVertexPNTT:
			pVertices = new SVertexTypePNTT[vertCount];
			break;

		case eVertexPNBTT:
			pVertices = new SVertexTypePNBTT[vertCount];
			break;

		default:
			break;
		}

		// Create index array
		pIndices = new unsigned long[idxCount];
	}

	~MeshData(void)
	{
		CleanUp();
	}

	void CleanUp(void)
	{
		if(pIndices)
			delete [] pIndices;

		if(pVertices)
			delete [] pVertices;

		pIndices = NULL;
		pVertices = NULL;
	}
};



/*
==============================================
	Material
==============================================
*/

struct SMaterial
{
};



#endif