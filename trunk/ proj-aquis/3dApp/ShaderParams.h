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
	SHADERBASE,					// For shaders with only PVW matrices
	SHADERTEXTURE,				// For shaders with texture	
	SHADERLIGHTTEXTURE,			// For shaders with light and shaders
	SHADERCOUNT
};


/*
	Base param struct

	Params:
		Matrix : projection
		Matrix : view
		Matrix : world
*/
struct ShaderBaseParams
{
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX world;

	// Must overriden with new shader param with own unique shader type
	virtual ShaderType GetType(void) { return SHADERBASE; }
};


/*
	Texture param struct

	Params:
		Matrix : projection
		Matrix : view
		Matrix : world
		Texture : texture
*/
struct ShaderTextureParams : public ShaderBaseParams
{
	ID3D11ShaderResourceView* pTexture;

	// Must overriden with new shader param with own unique shader type
	virtual ShaderType GetType(void) { return SHADERTEXTURE; }
};


/*
	Texture param struct

	Params:
		Matrix : projection
		Matrix : view
		Matrix : world
		Texture : texture
*/
struct ShaderLightTextureParams : public ShaderBaseParams
{
	ID3D11ShaderResourceView* pTexture;
	DirectX::XMFLOAT4 lightColour;
	DirectX::XMFLOAT3 lightDirection;
	float lightIntensity;

	// Must overriden with new shader param with own unique shader type
	virtual ShaderType GetType(void) { return SHADERLIGHTTEXTURE; }
};

#endif
