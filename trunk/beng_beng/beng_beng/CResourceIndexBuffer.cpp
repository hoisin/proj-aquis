#include "CResourceIndexBuffer.h"
#include "CIndexBuffer.h"


CResourceIndexBuffer::CResourceIndexBuffer(MeshData *pData)
{
	m_pIdxBuffer = new CIndexBuffer;
	//m_pIdxBuffer->LoadData(pData);
}


CResourceIndexBuffer::~CResourceIndexBuffer()
{
}


void CResourceIndexBuffer::VCleanUp()
{
	if(m_pIdxBuffer) {
		delete m_pIdxBuffer;
		m_pIdxBuffer = 0;
	}
}