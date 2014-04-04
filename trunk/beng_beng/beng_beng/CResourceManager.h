//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Main interfacing class for accessing/creating resources
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCEMANAGER_H__
#define __CRESOURCEMANAGER_H__

#include <map>
#include <string>
#include <glm.hpp>
#include "IResource.h"
#include "GfxDefs.h"

class CMeshDataGenerator;

class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	bool Initialise();

	// Geometry generation methods
	bool CreateTriangle(const std::string &geometryID, float size, EVertexType type,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	bool CreateVertexBuffer(const std::string &vertexID, MeshData *pData);

	bool CreateShader(const std::string &shaderID, const std::string &vertexShaderFile,
		const std::string &fragShaderFile);

	void ShutDown();

private:
	std::map<std::string, IResource *> m_resourceMap;

	CMeshDataGenerator *m_pMeshGenerator;
};

#endif