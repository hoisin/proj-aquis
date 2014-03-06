/*
	Date: 04/02/2013
	Author: Matthew Tsang

	Class which handles geometry data generation.
	Can generate primitives as well as load model data from files.
	Its main output is MeshData.

	Note: This class does not store anything. It simply creates MeshData Objects either from
		a file or procedural generation.

	IMPORTANT: All generated MeshData objects MUST be managed by the caller (i.e. deleting it when 
		not used).
		This class is simply a collection of methods and does not store any data.
		Failure to handle returned MeshData pointer will result in memory leaks!
*/

#pragma once
#ifndef __CMESHDATAGENERATOR_H__
#define __CMESHDATAGENERATOR_H__

#include <map>
#include "GfxDefs.h"

class CMeshDataGenerator
{
public:
	CMeshDataGenerator(void);
	~CMeshDataGenerator(void);

	/*
		-----------------------Primitive geometry generation methods-----------------------
	*/


	/*                     REVIEW PLS			*/
	// Creates triangle of specified colour (mainly used for debugging)
	MeshData* CreateTriangle(const std::string& geometryID, float size, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Creates multi-coloured triangle for debugging (Vertex types with colour component only)
	MeshData* CreateTriangleTriColour(const std::string& geometryID, float size, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	/*               EOF REVIEW PLS				*/



	// Creates a cube
	MeshData* CreateCube(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Creates a flat plane
	MeshData* CreatePlane(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Creates a plane with y values using sin
	// TO DO FIX W/E
	MeshData* CreateSinPlane(const std::string& geometryID, float size, float tessellation, EVertexType vertexType,
		const DirectX::XMFLOAT4& colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));
};

#endif