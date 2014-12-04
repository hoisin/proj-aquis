#include "CResourceVertexBuffer.h"
#include "CVertexBuffer.h"
#include "GfxDefs.h"

CResourceVertexBuffer::CResourceVertexBuffer(MeshData *pData) 
{
	m_pVertBuffer = new CVertexBuffer;
	//m_pVertBuffer->LoadData(pData);
}


CResourceVertexBuffer::~CResourceVertexBuffer()
{
	VCleanUp();
}


//------------------------------------------------------------------
//
//	VCleanUp(..)
//
//	Performs any clean up required
//
//------------------------------------------------------------------
void CResourceVertexBuffer::VCleanUp()
{
	if(m_pVertBuffer) {
		delete m_pVertBuffer;
		m_pVertBuffer = NULL;
	}
}
