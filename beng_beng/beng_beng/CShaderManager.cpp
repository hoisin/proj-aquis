#include "CShaderManager.h"
#include "CFwdLighting.h"

CShaderManager::CShaderManager()
{
}


CShaderManager::~CShaderManager()
{
	CleanUp();
}


CTechnique* CShaderManager::CreateFwdLightShader(const std::string& shaderID, const std::string &vertexShaderPath,
		const std::string &fragmentShaderPath)
{
	CFwdLighting* pShader = new CFwdLighting(vertexShaderPath, fragmentShaderPath);

	if (!pShader->VInit())
		return nullptr;

	m_shaderMap.insert(std::pair<std::string, CTechnique*>(shaderID, pShader));

	return pShader;
}



CTechnique* CShaderManager::GetShader(const std::string& shaderID)
{
	auto it = m_shaderMap.find(shaderID);

	if(it != m_shaderMap.end())
		return it->second;

	return NULL;
}


void CShaderManager::RemoveShader(const std::string& shaderID)
{
	auto it = m_shaderMap.find(shaderID);

	if(it != m_shaderMap.end())
	{
		delete it->second;
		it->second = NULL;
		m_shaderMap.erase(it);
	}
}


void CShaderManager::CleanUp()
{
	auto it = m_shaderMap.begin();

	for(; it != m_shaderMap.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}

	m_shaderMap.clear();
}