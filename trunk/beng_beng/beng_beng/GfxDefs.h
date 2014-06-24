//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Numerous graphics definitions.
//	Using 3rd party math library GLM
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __GFXDEFS_H__
#define __GFXDEFS_H__

#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <vector>

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
	glm::vec3 position;
	glm::vec3 colour;
};



struct SVertexTypePT : public SVertexType
{
	glm::vec3 position;
	glm::vec2 textureCoord;
};


struct SVertexTypePNC : public SVertexType
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 colour;
};


struct SVertexTypePNT : public SVertexType
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};


struct SVertexTypePNBT : public SVertexType
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 biTangent;
	glm::vec2 texture;
};


struct SVertexTypePNTT : public SVertexType
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec2 texture;
};


struct SVertexTypePNBTT : public SVertexType
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 biTangent;
	glm::vec3 tangent;
	glm::vec2 texture;
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
	Matrix stack
==============================================
*/

class CMatrixStack
{
private:
	std::vector<glm::mat4x4> m_vMatrices;

public:
	CMatrixStack(void) {};
	~CMatrixStack(void) {};

	// Adds matrix to top of stack
	void Push(const glm::mat4x4 &matrix)
	{
		m_vMatrices.push_back(matrix);
	}

	// Removes a matrix from the top of the stack and returns it
	glm::mat4x4 Pop(void)
	{
		glm::mat4x4 temp = m_vMatrices[(m_vMatrices.size() - 1)];
		m_vMatrices.pop_back();

		return temp;
	}

	// Clears stack
	void Empty(void)
	{
		m_vMatrices.clear();
	}

	// Gets the top matrix (doesn't remove it like pop)
	glm::mat4x4 GetTop(void)
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
	SVertexType*			pVertices;		// Pointer to vertex data
	unsigned int*			pIndices;		// Pointer to index data
	int						vertexCount;	// Vertex count
	int						indexCount;		// Index count
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
		pIndices = new unsigned int[idxCount];
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




#endif