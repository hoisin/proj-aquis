#include "CShaderManager.h"


CShaderManager::CShaderManager()
{
}


CShaderManager::~CShaderManager()
{
	CleanUp();
}


CShader* CShaderManager::CreateShader(const std::string& shaderID, const std::string &vertexShaderPath, 
		const std::string &fragmentShaderPath)
{
	CShader* pShader = new CShader;

	GLuint out = 0;

	if(!pShader->LoadShader(vertexShaderPath, fragmentShaderPath, out))
		return NULL;

	m_shaderMap.insert(std::pair<std::string, CShader*>(shaderID, pShader));
}



CShader* CShaderManager::GetShader(const std::string& shaderID)
{
	std::map<std::string, CShader*>::iterator it = m_shaderMap.find(shaderID);

	if(it == m_shaderMap.end())
		return NULL;

	return it->second;
}


void CShaderManager::RemoveShader(const std::string& shaderID)
{
	std::map<std::string, CShader*>::iterator it = m_shaderMap.find(shaderID);

	if(it != m_shaderMap.end())
	{
		delete it->second;
		it->second = NULL;
		m_shaderMap.erase(it);
	}
}


void CShaderManager::CleanUp()
{
	std::map<std::string, CShader*>::iterator it = m_shaderMap.begin();

	for(; it != m_shaderMap.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}

	m_shaderMap.clear();
}