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
	m_vertCount = pData->vertexCount;
	m_vertType = pData->vertexType;

	// Generate & setup VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	
	// Generate buffers based on vertex type
	switch(m_vertType)
	{
	case eVertexPC:
		m_numVBOs = 2;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, pData->vertexCount*sizeof(SVertexTypePC), pData->pVertices, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Colour buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, pData->vertexCount*sizeof(SVertexTypePC), pData->pVertices, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), &((SVertexTypePC*)(pData->pVertices))[0].colour);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(m_numVBOs, m_pVBO);
	glDeleteVertexArrays(1, &m_VAO);

	if(m_numVBOs > 0)
	{
		delete [] m_pVBO;
	}
}