/*
	07/02/2013
	Manager class for CD3DModels
*/

#ifndef __CD3DMODELMANAGER_H__
#define __CD3DMODELMANAGER_H__

#include <vector>
#include "GfxDefs.h"
#include "CD3DBase.h"
#include "CD3DModel.h"

class CD3DModelManager 
{
protected:
	std::vector<CD3DModel*> m_vpModels;

public:
	CD3DModelManager(void);
	~CD3DModelManager(void);

	// Adds a model to the collection, returns an index to model (-2 if fails to add)
	int AddD3DModel(ID3D11Buffer* pVertexBuffer, int vertexCount, ID3D11Buffer* pIndexBuffer, int indexCount, ID3D11ShaderResourceView* pTextureRes,
		EVertexType type, const std::string& modelName);

	// Remove functions only delete the model (freeing memory). The elements in the vector do not get removed
	bool RemoveD3DModel(int index);
	bool RemoveD3DModel(const std::string& modelName);

	CD3DModel* GetD3DModel(int index);
	CD3DModel* GetD3DModel(const std::string& modelName);

	// Removes all created models
	void EmptyD3DModels(void);

	int GetTotalModels(void);
};

#endif