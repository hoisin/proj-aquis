//--------------------------------------------------------------------------
//
//	29/01/2015
//
//	Mesh Manager
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CMESHMANAGER_H__
#define __CMESHMANAGER_H__

#include <map>
#include <glm\glm.hpp>

class CMesh;
class CSubMesh;

class CMeshManager
{
public:	
	CMeshManager(void);
	~CMeshManager(void);

	CMesh* CreateMesh(const glm::vec3& pos, const std::string& meshID);
	void AddSubMesh(const std::string& meshID, CSubMesh* pNewSubMesh, const std::string& subMeshID);

	CMesh* GetMesh(const std::string& meshID);
	void RemoveMesh(const std::string& meshID);

	void CleanUp(void);

private:
	std::map<std::string, CMesh*> m_mpMeshes;
};


#endif