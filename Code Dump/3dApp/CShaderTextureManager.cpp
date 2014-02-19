#include "CShaderTextureManager.h"
#include "WICTextureLoader.h"

CShaderTextureManager::CShaderTextureManager(void)
{
}


CShaderTextureManager::~CShaderTextureManager(void)
{
	ShutDown();
}


bool CShaderTextureManager::CreateShaderTexture(CD3DBase *pBase, const std::string& fileTextureName, ID3D11ShaderResourceView** pOutTexture, const std::string& textureName)
{
	// Load the texture in.
	std::wstring wFileTextureName = std::wstring(fileTextureName.begin(), fileTextureName.end());

	// Create the texture resource
	HRESULT result = CreateWICTextureFromFile(pBase->GetDevice(), pBase->GetContext(), wFileTextureName.c_str(), NULL, pOutTexture);

	if(FAILED(result))
	{
		return false;
	}

	// Create texture info entry
	SShaderTextureInfo newInfo;
	
	if(textureName == " ")
	{
		char* dest;
		sprintf(dest, "%d", m_vpTextures.size());

		std::string numCnt(dest);

		std::string texture = "texture_" + numCnt;

		newInfo.name = texture;
	}
	else
	{
		newInfo.name = textureName;
	}

	newInfo.pTexture = *pOutTexture;

	// Add to list
	m_vpTextures.push_back(newInfo);

	return true;
}


void CShaderTextureManager::ShutDown(void)
{
	for(std::vector<SShaderTextureInfo>::iterator it = m_vpTextures.begin(); it != m_vpTextures.end(); it++)
	{
		if(it->pTexture)
		{
			it->pTexture->Release();
			it->pTexture = NULL;
		}
	}
}