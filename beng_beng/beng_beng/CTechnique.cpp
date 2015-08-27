#include "CTechnique.h"
#include <fstream>
#include <string>

CTechnique::CTechnique() : m_shaderProg(0)
{
}


CTechnique::~CTechnique()
{
	for (const auto& it : m_shaderObjList) {
		glDeleteShader(it);
	}

	if (m_shaderProg != 0) {
		glDeleteProgram(m_shaderProg);
		m_shaderProg = 0;
	}
}


bool CTechnique::VInit()
{
	m_shaderProg = glCreateProgram();

	if (m_shaderProg == 0)
		return false;

	return true;
}


bool CTechnique::AddShader(GLenum shaderType, const char* pFileName)
{
	std::ifstream shaderStream(pFileName, std::ios::in);
	std::string shaderCode;

	if (shaderStream.is_open()) {
		std::string line = "";
		while (std::getline(shaderStream, line))
			shaderCode += "\n" + line;

		shaderStream.close();
	}
	else
		return false;

	GLuint shaderObj = glCreateShader(shaderType);

	if (shaderObj == 0)
		return false;

	m_shaderObjList.push_back(shaderObj);

	const GLchar* p[1];
	p[0] = shaderCode.c_str();
	GLint lengths[1] = { (GLuint)shaderCode.size() };

	glShaderSource(shaderObj, 1, p, lengths);

	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
		OutputDebugStringA(infoLog);
	}

	glAttachShader(m_shaderProg, shaderObj);

	return true;
}


bool CTechnique::Finialise()
{
	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(m_shaderProg);

	glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &success);

	if (success == 0) {
		glGetProgramInfoLog(m_shaderProg, sizeof(errorLog), NULL, errorLog);
		OutputDebugString(errorLog);
		return false;
	}

	glValidateProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(m_shaderProg, sizeof(errorLog), NULL, errorLog);
		OutputDebugString(errorLog);
		return false;
	}

	for (auto it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++) 
		glDeleteShader(*it);
	
	m_shaderObjList.clear();

	return  true;
}


void CTechnique::Enable()
{
	glUseProgram(m_shaderProg);
}


GLint CTechnique::GetUniformLocation(const char* pUniformName)
{
	GLuint location = glGetUniformLocation(m_shaderProg, pUniformName);

	return location;
}


GLint CTechnique::GetProgramParam(GLint param)
{
	GLint ret;
	glGetProgramiv(m_shaderProg, param, &ret);
	return ret;
}