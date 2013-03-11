/*
	Date: 31/01/2013
	Texture class handling a 2D texture
*/

#pragma once
#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__

#include <d3d11.h>
#include <string>

#include "WICTextureLoader.h"

class CTexture
{
protected:
	ID3D11ShaderResourceView* m_pTexture;

public:
	CTexture(void);
	CTexture(const CTexture& other);
	virtual ~CTexture(void);

	virtual bool VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string& fileTextureName);
	virtual void VShutDown(void);

	ID3D11ShaderResourceView* GetTexture(void);
};

#endif