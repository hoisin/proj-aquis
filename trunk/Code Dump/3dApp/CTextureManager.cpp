#include "CTextureManager.h"
#include "WICTextureLoader.h"


CTextureManager::CTextureManager(void)
{
}


CTextureManager::~CTextureManager(void)
{
}


bool CTextureManager::CreateTexture(CD3DBase* pBase, const std::string &textureID, 
		const std::string& fileTextureName, ID3D11ShaderResourceView *pOutTexture)
{
	// Load the texture in.
	std::wstring wFileTextureName = std::wstring(fileTextureName.begin(), fileTextureName.end());

	// Create the texture resource
	HRESULT result = CreateWICTextureFromFile(pBase->GetDevice(), pBase->GetContext(), wFileTextureName.c_str(), NULL, &pOutTexture);

	if(FAILED(result))
	{
		return false;
	}

	// Insert the new texture into map using std::pair....
	m_textures.insert(std::pair<std::string, ID3D11ShaderResourceView*>(textureID, pOutTexture));

	return true;
}


ID3D11ShaderResourceView *CTextureManager::GetTexture(const std::string &textureID)
{
	// Using iterators, find the specified texture
	std::map<std::string, ID3D11ShaderResourceView*>::iterator it = m_textures.find(textureID);

	// If we haven't reached the end of the map.
	if(it != m_textures.end())
	{
		return it->second;
	}

	return NULL;
}


void CTextureManager::ShutDown(void)
{
	std::map<std::string, ID3D11ShaderResourceView*>::iterator ita;

	for(ita = m_textures.begin(); ita != m_textures.end(); ita++)
	{
		ita->second->Release();
		ita->second = NULL;
	}
}


