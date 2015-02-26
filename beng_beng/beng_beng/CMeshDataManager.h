//--------------------------------------------------------------------------
//
//	26/02/2015
//
//	Just manages the created mesh data (RAM/CPU data).
//	Include the geometry generator here for now. May make it seperate later.
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CMESHDATAMANAGER_H__
#define __CMESHDATAMANAGER_H__

#include <map>
#include "GfxDefs.h"

class CMeshDataGenerator;

class CMeshDataManager
{
public:
	CMeshDataManager(void);
	~CMeshDataManager(void);

	bool AddMeshData(MeshData* pNewMeshData, const std::string& meshDataID);

	// Procedurally generated mesh data
	// Implemented when needed
	bool CreateTriangle() {}
	bool CreateQuad() {}
	bool CreatePlane() {}
	bool CreateCube() {}
	bool CreateSphere(const std::string& geometryID, float size, EVertexType type, unsigned int subDivisions = 1,
		const glm::vec4& colour = glm::vec4(0, 0, 0, 0));

	MeshData* GetMeshData(const std::string& meshDataID);
	bool RemoveMeshData(const std::string& meshDataID);

	void CleanUp(void);

protected:
	CMeshDataGenerator* m_pMeshDataGenerator;
	std::map<std::string, MeshData*> m_mpMeshData;
};




#endif