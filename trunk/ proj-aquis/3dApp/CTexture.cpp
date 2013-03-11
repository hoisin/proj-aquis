#include "CTexture.h"

CTexture::CTexture(void) : m_pTexture(NULL)
{
}


CTexture::CTexture(const CTexture& other) : m_pTexture(NULL)
{
	// For now do nothing
}


CTexture::~CTexture(void)
{
	VShutDown();
}


bool CTexture::VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string& fileTextureName)
{
	// Load the texture in.
	std::wstring wFileTextureName = std::wstring(fileTextureName.begin(), fileTextureName.end());

	HRESULT result = CreateWICTextureFromFile(pDevice, pContext, wFileTextureName.c_str(), NULL, &m_pTexture);

	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void CTexture::VShutDown(void)
{
	if(m_pTexture)
		m_pTexture->Release();

	m_pTexture = NULL;
}


ID3D11ShaderResourceView* CTexture::GetTexture(void)
{
	return m_pTexture;
}
