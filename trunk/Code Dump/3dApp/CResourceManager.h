/*
	Resource manager for graphics component

*/


#ifndef __CRESOURCEMANAGER_H__
#define __CRESOURCEMANAGER_H__

#include "CBufferManager.h"
#include "CMeshDataManager.h"
#include "CShaderTextureManager.h"

#include <string>

class CResourceManager
{
public:
	CResourceManager(void);
	~CResourceManager(void);

	int Initialise(void);

	/* Mesh data creation methods */
	int LoadMeshData(const std::string& meshDataID, const std::string &fileName);
	int CreateCubeMeshData(const std::string& meshDataID, int size);

	/* D3D mesh data creation methods */
	int CreateModel(const std::string& modelID, const std::string meshDataID);

	/* Load Shader Textures */
	int LoadShaderTexture(const std::string& textureID, const std::string& fileName);

	/* Load shaders */

	/* Managers */
	CMeshDataManager* GetMeshDataManager(void);
	CBufferManager* GetBufferManager(void);
	CShaderTextureManager* GetShaderTextureManager(void);

	void ShutDown(void);

protected:
	CMeshDataManager* m_pMeshDataManager;
	CBufferManager* m_pBufferManager;
	CShaderTextureManager* m_pShaderTextureManager;
};

#endif