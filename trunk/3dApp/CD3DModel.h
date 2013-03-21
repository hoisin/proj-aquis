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
	ID3D11Buffer *m_pVertexBuffer;
	ID3D11Buffer *m_pIndexBuffer;
	ID3D11ShaderResourceView* m_pTexture;						
	int m_vertexCount; 
	int m_indexCount;
	//int m_vertexSize;

	std::string m_name;
	EVertexType m_vertType;

public:
	CD3DModel(void);
	CD3DModel(const CD3DModel& other);
	~CD3DModel(void);
	
	int Initialise(ID3D11Buffer* pVertexBuffer, int vertCount, ID3D11Buffer* pIndexBuffer, int indexCount, ID3D11ShaderResourceView* pTextureRes,
		EVertexType type, const std::string& modelName);

	void ShutDown(void);

	void Render(CD3DBase* pD3d);

	int GetVertexCount(void) { return m_vertexCount; }
	int GetIndexCount(void) { return m_indexCount; }
	std::string GetModelName(void) { return m_name; }

	ID3D11Buffer* GetVertexBuffer(void) { return m_pVertexBuffer; }
	ID3D11Buffer* GetIndexBuffer(void) { return m_pIndexBuffer; }
	ID3D11ShaderResourceView* GetTexture(void) { return m_pTexture; }
	EVertexType GetVertexType(void) { return m_vertType; }

protected:
	// Draws buffers
	virtual void VRenderBuffers(ID3D11DeviceContext* pContext);
};

#endif