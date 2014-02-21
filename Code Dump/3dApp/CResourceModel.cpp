#include "CResourceModel.h"

#include "CD3DModel.h"
#include "CResourceMeshData.h"
#include "CResourceVertexBuffer.h"
#include "CResourceIndexBuffer.h"


CResourceModel::CResourceModel(CResourceMeshData *pInResMeshData, CResourceVertexBuffer *pInResVertBuf,
	CResourceIndexBuffer *pInResIndexBuf)
{
}


CResourceModel::~CResourceModel(void)
{
	VCleanUp();
}


EResourceType CResourceModel::VGetType(void)
{
	return eResourceIndexBuffer;
}


void CResourceModel::VCleanUp(void)
{
	if(m_pModel)
	{
		delete m_pModel;
		m_pModel = NULL;
	}
}


void* CResourceModel::VGetData(void)
{
	if(m_pModel)
	{
		return static_cast<void*>(m_pModel);
	}

	return NULL;
}

