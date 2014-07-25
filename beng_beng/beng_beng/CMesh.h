//--------------------------------------------------------------------------
//
//	21/07/2014
//
//	Mesh class representing a whole model consisting of sub-meshes
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CMESH_H__
#define __CMESH_H__

#include <vector>
#include <glm\glm.hpp>

class CModelMesh;		// to be changed to CSubMesh

class CMesh
{
public:
	CMesh(void);
	~CMesh(void);

protected:
	std::vector<CModelMesh *> m_vpSubMeshes;

	glm::vec3 pos;
};


#endif