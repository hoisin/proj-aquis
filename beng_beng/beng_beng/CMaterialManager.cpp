#include "CMaterialManager.h"
#include "CMaterial.h"

CMaterialManager::CMaterialManager(void)
{

}


CMaterialManager::~CMaterialManager(void)
{

}


void CMaterialManager::AddMaterial(const std::string& materialID,
	const CMaterial& material)
{
	std::map<std::string, CMaterial*>::iterator it = m_materials.find(materialID);


}


CMaterial* CMaterialManager::GetMaterial(const std::string& materialID)
{
	std::map<std::string, CMaterial*>::iterator it = m_materials.find(materialID);

	if (it != m_materials.end())
		return it->second;

	return NULL;
}


