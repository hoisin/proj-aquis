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
		
		// Bottom left vertex
		pVertexPC[1].position.x = -dist;
		pVertexPC[1].position.y = -dist;
		pVertexPC[1].position.z = 0;
		pVertexPC[1].colour.x = colour.x;
		pVertexPC[1].colour.y = colour.y;
		pVertexPC[1].colour.z = colour.z;

		// Bottom right vertex
		pVertexPC[2].position.x = dist;
		pVertexPC[2].position.y = -dist;
		pVertexPC[2].position.z = 0;
		pVertexPC[2].colour.x = colour.x;
		pVertexPC[2].colour.y = colour.y;
		pVertexPC[2].colour.z = colour.z;
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
		pVertexPT[0].textureCoord.x = 1;
		pVertexPT[0].textureCoord.y = 1;

		// Bottom left vertex
		pVertexPT[1].position.x = -dist;
		pVertexPT[1].position.y = -dist;
		pVertexPT[1].position.z = 0;
		pVertexPT[1].textureCoord.x = 0;
		pVertexPT[1].textureCoord.y = 0;

		// Bottom right vertex
		pVertexPT[2].position.x = dist;
		pVertexPT[2].position.y = -dist;
		pVertexPT[2].position.z = 0;
		pVertexPT[2].textureCoord.x = 1;
		pVertexPT[2].textureCoord.y = 0;
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


//-------------------------------------------------------------------------------------
//
//	CreateQuad(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of the quad
//	type			-	type of vertices to use
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a 2D quad consisting of 2 triangles
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreateQuad(const std::string &geometryID, float size, EVertexType type,
	const glm::vec4 &colour)
{
	MeshData *pNewGeometry = new MeshData(type, 4, 6);

	// Basing mesh at origin 0,0,0
	float dist = size / 2;

	// Create vertex data
	switch(type)
	{
	case eVertexPC:

		SVertexTypePC *pVertPC;
		
		pVertPC = static_cast<SVertexTypePC*>(pNewGeometry->pVertices);

		pVertPC[0].position.x = -dist;
		pVertPC[0].position.y = dist;
		pVertPC[0].position.z = 0;
		pVertPC[0].colour.r = colour.r;
		pVertPC[0].colour.g = colour.g;
		pVertPC[0].colour.b = colour.b;

		pVertPC[1].position.x = dist;
		pVertPC[1].position.y = dist;
		pVertPC[1].position.z = 0;
		pVertPC[1].colour.r = colour.r;
		pVertPC[1].colour.g = colour.g;
		pVertPC[1].colour.b = colour.b;

		pVertPC[2].position.x = -dist;
		pVertPC[2].position.y = -dist;
		pVertPC[2].position.z = 0;
		pVertPC[2].colour.r = colour.r;
		pVertPC[2].colour.g = colour.g;
		pVertPC[2].colour.b = colour.b;

		pVertPC[3].position.x = dist;
		pVertPC[3].position.y = -dist;
		pVertPC[3].position.z = 0;
		pVertPC[3].colour.r = colour.r;
		pVertPC[3].colour.g = colour.g;
		pVertPC[3].colour.b = colour.b;
		break;

	case eVertexPT:
		SVertexTypePT *pVertPT;

		pVertPT = static_cast<SVertexTypePT*>(pNewGeometry->pVertices);

		pVertPT[0].position.x = -dist;
		pVertPT[0].position.y = dist;
		pVertPT[0].position.z = 0;
		pVertPT[0].textureCoord.x = 0.f;
		pVertPT[0].textureCoord.y = 1.f;

		pVertPT[1].position.x = dist;
		pVertPT[1].position.y = dist;
		pVertPT[1].position.z = 0;
		pVertPT[1].textureCoord.x = 1.f;
		pVertPT[1].textureCoord.y = 1.f;

		pVertPT[2].position.x = -dist;
		pVertPT[2].position.y = -dist;
		pVertPT[2].position.z = 0;
		pVertPT[2].textureCoord.x = 0.f;
		pVertPT[2].textureCoord.y = 0.f;

		pVertPT[3].position.x = dist;
		pVertPT[3].position.y = -dist;
		pVertPT[3].position.z = 0;
		pVertPT[3].textureCoord.x = 1.f;
		pVertPT[3].textureCoord.y = 0.f;
		break;

		// Should not end up here
	default:
		delete pNewGeometry;
		pNewGeometry = NULL;
		break;
	}

	// Create index data
	pNewGeometry->pIndices[0] = 0;
	pNewGeometry->pIndices[1] = 1;
	pNewGeometry->pIndices[2] = 2;
	pNewGeometry->pIndices[3] = 1;
	pNewGeometry->pIndices[4] = 3;
	pNewGeometry->pIndices[5] = 2;

	return pNewGeometry;
}



//-------------------------------------------------------------------------------------
//
//	CreateCube(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of the quad
//	type			-	type of vertices to use
//	numFaces		-	the number of faces per each axis of a side
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a 2D quad consisting of 2 triangles
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreateCube(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces,
	const glm::vec4 &colour)
{
	// Number of vertices per side of cube
	int faceVerts = (numFaces + 1) * (numFaces + 1);

	// Total vertices
	int totalVerts = faceVerts * 6;		// 6 - total number of sides of a cube

	// Calculate number of indices
	//
	//	numFaces * numFaces = number of faces/cells on a face of cube
	//	6 = number of sides on cube
	//	2 = 2 triangles per side
	//	3 = 3 indices per triangle
	//
	int numIndices = ((numFaces * numFaces * 6) * 2) * 3;

	// Create mesh data
	MeshData *pMeshData = new MeshData(type, totalVerts, numIndices);

	// Step size between vertices
	float incrementDist = size / numFaces;
	int vertexCounter = 0;

	switch(type)
	{
	case eVertexPC:
		{
			SVertexTypePC *pVertexPC = static_cast<SVertexTypePC*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart;
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart;
					pVertexPC[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart;
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart;
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart;
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = (size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart;
					pVertexPC[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}
		}
		break;

	case eVertexPT:
		{
			SVertexTypePT *pVertexPT = static_cast<SVertexTypePT*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart;
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = (float)y / (float)numFaces;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart;
					pVertexPT[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = (float)y / (float)numFaces;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart;
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = (float)y / (float)numFaces;

					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart;
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = (float)y / (float)numFaces;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart;
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = (float)y / (float)numFaces;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = (size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart;
					pVertexPT[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = (float)y / (float)numFaces;
					vertexCounter++;
				}
			}
		}
		break;

	default:
		break;
	}


	// Create the indices
	int indexCounter = 0;
	int vIndex = 0;
	int numVertsX = numFaces + 1;

	// 6 faces in total so loop
	for(int i = 0; i < 6; i++)
	{
		// Loops for generating indices for a face
		for (int y = 0; y < (int)numFaces; y++)
		{
			for (int x = 0; x < (int)numFaces; x++)
			{
				// first triangle
				pMeshData->pIndices[indexCounter++] = vIndex;
				pMeshData->pIndices[indexCounter++] = vIndex + numVertsX + 1;
				pMeshData->pIndices[indexCounter++] = vIndex + numVertsX;
				

				// second triangle
				pMeshData->pIndices[indexCounter++] = vIndex;
				pMeshData->pIndices[indexCounter++] = vIndex + 1;
				pMeshData->pIndices[indexCounter++] = vIndex + numVertsX + 1;
				
				vIndex++;
			}

			vIndex++;
		}

		// Skips the 'bottom' row of vertices
		vIndex += (numFaces + 1);
	}


	return pMeshData;
}