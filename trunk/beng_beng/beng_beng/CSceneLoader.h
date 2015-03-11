//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Class handling shader
//
//	For current development purposes, implement to get simple drawing going.
//	This class will probably evolve or get replaced.
//
//	Author: SeaFooD © 2014
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