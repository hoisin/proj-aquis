#include "CMeshDataGenerator.h"


CMeshDataGenerator::CMeshDataGenerator()
{
}


CMeshDataGenerator::~CMeshDataGenerator()
{
}


//-------------------------------------------------------------------------------------
//
//	CreateTriangle(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of triangle
//	type			-	type of vertices to use
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a single triangle specifed of size "size".
//	Note that this creates a equilateral triangle hence only the single param of size.
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreateTriangle(const std::string &geometryID, float size, EVertexType type,
	const glm::vec4 &colour)
{
	// Create mesh data
	MeshData* pNewGeometry = new MeshData(type, 3, 3);

	// Distance of each vertex from origin (0,0,0)
	float dist = size / 2;

	// Calculate vertex data
	switch(type)
	{
	case eVertexPC:
		/*
		Used a simple approach for creating a triangle, therefore will probably not be equilateral.
		Think of placing the triangle in a square. Thats how the points are positioned.
					1
					* 
				   / \
			      /   \
		       2 *-----* 3
		*/

		SVertexTypePC* pVertexPC;

		// Top vertex
		pVertexPC = static_cast<SVertexTypePC*>(pNewGeometry->pVertices);
		pVertexPC[0].position.x = 0;
		pVertexPC[0].position.y = dist;
		pVertexPC[0].position.z = 0;
		pVertexPC[0].colour.x = colour.x;
		pVertexPC[0].colour.y = colour.y;
		pVertexPC[0].colour.z = colour.z;
		pVertexPC[0].colour.w = colour.w;

		// Bottom left vertex
		pVertexPC[1].position.x = -dist;
		pVertexPC[1].position.y = -dist;
		pVertexPC[1].position.z = 0;
		pVertexPC[1].colour.x = colour.x;
		pVertexPC[1].colour.y = colour.y;
		pVertexPC[1].colour.z = colour.z;
		pVertexPC[1].colour.w = colour.w;

		// Bottom right vertex
		pVertexPC[2].position.x = dist;
		pVertexPC[2].position.y = -dist;
		pVertexPC[2].position.z = 0;
		pVertexPC[2].colour.x = colour.x;
		pVertexPC[2].colour.y = colour.y;
		pVertexPC[2].colour.z = colour.z;
		pVertexPC[2].colour.w = colour.w;
		break;

	case eVertexPT:
		/*
		Used a simple approach for creating a triangle, therefore will probably not be equilateral.
		Think of placing the triangle in a square. Thats how the points are positioned.
					1
					* 
				   / \
			      /   \
		       2 *-----* 3
		*/

		SVertexTypePT* pVertexPT;

		// Top vertex
		pVertexPT = static_cast<SVertexTypePT*>(pNewGeometry->pVertices);
		pVertexPT[0].position.x = 0;
		pVertexPT[0].position.y = dist;
		pVertexPT[0].position.z = 0;
		pVertexPT[0].textureCoord.x = 0;
		pVertexPT[0].textureCoord.y = 0.5;

		// Bottom left vertex
		pVertexPT[1].position.x = -dist;
		pVertexPT[1].position.y = -dist;
		pVertexPT[1].position.z = 0;
		pVertexPT[1].textureCoord.x = 0;
		pVertexPT[1].textureCoord.y = 1;

		// Bottom right vertex
		pVertexPT[2].position.x = dist;
		pVertexPT[2].position.y = -dist;
		pVertexPT[2].position.z = 0;
		pVertexPT[2].textureCoord.x = 1;
		pVertexPT[2].textureCoord.y = 1;
		break;

	case eVertexPNC:
		/*
		Used a simple approach for creating a triangle, therefore will probably not be equilateral.
		Think of placing the triangle in a square. Thats how the points are positioned.
					1
					* 
				   / \
			      /   \
		       2 *-----* 3
		*/

		SVertexTypePNC* pVert;

		// Top vertex
		pVert = static_cast<SVertexTypePNC*>(pNewGeometry->pVertices);
		pVert[0].position.x = 0;
		pVert[0].position.y = dist;
		pVert[0].position.z = 0;
		pVert[0].normal.x = 0;
		pVert[0].normal.y = 0;
		pVert[0].normal.z = -1;
		pVert[0].colour.x = colour.x;
		pVert[0].colour.y = colour.y;
		pVert[0].colour.y = colour.z;
		pVert[0].colour.w = colour.w;

		// Bottom left vertex
		pVert[1].position.x = -dist;
		pVert[1].position.y = -dist;
		pVert[1].position.z = 0;
		pVert[1].normal.x = 0;
		pVert[1].normal.y = 0;
		pVert[1].normal.z = -1;
		pVert[1].colour.x = colour.x;
		pVert[1].colour.y = colour.y;
		pVert[1].colour.y = colour.z;
		pVert[1].colour.w = colour.w;

		// Bottom right vertex
		pVert[2].position.x = dist;
		pVert[2].position.y = -dist;
		pVert[2].position.z = 0;
		pVert[2].normal.x = 0;
		pVert[2].normal.y = 0;
		pVert[2].normal.z = -1;
		pVert[2].colour.x = colour.x;
		pVert[2].colour.y = colour.y;
		pVert[2].colour.y = colour.z;
		pVert[2].colour.w = colour.w;
		break;

	case eVertexPNT:
		/*
		Used a simple approach for creating a triangle, therefore will probably not be equilateral.
		Think of placing the triangle in a square. Thats how the points are positioned.
					1
					* 
				   / \
			      /   \
		       2 *-----* 3
		*/

		SVertexTypePNT* pVertexPNT;

		// Top vertex
		pVertexPNT = static_cast<SVertexTypePNT*>(pNewGeometry->pVertices);
		pVertexPNT[0].position.x = 0;
		pVertexPNT[0].position.y = dist;
		pVertexPNT[0].position.z = 0;
		pVertexPNT[0].normal.x = 0;
		pVertexPNT[0].normal.y = 0;
		pVertexPNT[0].normal.z = -1;
		pVertexPNT[0].texture.x = 0;
		pVertexPNT[0].texture.y = 0.5;

		// Bottom left vertex
		pVertexPNT[1].position.x = -dist;
		pVertexPNT[1].position.y = -dist;
		pVertexPNT[1].position.z = 0;
		pVertexPNT[1].normal.x = 0;
		pVertexPNT[1].normal.y = 0;
		pVertexPNT[1].normal.z = -1;
		pVertexPNT[1].texture.x = 0;
		pVertexPNT[1].texture.y = 1;

		// Bottom right vertex
		pVertexPNT[2].position.x = dist;
		pVertexPNT[2].position.y = -dist;
		pVertexPNT[2].position.z = 0;
		pVertexPNT[2].normal.x = 0;
		pVertexPNT[2].normal.y = 0;
		pVertexPNT[2].normal.z = -1;
		pVertexPNT[2].texture.x = 1;
		pVertexPNT[2].texture.y = 1;
		break;

	// shouldn't end up here
	default:
		delete pNewGeometry;
		pNewGeometry = NULL;
		break;
	}

	// Add indices
	pNewGeometry->pIndices[0] = 0;
	pNewGeometry->pIndices[1] = 2;
	pNewGeometry->pIndices[2] = 1;

	// Return reference to newly created geometry
	return pNewGeometry;
}