//--------------------------------------------------------------------------
//
//	14/04/2014
//
//	Texture class handling texture loading storing OpenGL handle to it.
//	Note: Does not store the actual image data.
//
//	TO DO: Add more texture operations such as more filter options, mip maps, etc..
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

	bool LoadTexture(unsigned int width, unsigned int height, GLint internalFormat,
	GLint texFormat, GLenum dataType, unsigned char *pData);

	void UseTexture();

	GLuint GetTexture() { return m_textureHandle; }

	void CleanUp();

private:
	GLuint m_textureHandle;
};


#endif