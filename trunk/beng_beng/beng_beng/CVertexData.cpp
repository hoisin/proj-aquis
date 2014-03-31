#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer() : m_pVBO(NULL)
{
}


CVertexBuffer::~CVertexBuffer()
{
	ShutDown();
}


//----------------------------------------------------------------------------------------------------
//
//	LoadData(..)
//
//	Params:
//	pData		-	Mesh data to load into GPU memory
//
//	Description:
//	Loads mesh data in RAM to VRAM.
//
//----------------------------------------------------------------------------------------------------
void CVertexBuffer::LoadData(MeshData *pData)
{
	m_vertType = pData->vertexType;

	// Generate & setup VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Generate buffers based on vertex type
	switch(m_vertType)
	{
	case eVertexPC:
		m_numVBOs = 2;

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, pData->vertexCount*3*sizeof(GL_FLOAT), pData->pVertices, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), 0);
		glEnableVertexAttribArray(0);

		// Colour buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, pData->vertexCount*3*sizeof(GL_FLOAT), pData->pVertices, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), &((SVertexTypePC*)(pData->pVertices))[0].colour);
		glEnableVertexAttribArray(1);
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Description:
//	Clean up
//
//----------------------------------------------------------------------------------------------------
void CVertexBuffer::ShutDown()
{
	glDeleteBuffers(m_numVBOs, m_pVBO);
	glDeleteVertexArrays(1, &m_VAO);
}