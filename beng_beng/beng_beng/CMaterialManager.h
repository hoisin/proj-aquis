//--------------------------------------------------------------------------
//
//	17/04/2015
//
//	Material manager
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------


#ifndef __CMATERIALMANAGER_H__
#define __CMATERIALMANAGER_H__

#include <string>
#include <map>

class CMaterial;

class CMaterialManager
{
public:
	CMaterialManager(void);
	~CMaterialManager(void);

	void AddMaterial(const std::string& materialID, CMaterial* material);

	CMaterial* GetMaterial(const std::string& materialID);

protected:
	std::map<std::string, CMaterial*> m_materials;
};

#endif