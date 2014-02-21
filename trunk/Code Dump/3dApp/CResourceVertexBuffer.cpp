#include "CResourceVertexBuffer.h"
#include "CD3DBase.h"


CResourceVertexBuffer::CResourceVertexBuffer(ID3D11Buffer *pInData) : m_pVertexBuffer(pInData)
{
}


CResourceVertexBuffer::~CResourceVertexBuffer(void)
{
	VCleanUp();
}


EResourceType CResourceVertexBuffer::VGetType(void)
{
	return eResourceVertexBuffer;
}


void CResourceVertexBuffer::VCleanUp(void)
{
	if(m_pVertexBuffer)
	{
		delete m_pVertexBuffer;
		m_pVertexBuffer = NULL;
	}
}


void* CResourceVertexBuffer::VGetData(void)
{
	if(m_pVertexBuffer)
	{
		return static_cast<void*>(m_pVertexBuffer);
	}

	return NULL;
}
