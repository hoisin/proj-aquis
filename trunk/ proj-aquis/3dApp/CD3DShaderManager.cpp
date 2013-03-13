#include "CD3DShaderManager.h"
#include "ErrorCodes.h"

CD3DShaderManager::CD3DShaderManager(void)
{
}


CD3DShaderManager::~CD3DShaderManager(void)
{
	EmptyD3DShaders();
}


int CD3DShaderManager::AddD3DShader(ID3D11Device* pDevice, EVertexType vertexType, const D3D11_SAMPLER_DESC& samplerDesc, const std::string& shaderName, const std::string& fileVertexShader, 
		const std::string& vertexShaderEntry, const std::string& vertexShaderTarget, const std::string& filePixelShader, const std::string& pixelShaderEntry, const std::string& pixelShaderTarget)
{
	// Check for free elements
	int freeIdx = -1;

	for(int i = 0; i < (int)m_vpShaders.size(); i++)
	{
		if(m_vpShaders[i] == NULL)
		{
			freeIdx = i;
			break;
		}
	}

	if(freeIdx == -1)
	{
		CD3DShader* pShader = new CD3DShader;

		if(!pShader->Initialize(pDevice, vertexType, samplerDesc, shaderName, fileVertexShader, vertexShaderEntry, vertexShaderTarget, filePixelShader, pixelShaderEntry, pixelShaderTarget))
		{
			delete pShader;
			return -2;
		}

		m_vpShaders.push_back(pShader);

		return ((int)m_vpShaders.size() - 1);
	}
	else
	{
		m_vpShaders[freeIdx] = new CD3DShader;
		if(!m_vpShaders[freeIdx]->Initialize(pDevice, vertexType, samplerDesc, shaderName, fileVertexShader, vertexShaderEntry, vertexShaderTarget, filePixelShader, pixelShaderEntry, pixelShaderTarget))
		{
			delete m_vpShaders[freeIdx];
			m_vpShaders[freeIdx] = NULL;
			return -2;
		}

		return freeIdx;
	}
}


int CD3DShaderManager::RemoveD3DShader(int index)
{
	if(index < 0 || index >= (int)m_vpShaders.size())
		return ERROR_GFX_SHADER_REMOVE;

	if(m_vpShaders[index])
	{
		delete m_vpShaders[index];
		m_vpShaders[index] = NULL;
	}

	return ERROR_PASS;
}


void CD3DShaderManager::EmptyD3DShaders(void)
{
	// Clean UP
	for(int i = 0; i < (int)m_vpShaders.size(); i++)
	{
		if(m_vpShaders[i])
		{
			delete m_vpShaders[i];
			m_vpShaders[i] = NULL;
		}
	}
}


CD3DShader* CD3DShaderManager::GetD3DShader(int index)
{
	// Boundary check
	if(index < 0 || index >= (int)m_vpShaders.size())
		return NULL;

	return m_vpShaders[index];
}


int CD3DShaderManager::GetTotalShaders(void)
{
	return (int)m_vpShaders.size();
}
