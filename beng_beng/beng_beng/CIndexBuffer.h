//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Index Buffer
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CINDEXBUFFER_H__
#define __CINDEXBUFFER_H__

#include <gl/glew.h>
#include <gl/wglew.h>
#include "GfxDefs.h"

class CIndexBuffer
{
public:
	CIndexBuffer();
	~CIndexBuffer();

	void LoadData(MeshData *pData);

	GLuint GetElementBuffer()	{ return m_elementBuffer; }
	GLuint GetIndexCount()		{ return m_idxCount; } 
		
	void ShutDown();

private:
	GLuint m_idxCount;			// Number of index entries
	GLuint m_elementBuffer;
};


#endif