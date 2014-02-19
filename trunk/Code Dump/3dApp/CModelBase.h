/*
	Date: 30/01/2013
	Model class handling D3D vertex and index buffers
*/

#pragma once
#ifndef __CMODELBASE_H__
#define __CMODELBASE_H__

#include "GfxDefs.h"
#include "CTexture.h"

class CModelBase
{
protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	CTexture* m_pTexture;

public:
	CModelBase(void);
	CModelBase(const CModelBase& otherModel);
	virtual ~CModelBase(void);

	virtual bool VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
		const std::string fileTextureName, const std::string fileModelName);
	virtual void VShutDown(void);

	void Render(ID3D11DeviceContext* pContext);

	int GetVertexCount(void) { return m_vertexCount; }
	int GetIndexCount(void) { return m_indexCount; }

	ID3D11ShaderResourceView* GetTexture(void);

protected:
	// Method uploads model into buffers
	virtual bool VInitialiseBuffers(ID3D11Device* pDevice);

	// Releases buffers
	virtual void VShutDownBuffers(void);

	// Draws buffers
	virtual void VRenderBuffers(ID3D11DeviceContext* pContext);

	// Method load model data
	virtual bool VLoadModel(const std::string fileModelName);

	// Loads texture into shader resource
	virtual bool VLoadTexture(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string fileTextureName);

	// Frees loaded textures
	virtual void VReleaseTexture(void);
};

#endif