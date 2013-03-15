/*
	Date: 31/01/2013
	Model class representing a cube shape
*/

#pragma once
#ifndef __CMODELCUBE_H__
#define __CMODELCUBE_H__

#include <vector>
#include "CModelBase.h"

class CModelCube : public CModelBase
{
protected:
	std::vector<ModelVertexTypePNT*> m_pModelVertices;
	std::vector<int> m_vIndices;

	float m_size;
	int m_tessellation;

public:
	CModelCube(float size = 1, int tessellation = 1);
	CModelCube(const CModelCube& other);
	~CModelCube(void);

	bool VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
		const std::string fileTextureName, const std::string fileModelName = "NULL");

	void VShutDown(void);

protected:
	bool VInitialiseBuffers(ID3D11Device* pDevice);

	// This method will generate the verts for the cube instead of loading
	bool VLoadModel(const std::string fileModelName);
};

#endif