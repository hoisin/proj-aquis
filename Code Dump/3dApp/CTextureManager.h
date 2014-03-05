/*
	18/03/2013
	Author: Matthew Tsang

	This manages creation and clean up of 2D textures used for shaders (ID3D11ShaderResourceView)
*/

#ifndef __CTEXTUREMANAGER_H__
#define __CTEXTUREMANAGER_H__

#include <vector>
#include <map>
#include "CD3DBase.h"

class CTextureManager
{
public:
	CTextureManager(void);
	~CTextureManager(void);

	bool CreateTexture(CD3DBase* pBase, const std::string &textureID, 
		const std::string& fileTextureName, ID3D11ShaderResourceView *pOutTexture = NULL);

	ID3D11ShaderResourceView *GetTexture(const std::string &textureID);

	// Releases all loaded textures
	void ShutDown(void);

private:
	std::map<std::string, ID3D11ShaderResourceView*> m_textures;
};

#endif