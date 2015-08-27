#include "CFwdLighting.h"

CFwdLighting::CFwdLighting(const std::string& vertexShaderPath,
	const std::string& fragmentShaderPath)
{
	m_vertexShaderPath = vertexShaderPath;
	m_fragementShaderPath = fragmentShaderPath;
}


CFwdLighting::~CFwdLighting()
{
}


bool CFwdLighting::VInit()
{
	if (!CTechnique::VInit())
		return false;

	if (!AddShader(GL_VERTEX_SHADER, m_vertexShaderPath.c_str()))
		return false;

	if (!AddShader(GL_FRAGMENT_SHADER, m_fragementShaderPath.c_str()))
		return false;

	if (!Finialise())
		return false;

	m_projViewMatLoc = GetUniformLocation("projViewMatrix");
	m_worldMatLoc = GetUniformLocation("worldMatrix");
	m_diffuseTexSamplerLoc = GetUniformLocation("diffuseTextureSampler");

	if (m_projViewMatLoc < 0 || m_worldMatLoc < 0 || m_diffuseTexSamplerLoc < 0)
		return false;

	return true;
}


void CFwdLighting::SetProjViewMatrix(const glm::mat4& projViewMat)
{
	glUniformMatrix4fv(m_projViewMatLoc, 1, GL_FALSE, (const GLfloat*)&projViewMat[0][0]);
}


void CFwdLighting::SetWorldMatrix(const glm::mat4& worldMat)
{
	glUniformMatrix4fv(m_worldMatLoc, 1, GL_FALSE, (const GLfloat*)&worldMat[0][0]);
}


void CFwdLighting::SetDiffuseTexture(GLuint textureID)
{
	glUniform1i(m_diffuseTexSamplerLoc, textureID);
}