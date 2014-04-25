//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Holds the related VBOs to VAO.
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CVERTEXDATA_H__
#define __CVERTEXDATA_H__

#include <gl/glew.h>
#include <gl/wglew.h>

#include "GfxDefs.h"

class CVertexBuffer
{
public:
	CVertexBuffer();
	~CVertexBuffer();

	void LoadData(MeshData *pData);

	void UseBuffer();

	GLuint GetVertexArray() { return m_VAO; }

	void ShutDown();

private:
	GLuint m_vertCount;	// Number of vertices (assuming a vector 3)
	GLuint m_numVBOs;	// Number of vertex buffer objects
	GLuint m_VAO;		// Only one vertex array object per CVertexData
	GLuint *m_pVBO;

	EVertexType m_vertType;	
};

#endif