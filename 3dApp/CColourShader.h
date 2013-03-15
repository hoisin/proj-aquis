/*
	Date: 01/02/2013
	Colour shader
*/

#pragma once
#ifndef __CCOLOURSHADER_H__
#define __CCOLOURSHADER_H__

#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

#include "IShader.h"
#include "ShaderParams.h"

class CColourShader : public IShader
{
protected:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pLayout;
	ID3D11Buffer* m_pMatrixBuffer;

public:
	CColourShader(void);
	~CColourShader(void);

	bool VInitialize(ID3D11Device* pDevice, const std::string& fileVertexShader, 
		const std::string& filePixelShader);

	void VShutDown();
	bool VRender(ID3D11DeviceContext* pContext, int indexCount, ShaderBaseParams* pParams);

private:
	bool VInitializeShader(ID3D11Device* pDevice, const std::string& fileVertexShader, 
		const std::string& filePixelShader);

	void VShutDownShader();

	bool VSetShaderParameters(ID3D11DeviceContext*, ShaderBaseParams* pParams);
	void VRenderShader(ID3D11DeviceContext* pContext, int indexCount);
};

#endif