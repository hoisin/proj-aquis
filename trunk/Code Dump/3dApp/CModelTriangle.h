/*
	Date: 01/02/2013
	Model class representing a triangle, 
		used mostly for testing and debuging
*/

#pragma once
#ifndef __CMODELTRIANGLE_H__
#define __CMODELTRIANGLE_H__

#include <vector>
#include "CModelBase.h"

class CModelTriangle : public CModelBase
{
protected:
	std::vector<ModelVertexTypePC*> m_pModelVertices;
	std::vector<int> m_vIndices;

	float m_size;
	float m_red, m_green, m_blue;

public:
	CModelTriangle(float size = 1, float red = 1, float green = 1, float blue = 1);
	CModelTriangle(const CModelTriangle& other);
	virtual ~CModelTriangle(void);

	bool VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
		const std::string fileTextureName, const std::string fileModelName = "NULL");

	void VShutDown(void);

protected:
	bool VInitialiseBuffers(ID3D11Device* pDevice);

	// This method will generate the verts for the triangle instead of loading
	bool VLoadModel(const std::string fileModelName);
};

#endif