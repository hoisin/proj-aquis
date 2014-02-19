/*
	Date: 31/01/2013
	Texture class handling a 2D texture for passing into a shader
*/

#pragma once
#ifndef __CSHADERTEXTURE_H__
#define __CSHADERTEXTURE_H__

#include <d3d11.h>
#include <string>

#include "WICTextureLoader.h"

class CShaderTexture
{
protected:
	ID3D11ShaderResourceView* m_pTexture;

public:
	CShaderTexture(void);
	CShaderTexture(const CShaderTexture& other);
	void operator=(const CShaderTexture& other);

	virtual ~CShaderTexture(void);

	virtual int VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string& fileTextureName);
	virtual void VShutDown(void);

	ID3D11ShaderResourceView* GetTexture(void);
};

#endif