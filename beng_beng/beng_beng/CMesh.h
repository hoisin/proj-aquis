//--------------------------------------------------------------------------
//
//	21/07/2014
//
//	Mesh class representing a whole model consisting of sub-meshes
//	All sub-meshes should be positioned correctly in its local space.
//	e.g. A simple car model can contain as sub-meshes:
//		- the chassis
//		- 4 individual wheels
//	These will be positioned correctly in local space so when transformed,
//		they will be properly placed in world space.
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CMESH_H__
#define __CMESH_H__

#include <vector>
#include <glm\glm.hpp>

class CSubMesh;		// to be changed to CSubMesh

class CMesh
{
public:
	CMesh(void);
	~CMesh(void);

	void AddSubMesh(CSubMesh* pSubMesh);

	CSubMesh* GetSubMesh(unsigned int index);
	unsigned int GetSubMeshCount();

	void SetPos(const glm::vec3& newPos);
	glm::vec3 GetPos(void) const;

	void CleanUp(void);

protected:
	std::vector<CSubMesh *> m_vpSubMeshes;

	glm::vec3 m_pos;
};


#endif