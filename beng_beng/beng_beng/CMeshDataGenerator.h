//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Generates mesh data from procedural generation or loaded from file
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------


#ifndef __CMESHDATAGENERATOR_H__
#define __CMESHDATAGENERATOR_H__


#include "GfxDefs.h"


class CMeshDataGenerator
{
public:
	CMeshDataGenerator();
	~CMeshDataGenerator();
	
	// Creates a single triangle
	MeshData* CreateTriangle(const std::string &geometryID, float size, EVertexType type,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	MeshData* CreateQuad(const std::string &geometryID, float size, EVertexType type, 
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	MeshData* CreateCube(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces = 1,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));
};


#endif