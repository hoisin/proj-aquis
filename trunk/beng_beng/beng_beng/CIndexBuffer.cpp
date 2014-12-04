#include "CIndexBuffer.h"


CIndexBuffer::CIndexBuffer()
{
}


CIndexBuffer::~CIndexBuffer()
{
	ShutDown();
}


void CIndexBuffer::LoadData(void* pIndexData, glm::uint32 indexCount)
{
	m_idxCount = indexCount;

	glGenBuffers(1, &m_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_idxCount * sizeof(unsigned int), pIndexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void CIndexBuffer::UseBuffer()
{
	// Free previous used index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// Probably don't need this

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}


void CIndexBuffer::ShutDown()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_elementBuffer);
}