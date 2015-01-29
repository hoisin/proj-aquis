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

#include <vector>

class CMesh;
class CSubMesh;

class CMeshManager
{
public:	
	CMeshManager(void);
	~CMeshManager(void);



private:
	std::vector<CMesh*> m_vpMeshes;
	std::vector<CSubMesh*> m_vpSubMeshes;

};


#endif