/*
	07/02/2013
	Manager for CD3DShaders
*/

#ifndef __CD3DSHADERMANAGER_H__
#define __CD3DSHADERMANaGER_H__

#include <vector>
#include "CD3DBase.h"
#include "CD3DShader.h"

class CD3DShaderManager
{
protected:
	std::vector<CD3DShader*> m_vpShaders;

public:
	CD3DShaderManager(void);
	~CD3DShaderManager(void);

	// Returns index of added shader ( Returns -2 for failed add )
	int AddD3DShader(ID3D11Device* pDevice, EVertexType vertexType, const D3D11_SAMPLER_DESC& samplerDesc, const std::string& shaderName, const std::string& fileVertexShader, 
		const std::string& vertexShaderEntry, const std::string& vertexShaderTarget, const std::string& filePixelShader, const std::string& pixelShaderEntry, const std::string& pixelShaderTarget);

	// Returns error code
	int RemoveD3DShader(int index);

	// Removes all created shaders
	void EmptyD3DShaders(void);

	CD3DShader* GetD3DShader(int index);

	int GetTotalShaders(void);
};

#endif