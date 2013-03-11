#include "CD3DModelManager.h"

#include <iostream>

CD3DModelManager::CD3DModelManager(void)
{
}


CD3DModelManager::~CD3DModelManager(void)
{
	EmptyD3DModels();
}


int CD3DModelManager::AddD3DModel(CD3DBase* pD3d, MeshData* pData, const std::string& modelName, const std::string fileTextureName)
{
	// Check name is not already used & check for unused elements if any
	bool bNameUsed = false;
	int freeIndex = -1;

	for(int i = 0; i < (int)m_vpModels.size(); i++)
	{
		if(m_vpModels[i]->GetModelName() == modelName)
		{
			bNameUsed = true;
			break;
		}
		else
		{
			// If there is a free pointer in the array, simply reuse rather than expand the array
			if(m_vpModels[i] == NULL)
			{
				freeIndex = i;
				break;
			}
		}
	}

	// Return some sort of warning (system won't stop you labeling multiple models with the same name)
	if(bNameUsed)
		std::cout << "WARNING: EXSITING MODEL WITH SAME NAME" << std::endl;

	if(freeIndex == -1)
	{
		// Create new model and initialise
		CD3DModel* pModel = new CD3DModel;
		if(!pModel->Initialise(pD3d, pData, modelName, fileTextureName))
		{
			delete pModel;
			return -2;
		}

		// Add to collection and return index
		m_vpModels.push_back(pModel);

		return ((int)m_vpModels.size() - 1);
	}
	else
	{
		// Create new model and initialise
		CD3DModel* pModel = new CD3DModel;
		if(!pModel->Initialise(pD3d, pData, modelName, fileTextureName))
		{
			delete pModel;
			return -2;
		}

		m_vpModels[freeIndex] = pModel;

		return freeIndex;
	}
}


bool CD3DModelManager::RemoveD3DModel(int index)
{
	// Boundary check
	if(index < 0 || index >= (int)m_vpModels.size())
		return false;

	if(m_vpModels[index])
	{
		delete m_vpModels[index];
		m_vpModels[index] = NULL;
	}

	return true;
}


bool CD3DModelManager::RemoveD3DModel(const std::string& modelName)
{
	// Find the value we want
	bool bFound = false;
	int idx;

	for(idx = 0; idx < (int)m_vpModels.size(); idx++)
	{
		//Make sure it aint empty unless you love access violation errors
		if(m_vpModels[idx] != NULL)
		{
			if(m_vpModels[idx]->GetModelName() == modelName)
			{
				bFound = true;
				break;
			}
		}
	}

	if(bFound)
	{
		delete m_vpModels[idx];
		m_vpModels[idx] = NULL;

		return true;
	}

	// Not found otherwise
	return false;
}


CD3DModel* CD3DModelManager::GetD3DModel(int index)
{
	// Boundary check
	if(index < 0 || index >= (int)m_vpModels.size())
		return NULL;
	
	return m_vpModels[index];
}


CD3DModel* CD3DModelManager::GetD3DModel(const std::string& modelName)
{
	// Find the value we want
	bool bFound = false;
	int idx;

	for(idx = 0; idx < (int)m_vpModels.size(); idx++)
	{
		// Make sure it aint empty unless you love access violation errors
		if(m_vpModels[idx] != NULL)
		{
			if(m_vpModels[idx]->GetModelName() == modelName)
			{
				bFound = true;
				break;
			}
		}
	}

	if(bFound)
		return m_vpModels[idx];
	
	// Not found otherwise
	return NULL;
}


void CD3DModelManager::EmptyD3DModels(void)
{
	for(int i = 0; i < (int)m_vpModels.size(); i++)
	{
		// Make sure we aint deleting a NULL object
		if(m_vpModels[i])
		{
			delete m_vpModels[i];
			m_vpModels[i] = NULL;
		}
	}

	m_vpModels.clear();
}


int CD3DModelManager::GetTotalModels(void)
{
	return (int)m_vpModels.size();
}