//----------------------------------------------------------------------
//
//	Date: 21/02/2014
//	Author: Matthew Tsang
//
//	The resource manager. Creates everything!
//
//	Feel that the Mesh, buffers, texture and shader managers should,
//	be created and managed here (subject to change....)
//  
//----------------------------------------------------------------------


#ifndef __CRESOURCEMANAGER_H__
#define __CRESOURCEMANAGER_H__

#include <string>
#include <map>

#include "IResource.h"

#include "CBufferManager.h"
#include "CMeshDataManager.h"
#include "CShaderTextureManager.h"

class CResourceManager
{
protected:
	//std::map<std::string, IResource*>	m_mMeshData;
	CD3DBase*							m_pD3DBase;
	CMeshDataManager*					m_pMeshDataManager;
	CBufferManager*						m_pBufferManager;
	CShaderTextureManager*				m_pShaderTextureManager;

public:
	// No default c'tor
	CResourceManager(CD3DBase *pD3DBase);
	~CResourceManager(void);

	bool Initialise(void);

	// Procedural generated assets
	MeshData* CreateMeshDataCube(const std::string &cubeID, int size, int tessellation,
		EVertexType type, const DirectX::XMFLOAT4 &colour = DirectX::XMFLOAT4(0, 0, 0, 1.f));

	// Create GPU assets
	bool CreateVertexIndexBuffers(const std::string &vertexID, const std::string &indexID,
		const MeshData *pMeshData, ID3D11Buffer *pOutVertBuf = NULL, ID3D11Buffer *pOutIdxBuf = NULL);

	///* Mesh data creation methods */
	//int LoadMeshData(const std::string& meshDataID, const std::string &fileName);
	//int CreateCubeMeshData(const std::string& meshDataID, int size);

	///* D3D mesh data creation methods */
	//int CreateModel(const std::string& modelID, const std::string meshDataID);

	///* Load Shader Textures */
	//int LoadShaderTexture(const std::string& textureID, const std::string& fileName);

	///* Load shaders */

	/* Managers */
	// TBH should'nt need these. Should provide a form of interface that allows calling code to do whatever it needs.
	// Adding these kind of defeats the purpose of this "resource manager"
	// (Subject to change).... don't rely on these
	CMeshDataManager* GetMeshDataManager(void);
	CBufferManager* GetBufferManager(void);
	CShaderTextureManager* GetShaderTextureManager(void);

	void ShutDown(void);
};

#endif