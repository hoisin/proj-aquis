/*
	Date: 01/02/2013
	Interface classes for shaders
*/

#pragma once
#ifndef __ISHADER_H__
#define __ISHADER_H__

#include <d3dcompiler.h>
#include <string>

#include "GfxDefs.h"
#include "ShaderParams.h"

class IShader
{
public:
	virtual ~IShader(void) {}

	virtual bool VInitialize(ID3D11Device* pDevice, const std::string& fileVertexShader, 
		const std::string& filePixelShader) = 0;

	virtual void VShutDown() = 0;
	virtual bool VRender(ID3D11DeviceContext* pContext, int indexCount, ShaderBaseParams* pParams) = 0;

private:
	virtual bool VInitializeShader(ID3D11Device* pDevice, const std::string& fileVertexShader, 
		const std::string& filePixelShader) = 0;

	virtual void VShutDownShader() = 0;

	virtual bool VSetShaderParameters(ID3D11DeviceContext*, ShaderBaseParams* pParams) = 0;
	virtual void VRenderShader(ID3D11DeviceContext* pContext, int indexCount) = 0;
};

#endif