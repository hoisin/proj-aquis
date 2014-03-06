#include "CResourceIndexBuffer.h"
#include "CD3DBase.h"


CResourceIndexBuffer::CResourceIndexBuffer(ID3D11Buffer *pInData) : m_pIndexBuffer(pInData)
{
}


CResourceIndexBuffer::~CResourceIndexBuffer(void)
{
	VCleanUp();
}


EResourceType CResourceIndexBuffer::VGetType(void)
{
	return eResourceIndexBuffer;
}


void CResourceIndexBuffer::VCleanUp(void)
{
	if(m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = NULL;
	}
}


void* CResourceIndexBuffer::VGetData(void)
{
	if(m_pIndexBuffer)
	{
		return static_cast<void*>(m_pIndexBuffer);
	}

	return NULL;
}
