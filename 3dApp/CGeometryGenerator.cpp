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
	MeshData* pNewGeometry = new MeshData;

	// Distance of each vertex from origin (0,0,0)
	float dist = size / 2;

	// Calculate vertex data
	switch(vertexType)
	{
	case eVertexPC:
		// Allocate/calculate data
		for(int i = 0; i < 3; i++)
			pNewGeometry->m_pvVertices.push_back(new SVertexTypePC);

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
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->position.x = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->position.y = dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->position.z = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.x = colour.x;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.y = colour.y;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.z = colour.z;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.w = colour.w;

		// Bottom left vertex
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->position.x = -dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->position.y = -dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->position.z = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.x = colour.x;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.y = colour.y;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.z = colour.z;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.w = colour.w;

		// Bottom right vertex
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->position.x = dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->position.y = -dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->position.z = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.x = colour.x;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.y = colour.y;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.z = colour.z;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.w = colour.w;
		break;

	case eVertexPT:
		// Allocate/calculate data
		for(int i = 0; i < 3; i++)
			pNewGeometry->m_pvVertices.push_back(new SVertexTypePT);

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
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->position.x = 0;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[0]))->position.y = dist;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[0]))->position.z = 0;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[0]))->textureCoord.x = 0;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[0]))->textureCoord.y = 0.5;

		// Bottom left vertex
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[1]))->position.x = -dist;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[1]))->position.y = -dist;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[1]))->position.z = 0;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[1]))->textureCoord.x = 0;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[1]))->textureCoord.y = 1;

		// Bottom right vertex
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[2]))->position.x = dist;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[2]))->position.y = -dist;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[2]))->position.z = 0;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[2]))->textureCoord.x = 1;
		((SVertexTypePT*)(pNewGeometry->m_pvVertices[2]))->textureCoord.y = 1;
		break;

	case eVertexPNC:
		// Allocate/calculate data
		for(int i = 0; i < 3; i++)
			pNewGeometry->m_pvVertices.push_back(new SVertexTypePNC);

		// Variable for retrieving vertex data
		SVertexTypePNC* pVert;

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
		pVert = (SVertexTypePNC*)(pNewGeometry->m_pvVertices[0]);
		pVert->position.x = 0;
		pVert->position.y = dist;
		pVert->position.z = 0;
		pVert->normal.x = 0;
		pVert->normal.y = 0;
		pVert->normal.z = -1;
		pVert->colour.x = colour.x;
		pVert->colour.y = colour.y;
		pVert->colour.y = colour.z;
		pVert->colour.w = colour.w;

		// Bottom left vertex
		pVert = (SVertexTypePNC*)(pNewGeometry->m_pvVertices[1]);
		pVert->position.x = -dist;
		pVert->position.y = -dist;
		pVert->position.z = 0;
		pVert->normal.x = 0;
		pVert->normal.y = 0;
		pVert->normal.z = -1;
		pVert->colour.x = colour.x;
		pVert->colour.y = colour.y;
		pVert->colour.y = colour.z;
		pVert->colour.w = colour.w;

		// Bottom right vertex
		pVert = (SVertexTypePNC*)(pNewGeometry->m_pvVertices[2]);
		pVert->position.x = dist;
		pVert->position.y = -dist;
		pVert->position.z = 0;
		pVert->normal.x = 0;
		pVert->normal.y = 0;
		pVert->normal.z = -1;
		pVert->colour.x = colour.x;
		pVert->colour.y = colour.y;
		pVert->colour.y = colour.z;
		pVert->colour.w = colour.w;
		break;

	case eVertexPNT:
		// Allocate/calculate data
		for(int i = 0; i < 3; i++)
			pNewGeometry->m_pvVertices.push_back(new SVertexTypePNT);

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
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->position.x = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->position.y = dist;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->position.z = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->normal.x = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->normal.y = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->normal.z = -1;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->texture.x = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[0]))->texture.y = 0.5;

		// Bottom left vertex
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->position.x = -dist;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->position.y = -dist;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->position.z = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->normal.x = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->normal.y = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->normal.z = -1;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->texture.x = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[1]))->texture.y = 1;

		// Bottom right vertex
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->position.x = dist;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->position.y = -dist;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->position.z = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->normal.x = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->normal.y = 0;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->normal.z = -1;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->texture.x = 1;
		((SVertexTypePNT*)(pNewGeometry->m_pvVertices[2]))->texture.y = 1;
		break;

	// shouldn't end up here
	default:
		delete pNewGeometry;
		pNewGeometry = NULL;
		break;
	}

	// Add indices
	pNewGeometry->m_indices.push_back(0);
	pNewGeometry->m_indices.push_back(2);
	pNewGeometry->m_indices.push_back(1);

	// Set vertex type
	pNewGeometry->m_vertexType = vertexType;

	// Add new geometry to map
	m_mGeometry.insert(std::pair<std::string, MeshData*>(geometryID, pNewGeometry));

	// Return reference to newly created geometry
	return pNewGeometry;
}


MeshData* CGeometryGenerator::CreateTriangleTriColour(const std::string& geometryID, float size, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour)
{
	// Create mesh data
	MeshData* pNewGeometry = new MeshData;

	// Distance of each vertex from origin (0,0,0)
	float dist = size / 2;

	// Calculate vertex data
	switch(vertexType)
	{
	case eVertexPC:
		// Allocate/calculate data
		for(int i = 0; i < 3; i++)
			pNewGeometry->m_pvVertices.push_back(new SVertexTypePC);

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
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->position.x = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->position.y = dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->position.z = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.x = 1.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.y = 0.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.z = 0.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[0]))->colour.w = 1.f;

		// Bottom left vertex
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->position.x = -dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->position.y = -dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->position.z = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.x = 0.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.y = 1.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.z = 0.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[1]))->colour.w = 1.f;

		// Bottom right vertex
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->position.x = dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->position.y = -dist;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->position.z = 0;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.x = 0.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.y = 0.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.z = 1.f;
		((SVertexTypePC*)(pNewGeometry->m_pvVertices[2]))->colour.w = 1.f;
		break;

	case eVertexPNC:
		// Allocate/calculate data
		for(int i = 0; i < 3; i++)
			pNewGeometry->m_pvVertices.push_back(new SVertexTypePNC);

		// Variable for retrieving vertex data
		SVertexTypePNC* pVert;

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
		pVert = (SVertexTypePNC*)(pNewGeometry->m_pvVertices[0]);
		pVert->position.x = 0;
		pVert->position.y = dist;
		pVert->position.z = 0;
		pVert->normal.x = 0;
		pVert->normal.y = 0;
		pVert->normal.z = -1;
		pVert->colour.x = colour.x;
		pVert->colour.y = colour.y;
		pVert->colour.y = colour.z;
		pVert->colour.w = colour.w;

		// Bottom left vertex
		pVert = (SVertexTypePNC*)(pNewGeometry->m_pvVertices[1]);
		pVert->position.x = -dist;
		pVert->position.y = -dist;
		pVert->position.z = 0;
		pVert->normal.x = 0;
		pVert->normal.y = 0;
		pVert->normal.z = -1;
		pVert->colour.x = colour.x;
		pVert->colour.y = colour.y;
		pVert->colour.y = colour.z;
		pVert->colour.w = colour.w;

		// Bottom right vertex
		pVert = (SVertexTypePNC*)(pNewGeometry->m_pvVertices[2]);
		pVert->position.x = dist;
		pVert->position.y = -dist;
		pVert->position.z = 0;
		pVert->normal.x = 0;
		pVert->normal.y = 0;
		pVert->normal.z = -1;
		pVert->colour.x = colour.x;
		pVert->colour.y = colour.y;
		pVert->colour.y = colour.z;
		pVert->colour.w = colour.w;
		break;

	// shouldn't end up here
	default:
		delete pNewGeometry;
		pNewGeometry = NULL;
		break;
	}

	// Add indices
	pNewGeometry->m_indices.push_back(0);
	pNewGeometry->m_indices.push_back(2);
	pNewGeometry->m_indices.push_back(1);

	// Set vertex type
	pNewGeometry->m_vertexType = vertexType;

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
	MeshData* pMeshData = new MeshData;

	// Pre-allocate indices
	for(int j = 0; j < numIndices; j++)
		pMeshData->m_indices.push_back(0);

	// Calc space inbetween vertices (same for x and y directions)
	float incrementDist = size / tessellation;
	int vertexCoutner = 0;

	switch(vertexType)
	{
	case eVertexPC:
		// Create empty vertices
		for(int i = 0; i < totalVerts; i++)
			pMeshData->m_pvVertices.push_back(new SVertexTypePC);

		// Cube generated of length size centred at (0,0,0)
		// ------------- Begin Cube Generation -------------

		// ---Vertex/Index Generation---

		// Front face
		for(int y = 0; y < (tessellation + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = size / 2;
			float zStart = -(size / 2);

			for(int x = 0; x < (tessellation + 1); x++)
			{
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
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
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart + (y * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
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
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
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
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart - (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
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
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart + (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
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
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (y * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
			}
		}
		break;

		case eVertexPT:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePT);

			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePT* pVertPT;

			// Front face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPT = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPT->position.x = xStart + (x * incrementDist);
					pVertPT->position.y = yStart - (y * incrementDist);
					pVertPT->position.z = zStart;
					pVertPT->textureCoord.x = (float)x / (float)tessellation ;
					pVertPT->textureCoord.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					pVertPT = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPT->position.x = xStart + (x * incrementDist);
					pVertPT->position.y = yStart;
					pVertPT->position.z = zStart + (y * incrementDist);
					pVertPT->textureCoord.x = (float)x / (float)tessellation ;
					pVertPT->textureCoord.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					pVertPT = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPT->position.x = xStart;
					pVertPT->position.y = yStart - (y * incrementDist);
					pVertPT->position.z = zStart - (x * incrementDist);
					pVertPT->textureCoord.x = (float)x / (float)tessellation ;
					pVertPT->textureCoord.y = (float)y / (float)tessellation ;


					vertexCoutner++;
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
					pVertPT = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPT->position.x = xStart - (x * incrementDist);
					pVertPT->position.y = yStart - (y * incrementDist);
					pVertPT->position.z = zStart;
					pVertPT->textureCoord.x = (float)x / (float)tessellation ;
					pVertPT->textureCoord.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					pVertPT = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPT->position.x = xStart;
					pVertPT->position.y = yStart - (y * incrementDist);
					pVertPT->position.z = zStart + (x * incrementDist);
					pVertPT->textureCoord.x = (float)x / (float)tessellation ;
					pVertPT->textureCoord.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					pVertPT = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPT->position.x = xStart + (x * incrementDist);
					pVertPT->position.y = yStart;
					pVertPT->position.z = zStart - (y * incrementDist);
					pVertPT->textureCoord.x = (float)x / (float)tessellation;
					pVertPT->textureCoord.y = (float)y / (float)tessellation;

					vertexCoutner++;
				}
			}
			break;

			case eVertexPNC:
				// Create empty vertices
				for(int i = 0; i < totalVerts; i++)
					pMeshData->m_pvVertices.push_back(new SVertexTypePNC);

				// Cube generated of length size centred at (0,0,0)
				// ------------- Begin Cube Generation -------------

				// ---Vertex/Index Generation---

				// Variable for retrieving vertex data
				SVertexTypePNC* pVertPNC;

				// Front face
				for(int y = 0; y < (tessellation + 1); y++)
				{
					float xStart = -(size / 2);
					float yStart = size / 2;
					float zStart = -(size / 2);

					for(int x = 0; x < (tessellation + 1); x++)
					{
						pVertPNC = (SVertexTypePNC*)pMeshData->m_pvVertices[vertexCoutner];

						pVertPNC->position.x = xStart + (x * incrementDist);
						pVertPNC->position.y = yStart - (y * incrementDist);
						pVertPNC->position.z = zStart;
						pVertPNC->normal.x = 0.0f;
						pVertPNC->normal.y = 0.0f;
						pVertPNC->normal.z = -1.0f;
						pVertPNC->colour.x = colour.x;
						pVertPNC->colour.y = colour.y;
						pVertPNC->colour.z = colour.z;
						pVertPNC->colour.w = colour.w;

						vertexCoutner++;
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
						pVertPNC->position.x = xStart + (x * incrementDist);
						pVertPNC->position.y = yStart;
						pVertPNC->position.z = zStart + (y * incrementDist);
						pVertPNC->normal.x = 0.0f;
						pVertPNC->normal.y = -1.0f;
						pVertPNC->normal.z = 0.0f;
						pVertPNC->colour.x = colour.x;
						pVertPNC->colour.y = colour.y;
						pVertPNC->colour.z = colour.z;
						pVertPNC->colour.w = colour.w;

						vertexCoutner++;
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
						pVertPNC->position.x = xStart;
						pVertPNC->position.y = yStart - (y * incrementDist);
						pVertPNC->position.z = zStart - (x * incrementDist);
						pVertPNC->normal.x = -1.0f;
						pVertPNC->normal.y = 0.0f;
						pVertPNC->normal.z = 0.0f;
						pVertPNC->colour.x = colour.x;
						pVertPNC->colour.y = colour.y;
						pVertPNC->colour.z = colour.z;
						pVertPNC->colour.w = colour.w;

						vertexCoutner++;
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
						pVertPNC->position.x = xStart - (x * incrementDist);
						pVertPNC->position.y = yStart - (y * incrementDist);
						pVertPNC->position.z = zStart;
						pVertPNC->normal.x = 0.0f;
						pVertPNC->normal.y = 0.0f;
						pVertPNC->normal.z = 1.0f;
						pVertPNC->colour.x = colour.x;
						pVertPNC->colour.y = colour.y;
						pVertPNC->colour.z = colour.z;
						pVertPNC->colour.w = colour.w;

						vertexCoutner++;
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
						pVertPNC->position.x = xStart;
						pVertPNC->position.y = yStart - (y * incrementDist);
						pVertPNC->position.z = zStart + (x * incrementDist);
						pVertPNC->normal.x = 1.0f;
						pVertPNC->normal.y = 0.0f;
						pVertPNC->normal.z = 0.0f;
						pVertPNC->colour.x = colour.x;
						pVertPNC->colour.y = colour.y;
						pVertPNC->colour.z = colour.z;
						pVertPNC->colour.w = colour.w;

						vertexCoutner++;
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
						pVertPNC->position.x = xStart + (x * incrementDist);
						pVertPNC->position.y = yStart;
						pVertPNC->position.z = zStart - (y * incrementDist);
						pVertPNC->normal.x = 0.0f;
						pVertPNC->normal.y = 1.0f;
						pVertPNC->normal.z = 0.0f;
						pVertPNC->colour.x = colour.x;
						pVertPNC->colour.y = colour.y;
						pVertPNC->colour.z = colour.z;
						pVertPNC->colour.w = colour.w;

						vertexCoutner++;
					}
				}
				break;

		case eVertexPNT:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePNT);

			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Front face
			for(int y = 0; y < (tessellation + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (tessellation + 1); x++)
				{
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = -1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart + (y * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = -1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = -1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)y / (float)tessellation ;


					vertexCoutner++;
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
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart - (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = 1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart - (y * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart + (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = 1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)y / (float)tessellation ;

					vertexCoutner++;
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
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (y * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = 1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)y / (float)tessellation ;

					vertexCoutner++;
				}
			}
			break;

		default:
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
				pMeshData->m_indices[indexCounter++] = vIndex;
				pMeshData->m_indices[indexCounter++] = vIndex + numVertsX + 1;
				pMeshData->m_indices[indexCounter++] = vIndex + numVertsX;
				

				// second triangle
				pMeshData->m_indices[indexCounter++] = vIndex;
				pMeshData->m_indices[indexCounter++] = vIndex + 1;
				pMeshData->m_indices[indexCounter++] = vIndex + numVertsX + 1;
				
				vIndex++;
			}

			vIndex++;
		}

		// Skips the 'bottom' row of vertices
		vIndex += (tessellation + 1);
	}

	// Set vertex type
	pMeshData->m_vertexType = vertexType;

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
	MeshData* pMeshData = new MeshData;

	// Pre-allocate indices
	for(int j = 0; j < numIndices; j++)
		pMeshData->m_indices.push_back(0);

	// Calc space inbetween vertices (same for x and y directions)
	float incrementDist = size / tessellation;
	int vertexCoutner = 0;

	switch(vertexType)
	{
	case eVertexPC:
		// Create empty vertices
		for(int i = 0; i < totalVerts; i++)
			pMeshData->m_pvVertices.push_back(new SVertexTypePC);

		// Plane generated of length size centred at (0,0,0)
		// ------------- Begin Cube Generation -------------

		// ---Vertex/Index Generation---

		// Plane
		for(int z = 0; z < (tessellation + 1); z++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = size / 2;

			for(int x = 0; x < (tessellation + 1); x++)
			{
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (z * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
			}
		}
		break;

		case eVertexPT:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePT);

			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePT* pVert;

			// Front face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVert = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVert->position.x = xStart + (x * incrementDist);
					pVert->position.y = yStart;
					pVert->position.z = zStart - (z * incrementDist);
					pVert->textureCoord.x = (float)x / (float)tessellation ;
					pVert->textureCoord.y = (float)z / (float)tessellation ;

					vertexCoutner++;
				}
			}
			break;

		case eVertexPNC:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePNC);

			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePNC* pVertPNC;

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPNC = (SVertexTypePNC*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPNC->position.x = xStart + (x * incrementDist);
					pVertPNC->position.y = yStart;
					pVertPNC->position.z = zStart - (z * incrementDist);
					pVertPNC->normal.x = 0.0f;
					pVertPNC->normal.y = 1.0f;
					pVertPNC->normal.z = 0.0f;
					pVertPNC->colour.x = colour.x;
					pVertPNC->colour.y = colour.y;
					pVertPNC->colour.z = colour.z;
					pVertPNC->colour.w = colour.w;

					vertexCoutner++;
				}
			}
			break;

		case eVertexPNT:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePNT);

			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (z * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = 1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)z / (float)tessellation ;

					vertexCoutner++;
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
			pMeshData->m_indices[indexCounter++] = vIndex;
			pMeshData->m_indices[indexCounter++] = vIndex + numVertsX + 1;
			pMeshData->m_indices[indexCounter++] = vIndex + numVertsX;

			// second triangle
			pMeshData->m_indices[indexCounter++] = vIndex;
			pMeshData->m_indices[indexCounter++] = vIndex + 1;
			pMeshData->m_indices[indexCounter++] = vIndex + numVertsX + 1;

			vIndex++;
		}

		vIndex++;
	}

	// Set vertex type
	pMeshData->m_vertexType = vertexType;

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
	MeshData* pMeshData = new MeshData;

	// Pre-allocate indices
	for(int j = 0; j < numIndices; j++)
		pMeshData->m_indices.push_back(0);

	// Calc space inbetween vertices (same for x and y directions)
	float incrementDist = size / tessellation;
	int vertexCoutner = 0;

	switch(vertexType)
	{
	case eVertexPC:
		// Create empty vertices
		for(int i = 0; i < totalVerts; i++)
			pMeshData->m_pvVertices.push_back(new SVertexTypePC);

		// Plane generated of length size centred at (0,0,0)
		// ------------- Begin Cube Generation -------------

		// ---Vertex/Index Generation---

		// Plane
		for(int z = 0; z < (tessellation + 1); z++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = size / 2;

			for(int x = 0; x < (tessellation + 1); x++)
			{
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (z * incrementDist);
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.x = colour.x;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.y = colour.y;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.z = colour.z;
				((SVertexTypePC*)(pMeshData->m_pvVertices[vertexCoutner]))->colour.w = colour.w;

				vertexCoutner++;
			}
		}
		break;

		case eVertexPT:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePT);

			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePT* pVert;

			// Front face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVert = (SVertexTypePT*)pMeshData->m_pvVertices[vertexCoutner];

					pVert->position.x = xStart + (x * incrementDist);
					pVert->position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
					//pVert->position.y = yStart + ((sin((double)(x%360)*0.0174532925f)) + (sin((double)(z%360)*0.0174532925f)) * 10);
					pVert->position.z = zStart - (z * incrementDist);
					pVert->textureCoord.x = (float)x / (float)tessellation ;
					pVert->textureCoord.y = (float)z / (float)tessellation ;

					vertexCoutner++;
				}
			}
			break;

		case eVertexPNC:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePNC);

			// Cube generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// Variable for retrieving vertex data
			SVertexTypePNC* pVertPNC;

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					pVertPNC = (SVertexTypePNC*)pMeshData->m_pvVertices[vertexCoutner];

					pVertPNC->position.x = xStart + (x * incrementDist);
					pVertPNC->position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
					pVertPNC->position.z = zStart - (z * incrementDist);
					pVertPNC->normal.x = 0.0f;
					pVertPNC->normal.y = 1.0f;
					pVertPNC->normal.z = 0.0f;
					pVertPNC->colour.x = colour.x;
					pVertPNC->colour.y = colour.y;
					pVertPNC->colour.z = colour.z;
					pVertPNC->colour.w = colour.w;

					vertexCoutner++;
				}
			}
			break;

		case eVertexPNT:
			// Create empty vertices
			for(int i = 0; i < totalVerts; i++)
				pMeshData->m_pvVertices.push_back(new SVertexTypePNT);

			// Plane generated of length size centred at (0,0,0)
			// ------------- Begin Cube Generation -------------

			// ---Vertex/Index Generation---

			// top face
			for(int z = 0; z < (tessellation + 1); z++)
			{
				float xStart = -(size / 2);
				float yStart = 0;
				float zStart = size / 2;

				for(int x = 0; x < (tessellation + 1); x++)
				{
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.x = xStart + (x * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.y = yStart + (sin((double)(((float)x*(float)z*0.25)*0.0174532925f)) * 10);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->position.z = zStart - (z * incrementDist);
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.x = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.y = 1.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->normal.z = 0.0f;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.x = (float)x / (float)tessellation ;
					((SVertexTypePNT*)(pMeshData->m_pvVertices[vertexCoutner]))->texture.y = (float)z / (float)tessellation ;

					vertexCoutner++;
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
			pMeshData->m_indices[indexCounter++] = vIndex;
			pMeshData->m_indices[indexCounter++] = vIndex + numVertsX + 1;
			pMeshData->m_indices[indexCounter++] = vIndex + numVertsX;

			// second triangle
			pMeshData->m_indices[indexCounter++] = vIndex;
			pMeshData->m_indices[indexCounter++] = vIndex + 1;
			pMeshData->m_indices[indexCounter++] = vIndex + numVertsX + 1;

			vIndex++;
		}

		vIndex++;
	}

	// Set vertex type
	pMeshData->m_vertexType = vertexType;

	m_mGeometry.insert(std::pair<std::string, MeshData*>("geometryID", pMeshData));

	return pMeshData;
}