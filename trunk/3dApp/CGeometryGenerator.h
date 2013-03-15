/*
	Date: 04/02/2013
	Class which handles geometry data generation.
	Can generate primitives as well as load model data from files.
	Its main output is MeshData.

	Note: All create functions will return a pointer to the newly created geometry data and	
		will store the data in a map. This class handles the creation of geometry data as well as the
		deletion.
*/

#pragma once
#ifndef __CGEOMETRYGENERATOR_H__
#define __CGEOMETRYGENERATOR_H__

#include <map>
#include "GfxDefs.h"

class CGeometryGenerator
{
protected:
	std::map<std::string, MeshData*> m_mGeometry;	

public:
	CGeometryGenerator(void);
	~CGeometryGenerator(void);

	void ShutDown(void);

	/*
		-----------------------Primitive geometry generation methods-----------------------
	*/

	// Creates triangle of specified colour (mainly used for debugging)
	MeshData* CreateTriangle(const std::string& geometryID, float size, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Creates multi-coloured triangle for debugging (Vertex types with colour component only)
	MeshData* CreateTriangleTriColour(const std::string& geometryID, float size, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Creates a cube
	MeshData* CreateCube(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Creates a flat plane
	MeshData* CreatePlane(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Creates a plane with y values using sin
	MeshData* CreateSinPlane(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));
};

#endif