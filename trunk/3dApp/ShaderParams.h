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
	SHADERCOLOUR,				// For shaders with diffuse colour
	SHADERTEXTURE,				// For shaders with texture	
	SHADERLIGHTCOLOUR,			// For shaders with light and diffuse colour
	SHADERLIGHTTEXTURE,			// For shaders with light and texture
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
	Colour param struct

	Params:
		Matrix : projection
		Matrix : view
		Matrix : world
*/
struct ShaderColourParams : public ShaderBaseParams
{
	DirectX::XMFLOAT4 colour;

	ShaderType GetType(void) { return SHADERCOLOUR; }
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

	ShaderType GetType(void) { return SHADERTEXTURE; }
};


/*
	Light colour param struct

	Params:
		Matrix : projection
		Matrix : view
		Matrix : world
		float4 : Diffuse colour
		float4 : light colour
		float3 : light direction
		float : light intensity	
*/
struct ShaderLightColourParams : public ShaderBaseParams
{
	DirectX::XMFLOAT4 colour;
	DirectX::XMFLOAT4 lightColour;
	DirectX::XMFLOAT3 lightDirection;
	float lightIntensity;

	ShaderType GetType(void) { return SHADERLIGHTCOLOUR; }
};


/*
	Light texture param struct

	Params:
		Matrix : projection
		Matrix : view
		Matrix : world
		Texture : texture
		float4 : light colour
		float3 : light direction
		float : light intensity
*/
struct ShaderLightTextureParams : public ShaderBaseParams
{
	ID3D11ShaderResourceView* pTexture;
	DirectX::XMFLOAT4 lightColour;
	DirectX::XMFLOAT3 lightDirection;
	float lightIntensity;

	ShaderType GetType(void) { return SHADERLIGHTTEXTURE; }
};

#endif
