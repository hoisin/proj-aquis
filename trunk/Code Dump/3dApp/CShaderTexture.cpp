#include "CShaderTexture.h"
#include "ErrorCodes.h"

CShaderTexture::CShaderTexture(void) : m_pTexture(NULL)
{
	// Do nothing
}


CShaderTexture::CShaderTexture(const CShaderTexture& other) : m_pTexture(NULL)
{
	// Do nothing
}


CShaderTexture::~CShaderTexture(void)
{
	VShutDown();
}


int CShaderTexture::VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string& fileTextureName)
{
	// Load the texture in.
	std::wstring wFileTextureName = std::wstring(fileTextureName.begin(), fileTextureName.end());

	// Create the texture resource
	HRESULT result = CreateWICTextureFromFile(pDevice, pContext, wFileTextureName.c_str(), NULL, &m_pTexture);

	if(FAILED(result))
	{
		return ERROR_GFX_WIC_CREATE_TEXTURE;
	}

	return ERROR_PASS;
}


void CShaderTexture::VShutDown(void)
{
	if(m_pTexture)
		m_pTexture->Release();

	m_pTexture = NULL;
}


ID3D11ShaderResourceView* CShaderTexture::GetTexture(void)
{
	return m_pTexture;
}
