//--------------------------------------------------------------------------
//
//	25/07/2014
//
//	G-Buffer used for deferred rendering
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------


#ifndef __CGBUFFER_H__
#define __CGBUFFER_H__

#include <gl/glew.h>
#include <gl/wglew.h>

class CGBuffer
{
	enum EBufferType {
		ePosition = 0,			// Will be removed further down the line
		eDiffuse,				// Also known as the albedo
		eNormal,
		eSizeOfGBuffer
	};

public:
	CGBuffer(void);
	~CGBuffer(void);

protected:
	GLUINT m_fbo;						// Frame buffer object for off screen rendering
	GLUINT m_buffer[eSizeOfGBuffer];
};

#endif