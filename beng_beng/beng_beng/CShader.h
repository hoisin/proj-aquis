//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Class handling shader
//
//	For current development purposes, implement to get simple drawing going.
//	This class will probably evolve or get replaced.
//
//	Author: SeaFooD � 2014
//
//--------------------------------------------------------------------------

#ifndef __CSHADER_H__
#define __CSHADER_H__

#include <gl/glew.h>
#include <gl/wglew.h>
#include <string>

class CShader
{
public:
	CShader();
	~CShader();

	bool LoadShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, GLuint &outID);
	
	void UserShader();

	GLuint GetShaderID() { return m_programID; }

protected:
	GLuint m_programID;
};

#endif