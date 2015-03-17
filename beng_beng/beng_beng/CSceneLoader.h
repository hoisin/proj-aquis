//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CSCENELOADER_H__
#define __CSCENELOADER_H__

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure

class CSceneLoader
{
public:
	CSceneLoader(void);
	~CSceneLoader(void);

	void LoadScene(void);
};


#endif