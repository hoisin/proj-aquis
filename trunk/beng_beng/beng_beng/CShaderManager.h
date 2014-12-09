//--------------------------------------------------------------------------
//
//	08/12/2014
//
//	Shader manager..
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------


#ifndef __CSHADERMANAGER_H__
#define __CSHADERMANAGER_H__

#include <map>
#include <string>
#include "CShader.h"

class CShaderManager
{
public:
	CShaderManager();
	~CShaderManager();

	CShader* CreateShader(const std::string& shaderID, const std::string &vertexShaderPath, 
		const std::string &fragmentShaderPath);

	CShader* GetShader(const std::string& shaderID);

	void RemoveShader(const std::string& shaderID);

	void CleanUp();

private:
	std::map<std::string, CShader*> m_shaderMap;
};

#endif