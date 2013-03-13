/*
	Date: 05/02/2013
	Base shader class
*/

#pragma once
#ifndef __CD3DSHADER_H__
#define __CD3DSHADER_H__

#include <d3dcompiler.h>
#include <string>

#include "GfxDefs.h"
#include "ShaderParams.h"

class CD3DShader
{
protected:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pLayout;
	ID3D11Buffer* m_pMatrixBuffer;
	ID3D11Buffer* m_pLightBuffer;
	ID3D11SamplerState* m_sampleState;

	std::string m_name;
	EVertexType m_vertexType;

public:
	CD3DShader(void);
	virtual ~CD3DShader(void);

	int Initialize(ID3D11Device* pDevice, EVertexType vertexType, const D3D11_SAMPLER_DESC& samplerDesc, const std::string& shaderName, const std::string& fileVertexShader, 
		const std::string& vertexShaderEntry, const std::string& vertexShaderTarget, const std::string& filePixelShader, const std::string& pixelShaderEntry, const std::string& pixelShaderTarget);

	void ShutDown();

	int Render(ID3D11DeviceContext* pContext, int indexCount, ShaderBaseParams* pParams);

	std::string GetName(void);
	EVertexType GetVertexType(void);

protected:
	virtual int VInitializeShader(ID3D11Device* pDevice, EVertexType vertexType, const D3D11_SAMPLER_DESC& samplerDesc, const std::string& fileVertexShader, 
		const std::string& vertexShaderEntry, const std::string& vertexShaderTarget, const std::string& filePixelShader, const std::string& pixelShaderEntry, const std::string& pixelShaderTarget);

	virtual void VShutDownShader();

	virtual int VSetShaderParameters(ID3D11DeviceContext*, ShaderBaseParams* pParams);
	virtual void VRenderShader(ID3D11DeviceContext* pContext, int indexCount);

	void GetLayout(D3D11_INPUT_ELEMENT_DESC** pLayout, unsigned int& numElements, EVertexType type);
};

#endif