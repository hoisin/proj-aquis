/*
	Date: 30/01/2013
	Model class handling D3D vertex and index buffers.

	Note: May inherit from, so using protected data memebers
*/

#pragma once
#ifndef __CD3DMODEL_H__
#define __CD3DMODEL_H__

#include "GfxDefs.h"

class CD3DBase;

class CD3DModel
{
protected:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer *m_indexBuffer;
	ID3D11ShaderResourceView* m_pTexture;						
	int m_vertexCount; 
	int m_indexCount;
	int m_vertexSize;

	std::string m_name;
	EVertexType m_vertType;

public:
	CD3DModel(void);
	CD3DModel(const CD3DModel& other);
	~CD3DModel(void);
	
	int Initialise(CD3DBase* pD3d, MeshData* pData, const std::string& modelName, const std::string fileTextureName = "NULL");

	void ShutDown(void);

	void Render(CD3DBase* pD3d);

	int GetVertexCount(void) { return m_vertexCount; }
	int GetIndexCount(void) { return m_indexCount; }
	std::string GetModelName(void) { return m_name; }

	ID3D11Buffer* GetVertexBuffer(void) { return m_vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer(void) { return m_indexBuffer; }
	ID3D11ShaderResourceView* GetTexture(void) { return m_pTexture; }
	EVertexType GetVertexType(void);

protected:
	virtual int VInitialiseBuffers(ID3D11Device* pDevice, MeshData* pData);

	// Releases buffers
	virtual void VShutDownBuffers(void);

	// Draws buffers
	virtual void VRenderBuffers(ID3D11DeviceContext* pContext);

	// Loads texture into shader resource
	virtual int VLoadTexture(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string fileTextureName);

	// Frees loaded textures
	virtual void VReleaseTexture(void);

	// Internal helper method
	void CopyVertexData(SVertexType **pVertices, MeshData* pData);
};

#endif