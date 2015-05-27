//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Loads model/scene data 
//	Uses Assimp library for importing model data.
//
//	To Do: Extend capabilities to other file formats.
//		Current working with .obj files only
//	
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CSCENELOADER_H__
#define __CSCENELOADER_H__

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

class CMeshDataManager;
class CTextureManager;
class CMaterialManager;

class CSceneLoader
{
public:
	CSceneLoader(void);
	~CSceneLoader(void);

	// This loads a scene from a .obj file
	bool LoadScene(const std::string& fileName, CMeshDataManager* pMeshMgr,
		CTextureManager* pTextureMgr, CMaterialManager* pMaterialMgr);

	// This spawns a test scene which we define hardcoded
	bool TestScene(CMeshDataManager* pMeshMgr,
		CTextureManager* pTextureMgr, CMaterialManager* pMaterialMgr);
};


#endif