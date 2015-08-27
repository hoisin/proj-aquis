///--------------------------------------------------------------------------
//
//	25/08/2015
//
//	Base shader technique class
//
//	Replaces CShader
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CTECHNIQUE_H__
#define __CTECHNIQUE_H__

#include <gl/glew.h>
#include <gl/wglew.h>
#include <list>

class CTechnique
{
public:
	CTechnique();
	virtual ~CTechnique();

	virtual bool VInit();

	void Enable();

protected:
	bool AddShader(GLenum shaderType, const char* pShaderText);

	bool Finialise();

	GLint GetUniformLocation(const char* pUniformName);

	GLint GetProgramParam(GLint param);

private:
	GLuint m_shaderProg;

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;
};

#endif