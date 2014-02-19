/*
	Date: 05/02/2013
	Base shader class
*/

#pragma once
#ifndef __CD3DEFFECT_H__
#define __CD3DEFFECT_H__

#include <d3dcompiler.h>
#include <string>

#include "GfxDefs.h"
#include "ShaderParams.h"

class CD3DEffect
{
protected:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pLayout;
	ID3D11Buffer* m_pMatrixBuffer;

public:
	CD3DEffect(void);
	virtual ~CD3DEffect(void);

	bool Initialize(ID3D11Device* pDevice, EVertexType vertexType, const std::string& fileVertexShader, 
		const std::string& filePixelShader);

	void ShutDown();
	bool Render(ID3D11DeviceContext* pContext, int indexCount, ShaderBaseParams* pParams);

protected:
	virtual bool VInitializeShader(ID3D11Device* pDevice, EVertexType vertexType, const std::string& fileVertexShader, 
		const std::string& filePixelShader);

	virtual void VShutDownShader();

	virtual bool VSetShaderParameters(ID3D11DeviceContext*, ShaderBaseParams* pParams);
	virtual void VRenderShader(ID3D11DeviceContext* pContext, int indexCount);

	void GetLayout(D3D11_INPUT_ELEMENT_DESC** pLayout, unsigned int& numElements, EVertexType type);
};

#endif