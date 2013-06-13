/*
	18/03/2013

	This manages creation and clean up of 2D textures used for shaders (ID3D11ShaderResourceView)
*/

#ifndef __CSHADERTEXTUREMANAGER_H__
#define __CSHADERTEXTUREMANAGER_H__

#include <vector>
#include "CD3DBase.h"

class CShaderTextureManager
{
	struct SShaderTextureInfo
	{
		std::string name;
		ID3D11ShaderResourceView* pTexture;
	};

public:
	CShaderTextureManager(void);
	~CShaderTextureManager(void);

	bool CreateShaderTexture(CD3DBase* pBase, const std::string& fileTextureName, ID3D11ShaderResourceView** pOutTexture, const std::string& textureName = " ");

	// Releases all loaded textures
	void ShutDown(void);

private:
	std::vector<SShaderTextureInfo> m_vpTextures;
};

#endif