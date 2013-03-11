/*
	Date: 01/02/2013
	Shader params definitions
*/

#pragma once
#ifndef __SHADERPARAMS_H__
#define __SHADERPARAMS_H__

#include <DirectXMath.h>

enum ShaderType
{
	SHADERBASE,
	SHADERTEXTURE,
	SHADERCOUNT
};

// Base param struct
struct ShaderBaseParams
{
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX world;

	// Must overriden with new shader param with own unique shader type
	virtual ShaderType GetType(void) { return SHADERBASE; }
};


// Base param struct
struct ShaderTextureParams : public ShaderBaseParams
{
	ID3D11ShaderResourceView* pTexture;

	// Must overriden with new shader param with own unique shader type
	virtual ShaderType GetType(void) { return SHADERTEXTURE; }
};


#endif
