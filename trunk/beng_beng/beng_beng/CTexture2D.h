//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Texture class handling texture loading storing OpenGL handle to it.
//	Note: Does not store the actual image data.
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CTEXTURE2D_H__
#define __CTEXTURE2D_H__


#include <gl/glew.h>
#include <gl/wglew.h>
#include <string>

class CTexture2D
{
public:
	CTexture2D();
	~CTexture2D();

	bool LoadTexture(const std::string &fileName);

	GLuint GetTexture() { return m_textureHandle; }

private:
	GLuint m_textureHandle;
};


#endif