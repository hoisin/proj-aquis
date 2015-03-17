//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Loads model/scene data 
//	Uses Assimp library for importing model data.
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

class CSceneLoader
{
public:
	CSceneLoader(void);
	~CSceneLoader(void);

	bool LoadScene(const std::string& fileName, CMeshDataManager* pMeshMgr);
};


#endif