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
//	pVertData		-	pointer to data
//	vertexCount		-	number of vertices
//	vertType		-	the vertex type
//
//	Description:
//	Loads mesh data in RAM to VRAM.
//
//----------------------------------------------------------------------------------------------------
void CVertexBuffer::LoadData(void* pVertData, glm::uint32 vertexCount, EVertexType vertType)
{
	m_vertCount = vertexCount;
	m_vertType = vertType;

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
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Colour buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), (void*)sizeof(glm::vec3));
		

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPT:
		m_numVBOs = 2;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePT), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Texture buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePT), (void*)sizeof(glm::vec3));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPNC:
		m_numVBOs = 3;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNC), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Normal buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNC), (void*)sizeof(glm::vec3));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Colour buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNC), (void*)(sizeof(glm::vec3) * 2));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPNT:
		m_numVBOs = 3;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNT), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Normal buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNT), (void*)sizeof(glm::vec3));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Texture buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNT), (void*)(sizeof(glm::vec3) * 2));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPNTT:
		m_numVBOs = 4;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Normal buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)sizeof(glm::vec3));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Tangent buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)(sizeof(glm::vec3) * 2));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Texture buffer
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[3]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)(sizeof(glm::vec3) * 3));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		break;

	default:
		break;
	}

	glBindVertexArray(0);
}


//----------------------------------------------------------------------------------------------------
//
//	UseBuffer(..)
//
//	Description:
//	Set this buffer to be the current buffer in use
//
//----------------------------------------------------------------------------------------------------
void CVertexBuffer::UseBuffer()
{
	// Free previous used buffer
	glBindVertexArray(0);			// Probably don't need this

	glBindVertexArray(m_VAO);
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

	if(m_numVBOs > 0) {
		delete [] m_pVBO;
	}
}