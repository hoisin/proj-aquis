#include "CGeometryGenerator.h"

CGeometryGenerator::CGeometryGenerator(void)
{
}


CGeometryGenerator::~CGeometryGenerator(void)
{
	ShutDown();
}


void CGeometryGenerator::ShutDown(void)
{
	// Release stored geometry
	for(std::map<std::string, MeshData*>::iterator ita = m_mGeometry.begin();
		ita != m_mGeometry.end(); ita++)
	{
		delete ita->second;
		ita->second = NULL;
	}

	// Clear elements
	m_mGeometry.clear();
}


MeshData* CGeometryGenerator::CreateTriangle(const std::string& geometryID, float size, EVertexType vertexType,
	const DirectX::XMFLOAT4& colour)
{
	// Create mesh data
	MeshData* pNewGeometry = new MeshData(vertexType, 3, 3);

	// Distance of each vertex from origin (0,0,0)
	float dist = size / 2;

	// Calculate vertex data
	switch(vertexType)
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

		SVertexTypePC* pVertexPC = NULL;

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

		SVertexTypePT* pVertexPT = NULL;

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

		SVertexTypePNC* pVert = NULL;

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

		SVertexTypePNT* pVertexPNT = NULL;

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

	// Add new geometry to map
	m_mGeometry.insert(std::pair<std::string, MeshData*>(geometryID, pNewGeometry));

	// Return reference to newly created geometry
	return pNewGeometry;
}


MeshData* CGeometryGenerator::CreateTriangleTriColour(const std::string& geometryID, float size, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour)
{
	// Create mesh data
	MeshData* pNewGeometry = new MeshData(vertexType, 3, 3);

	// Distance of each vertex from origin (0,0,0)
	float dist = size / 2;

	// Calculate vertex data
	switch(vertexType)
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

		SVertexTypePC* pVertexPC = NULL;

		// Top vertex
		pVertexPC = static_cast<SVertexTypePC*>(pNewGeometry->pVertices);
		pVertexPC[0].position.x = 0;
		pVertexPC[0].position.y = dist;
		pVertexPC[0].position.z = 0;
		pVertexPC[0].colour.x = 1.f;
		pVertexPC[0].colour.y = 0.f;
		pVertexPC[0].colour.z = 0.f;
		pVertexPC[0].colour.w = 1.f;

		// Bottom left vertex
		pVertexPC[1].position.x = -dist;
		pVertexPC[1].position.y = -dist;
		pVertexPC[1].position.z = 0;
		pVertexPC[1].colour.x = 0.f;
		pVertexPC[1].colour.y = 1.f;
		pVertexPC[1].colour.z = 0.f;
		pVertexPC[1].colour.w = 1.f;

		// Bottom right vertex
		pVertexPC[2].position.x = dist;
		pVertexPC[2].position.y = -dist;
		pVertexPC[2].position.z = 0;
		pVertexPC[2].colour.x = 0.f;
		pVertexPC[2].colour.y = 0.f;
		pVertexPC[2].colour.z = 1.f;
		pVertexPC[2].colour.w = 1.f;
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

		SVertexTypePNC* pVertexPNC = NULL;

		// Top vertex
		pVertexPNC = static_cast<SVertexTypePNC*>(pNewGeometry->pVertices);
		pVertexPNC[0].position.x = 0;
		pVertexPNC[0].position.y = dist;
		pVertexPNC[0].position.z = 0;
		pVertexPNC[0].normal.x = 0;
		pVertexPNC[0].normal.y = 0;
		pVertexPNC[0].normal.z = -1;
		pVertexPNC[0].colour.x = colour.x;
		pVertexPNC[0].colour.y = colour.y;
		pVertexPNC[0].colour.y = colour.z;
		pVertexPNC[0].colour.w = colour.w;

		// Bottom left vertex
		pVertexPNC[1].position.x = -dist;
		pVertexPNC[1].position.y = -dist;
		pVertexPNC[1].position.z = 0;
		pVertexPNC[1].normal.x = 0;
		pVertexPNC[1].normal.y = 0;
		pVertexPNC[1].normal.z = -1;
		pVertexPNC[1].colour.x = colour.x;
		pVertexPNC[1].colour.y = colour.y;
		pVertexPNC[1].colour.y = colour.z;
		pVertexPNC[1].colour.w = colour.w;

		// Bottom right vertex
		pVertexPNC[2].position.x = dist;
		pVertexPNC[2].position.y = -dist;
		pVertexPNC[2].position.z = 0;
		pVertexPNC[2].normal.x = 0;
		pVertexPNC[2].normal.y = 0;
		pVertexPNC[2].normal.z = -1;
		pVertexPNC[2].colour.x = colour.x;
		pVertexPNC[2].colour.y = colour.y;
		pVertexPNC[2].colour.y = colour.z;
		pVertexPNC[2].colour.w = colour.w;
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

	// Add new geometry to map
	m_mGeometry.insert(std::pair<std::string, MeshData*>(geometryID, pNewGeometry));

	// Return reference to newly created geometry
	return pNewGeometry;
}


MeshData* CGeometryGenerator::CreateCube(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
	const DirectX::XMFLOAT4& colour)
{
	// Number of vertices on one side of the cube
	int faceVerts = (tessellation + 1) * (tessellation + 1);

	// Total number of vertices of the cube
	int totalVerts = faceVerts * 6;

	/*
		m_tessellation * m_tessellation = number of faces / cells on a face of cube
		6 = number of faces on cube
		2 = 2 triangles per face
		3 = 3 indices per triangle
	*/
	int numIndices = ((tessellation * tessellation * 6) * 2) * 3;

	// Create new mesh data
	MeshData* pMeshData = new MeshData(vertexType, totalVerts, numIndices);

	// Calc space inbetween vertices (same for x and y directions)
	float incrementDist = size / tessellation;
	int vertexCounter = 0;

	switch(vertexType)
	{
	case eVertexPC:
		// Cube generated of length size centred at (0,0,0)
		// ------------- Begin Cube Generation -------------

		// ---Vertex/Index Generation---

		SVertexTypePC* pVertexPC = static_cast<SVertexTypePC*>(pMeshData->pVertices);

		// Front face
		for(int y = 0; y < (tessellation + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = size / 2;
			float zStart = -(size / 2);

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
				pVertexPC[vertexCounter].position.z = zStart;
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}

		// bottom face
		for(int y = 0; y < (tessellation + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = -(size / 2);
			float zStart = -(size / 2);

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertexPC[vertexCounter].position.y = yStart;
				pVertexPC[vertexCounter].position.z = zStart + (y * incrementDist);
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}

		// Left face
		for(int y = 0; y < (tessellation + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = size / 2;
			float zStart = size / 2;

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart;
				pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
				pVertexPC[vertexCounter].position.z = zStart - (x * incrementDist);
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}

		// Back face
		for(int y = 0; y < (tessellation + 1); y++)
		{
			float xStart = size / 2;
			float yStart = size / 2;
			float zStart = size / 2;

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart - (x * incrementDist);
				pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
				pVertexPC[vertexCounter].position.z = zStart;
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}

		// Right face
		for(int y = 0; y < (tessellation + 1); y++)
		{
			float xStart = size / 2;
			float yStart = size / 2;
			float zStart = -(size / 2);

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart;
				pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
				pVertexPC[vertexCounter].position.z = zStart + (x * incrementDist);
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}

		// Top face
		for(int y = 0; y < (tessellation + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = size / 2;
			float zStart = (size / 2);

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertexPC[vertexCounter].position.y = yStart;
				pVertexPC[vertexCounter].position.z = zStart - (y * incrementDist);
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}
		break;

		case eVertexPT:
			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePT* pVertPT = static_cast<SVertexTypePT*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertPT[vertexCounter].position.z = zStart;
					pVertPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation ;
					pVertPT[vertexCounter].textureCoord.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertPT[vertexCounter].position.y = yStart;
					pVertPT[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation ;
					pVertPT[vertexCounter].textureCoord.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPT[vertexCounter].position.x = xStart;
					pVertPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertPT[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation ;
					pVertPT[vertexCounter].textureCoord.y = (float)y / (float)tessellation ;


					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPT[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertPT[vertexCounter].position.z = zStart;
					pVertPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation ;
					pVertPT[vertexCounter].textureCoord.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPT[vertexCounter].position.x = xStart;
					pVertPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertPT[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation ;
					pVertPT[vertexCounter].textureCoord.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = (size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertPT[vertexCounter].position.y = yStart;
					pVertPT[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation;
					pVertPT[vertexCounter].textureCoord.y = (float)y / (float)tessellation;

					vertexCounter++;
				}
			}
			break;

			case eVertexPNC:
				// Cube generated of length size centred at (0,0,0)
				// ------------- Begin Cube Generation -------------

				// ---Vertex/Index Generation---

				// Variable for retrieving vertex data
				SVertexTypePNC* pVertexPNC = static_cast<SVertexTypePNC*>(pMeshData->pVertices);

				// Front face
				for(int y = 0; y < (tessellation + 1); y++)
				{
					float xStart = -(size / 2);
					float yStart = size / 2;
					float zStart = -(size / 2);

					for(int x = 0; x < (tessellation + 1); x++)
					{
						pVertexPNC[vertexCounter].position.x = xStart + (x * incrementDist);
						pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
						pVertexPNC[vertexCounter].position.z = zStart;
						pVertexPNC[vertexCounter].normal.x = 0.0f;
						pVertexPNC[vertexCounter].normal.y = 0.0f;
						pVertexPNC[vertexCounter].normal.z = -1.0f;
						pVertexPNC[vertexCounter].colour.x = colour.x;
						pVertexPNC[vertexCounter].colour.y = colour.y;
						pVertexPNC[vertexCounter].colour.z = colour.z;
						pVertexPNC[vertexCounter].colour.w = colour.w;

						vertexCounter++;
					}
				}

				// bottom face
				for(int y = 0; y < (tessellation + 1); y++)
				{
					float xStart = -(size / 2);
					float yStart = -(size / 2);
					float zStart = -(size / 2);

					for(int x = 0; x < (tessellation + 1); x++)
					{
						pVertexPNC[vertexCounter].position.x = xStart + (x * incrementDist);
						pVertexPNC[vertexCounter].position.y = yStart;
						pVertexPNC[vertexCounter].position.z = zStart + (y * incrementDist);
						pVertexPNC[vertexCounter].normal.x = 0.0f;
						pVertexPNC[vertexCounter].normal.y = -1.0f;
						pVertexPNC[vertexCounter].normal.z = 0.0f;
						pVertexPNC[vertexCounter].colour.x = colour.x;
						pVertexPNC[vertexCounter].colour.y = colour.y;
						pVertexPNC[vertexCounter].colour.z = colour.z;
						pVertexPNC[vertexCounter].colour.w = colour.w;

						vertexCounter++;
					}
				}

				// Left face
				for(int y = 0; y < (tessellation + 1); y++)
				{
					float xStart = -(size / 2);
					float yStart = size / 2;
					float zStart = size / 2;

					for(int x = 0; x < (tessellation + 1); x++)
					{
						pVertexPNC[vertexCounter].position.x = xStart;
						pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
						pVertexPNC[vertexCounter].position.z = zStart - (x * incrementDist);
						pVertexPNC[vertexCounter].normal.x = -1.0f;
						pVertexPNC[vertexCounter].normal.y = 0.0f;
						pVertexPNC[vertexCounter].normal.z = 0.0f;
						pVertexPNC[vertexCounter].colour.x = colour.x;
						pVertexPNC[vertexCounter].colour.y = colour.y;
						pVertexPNC[vertexCounter].colour.z = colour.z;
						pVertexPNC[vertexCounter].colour.w = colour.w;

						vertexCounter++;
					}
				}

				// Back face
				for(int y = 0; y < (tessellation + 1); y++)
				{
					float xStart = size / 2;
					float yStart = size / 2;
					float zStart = size / 2;

					for(int x = 0; x < (tessellation + 1); x++)
					{
						pVertexPNC[vertexCounter].position.x = xStart - (x * incrementDist);
						pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
						pVertexPNC[vertexCounter].position.z = zStart;
						pVertexPNC[vertexCounter].normal.x = 0.0f;
						pVertexPNC[vertexCounter].normal.y = 0.0f;
						pVertexPNC[vertexCounter].normal.z = 1.0f;
						pVertexPNC[vertexCounter].colour.x = colour.x;
						pVertexPNC[vertexCounter].colour.y = colour.y;
						pVertexPNC[vertexCounter].colour.z = colour.z;
						pVertexPNC[vertexCounter].colour.w = colour.w;

						vertexCounter++;
					}
				}

				// Right face
				for(int y = 0; y < (tessellation + 1); y++)
				{
					float xStart = size / 2;
					float yStart = size / 2;
					float zStart = -(size / 2);

					for(int x = 0; x < (tessellation + 1); x++)
					{
						pVertexPNC[vertexCounter].position.x = xStart;
						pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
						pVertexPNC[vertexCounter].position.z = zStart + (x * incrementDist);
						pVertexPNC[vertexCounter].normal.x = 1.0f;
						pVertexPNC[vertexCounter].normal.y = 0.0f;
						pVertexPNC[vertexCounter].normal.z = 0.0f;
						pVertexPNC[vertexCounter].colour.x = colour.x;
						pVertexPNC[vertexCounter].colour.y = colour.y;
						pVertexPNC[vertexCounter].colour.z = colour.z;
						pVertexPNC[vertexCounter].colour.w = colour.w;

						vertexCounter++;
					}
				}

				// Top face
				for(int y = 0; y < (tessellation + 1); y++)
				{
					float xStart = -(size / 2);
					float yStart = size / 2;
					float zStart = (size / 2);

					for(int x = 0; x < (tessellation + 1); x++)
					{
						pVertexPNC[vertexCounter].position.x = xStart + (x * incrementDist);
						pVertexPNC[vertexCounter].position.y = yStart;
						pVertexPNC[vertexCounter].position.z = zStart - (y * incrementDist);
						pVertexPNC[vertexCounter].normal.x = 0.0f;
						pVertexPNC[vertexCounter].normal.y = 1.0f;
						pVertexPNC[vertexCounter].normal.z = 0.0f;
						pVertexPNC[vertexCounter].colour.x = colour.x;
						pVertexPNC[vertexCounter].colour.y = colour.y;
						pVertexPNC[vertexCounter].colour.z = colour.z;
						pVertexPNC[vertexCounter].colour.w = colour.w;

						vertexCounter++;
					}
				}
				break;

		case eVertexPNT:
			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			SVertexTypePNT* pVertexPNT = static_cast<SVertexTypePNT*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart;
					pVertexPNT[vertexCounter].normal.x = 0.0f;
					pVertexPNT[vertexCounter].normal.y = 0.0f;
					pVertexPNT[vertexCounter].normal.z = -1.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart;
					pVertexPNT[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertexPNT[vertexCounter].normal.x = 0.0f;
					pVertexPNT[vertexCounter].normal.y = -1.0f;
					pVertexPNT[vertexCounter].normal.z = 0.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart;
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertexPNT[vertexCounter].normal.x = -1.0f;
					pVertexPNT[vertexCounter].normal.y = 0.0f;
					pVertexPNT[vertexCounter].normal.z = 0.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)y / (float)tessellation ;


					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart;
					pVertexPNT[vertexCounter].normal.x = 0.0f;
					pVertexPNT[vertexCounter].normal.y = 0.0f;
					pVertexPNT[vertexCounter].normal.z = 1.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart;
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertexPNT[vertexCounter].normal.x = 1.0f;
					pVertexPNT[vertexCounter].normal.y = 0.0f;
					pVertexPNT[vertexCounter].normal.z = 0.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = (size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart;
					pVertexPNT[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertexPNT[vertexCounter].normal.x = 0.0f;
					pVertexPNT[vertexCounter].normal.y = 1.0f;
					pVertexPNT[vertexCounter].normal.z = 0.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)y / (float)tessellation ;

					vertexCounter++;
				}
			}
			break;

		default:
			delete pMeshData;
			pMeshData = NULL;
			break;
	}

	int indexCounter = 0;
	int vIndex = 0;
	int numVertsX = tessellation + 1;

	// 6 faces in total so loop
	for(int i = 0; i < 6; i++)
	{
		// Loops for generating indices for a face
		for (int y = 0; y < tessellation; y++)
		{
			for (int x = 0; x < tessellation; x++)
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
		vIndex += (tessellation + 1);
	}

	m_mGeometry.insert(std::pair<std::string, MeshData*>("geometryID", pMeshData));

	return pMeshData;
}



MeshData* CGeometryGenerator::CreatePlane(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour)
{
	// Total number of vertices of the cube
	int totalVerts = (tessellation + 1) * (tessellation + 1);

	/*
		m_tessellation * m_tessellation = number of faces / cells on a face of cube
		2 = 2 triangles per face
		3 = 3 indices per triangle
	*/
	int numIndices = ((tessellation * tessellation) * 2) * 3;

	// Create new mesh data
	MeshData* pMeshData = new MeshData(vertexType, totalVerts, numIndices);

	// Calc space inbetween vertices (same for x and y directions)
	float incrementDist = size / tessellation;
	int vertexCounter = 0;

	switch(vertexType)
	{
	case eVertexPC:
		// Plane generated of length size centred at (0,0,0)
		// ------------- Begin Cube Generation -------------

		// ---Vertex/Index Generation---

		SVertexTypePC* pVertexPC = static_cast<SVertexTypePC*>(pMeshData->pVertices);

		// Plane
		for(int z = 0; z < (tessellation + 1); z++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = size / 2;

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertexPC[vertexCounter].position.y = yStart;
				pVertexPC[vertexCounter].position.z = zStart - (z * incrementDist);
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}
		break;

		case eVertexPT:
			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePT* pVertexPT = static_cast<SVertexTypePT*>(pMeshData->pVertices);

			// Front face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart;
					pVertexPT[vertexCounter].position.z = zStart - (z * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation ;
					pVertexPT[vertexCounter].textureCoord.y = (float)z / (float)tessellation ;

					vertexCounter++;
				}
			}
			break;

		case eVertexPNC:
			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePNC* pVertexPNC = static_cast<SVertexTypePNC*>(pMeshData->pVertices);

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNC[vertexCounter].position.y = yStart;
					pVertexPNC[vertexCounter].position.z = zStart - (z * incrementDist);
					pVertexPNC[vertexCounter].normal.x = 0.0f;
					pVertexPNC[vertexCounter].normal.y = 1.0f;
					pVertexPNC[vertexCounter].normal.z = 0.0f;
					pVertexPNC[vertexCounter].colour.x = colour.x;
					pVertexPNC[vertexCounter].colour.y = colour.y;
					pVertexPNC[vertexCounter].colour.z = colour.z;
					pVertexPNC[vertexCounter].colour.w = colour.w;

					vertexCounter++;
				}
			}
			break;

		case eVertexPNT:
			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			SVertexTypePNT* pVertexPNT = static_cast<SVertexTypePNT*>(pMeshData->pVertices);

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart;
					pVertexPNT[vertexCounter].position.z = zStart - (z * incrementDist);
					pVertexPNT[vertexCounter].normal.x = 0.0f;
					pVertexPNT[vertexCounter].normal.y = 1.0f;
					pVertexPNT[vertexCounter].normal.z = 0.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)z / (float)tessellation ;

					vertexCounter++;
				}
			}
			break;

		default:
			break;
	}

	int indexCounter = 0;
	int vIndex = 0;
	int numVertsX = tessellation + 1;

	// Loops for generating indices for a face
	for (int z = 0; z < tessellation; z++)
	{
		for (int x = 0; x < tessellation; x++)
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

	m_mGeometry.insert(std::pair<std::string, MeshData*>("geometryID", pMeshData));

	return pMeshData;
}



MeshData* CGeometryGenerator::CreateSinPlane(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour)
{
	// Total number of vertices of the cube
	int totalVerts = (tessellation + 1) * (tessellation + 1);

	/*
		m_tessellation * m_tessellation = number of faces / cells on a face of cube
		2 = 2 triangles per face
		3 = 3 indices per triangle
	*/
	int numIndices = ((tessellation * tessellation) * 2) * 3;

	// Create new mesh data
	MeshData* pMeshData = new MeshData(vertexType, totalVerts, numIndices);

	// Calc space inbetween vertices (same for x and y directions)
	float incrementDist = size / tessellation;
	int vertexCounter = 0;

	switch(vertexType)
	{
	case eVertexPC:
		// Plane generated of length size centred at (0,0,0)
		// ------------- Begin Cube Generation -------------

		// ---Vertex/Index Generation---
		SVertexTypePC* pVertexPC = static_cast<SVertexTypePC*>(pMeshData->pVertices);

		// Plane
		for(int z = 0; z < (tessellation + 1); z++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = size / 2;

			for(int x = 0; x < (tessellation + 1); x++)
			{
				pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertexPC[vertexCounter].position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
				pVertexPC[vertexCounter].position.z = zStart - (z * incrementDist);
				pVertexPC[vertexCounter].colour.x = colour.x;
				pVertexPC[vertexCounter].colour.y = colour.y;
				pVertexPC[vertexCounter].colour.z = colour.z;
				pVertexPC[vertexCounter].colour.w = colour.w;

				vertexCounter++;
			}
		}
		break;

		case eVertexPT:
			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePT* pVertexPT = static_cast<SVertexTypePT*>(pMeshData->pVertices);

			// Front face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
					//pVertexPT[vertexCounter].position.y = yStart + ((sin((double)(x%360)*0.0174532925f)) + (sin((double)(z%360)*0.0174532925f)) * 10);
					pVertexPT[vertexCounter].position.z = zStart - (z * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)tessellation ;
					pVertexPT[vertexCounter].textureCoord.y = (float)z / (float)tessellation ;

					vertexCounter++;
				}
			}
			break;

		case eVertexPNC:
			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePNC* pVertPNC = static_cast<SVertexTypePNC*>(pMeshData->pVertices);

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPNC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertPNC[vertexCounter].position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
					pVertPNC[vertexCounter].position.z = zStart - (z * incrementDist);
					pVertPNC[vertexCounter].normal.x = 0.0f;
					pVertPNC[vertexCounter].normal.y = 1.0f;
					pVertPNC[vertexCounter].normal.z = 0.0f;
					pVertPNC[vertexCounter].colour.x = colour.x;
					pVertPNC[vertexCounter].colour.y = colour.y;
					pVertPNC[vertexCounter].colour.z = colour.z;
					pVertPNC[vertexCounter].colour.w = colour.w;

					vertexCounter++;
				}
			}
			break;

		case eVertexPNT:
			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---
			SVertexTypePNT* pVertexPNT = static_cast<SVertexTypePNT*>(pMeshData->pVertices);

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
					pVertexPNT[vertexCounter].position.z = zStart - (z * incrementDist);
					pVertexPNT[vertexCounter].normal.x = 0.0f;
					pVertexPNT[vertexCounter].normal.y = 1.0f;
					pVertexPNT[vertexCounter].normal.z = 0.0f;
					pVertexPNT[vertexCounter].texture.x = (float)x / (float)tessellation ;
					pVertexPNT[vertexCounter].texture.y = (float)z / (float)tessellation ;

					vertexCounter++;
				}
			}
			break;

		default:
			break;
	}

	int indexCounter = 0;
	int vIndex = 0;
	int numVertsX = tessellation + 1;

	// Loops for generating indices for a face
	for (int z = 0; z < tessellation; z++)
	{
		for (int x = 0; x < tessellation; x++)
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

	m_mGeometry.insert(std::pair<std::string, MeshData*>("geometryID", pMeshData));

	return pMeshData;
}