#include "CMaterialManager.h"
#include "CMaterial.h"

CMaterialManager::CMaterialManager(void)
{

}


CMaterialManager::~CMaterialManager(void)
{
	std::map<std::string, CMaterial*>::iterator it;

	for (it = m_materials.begin(); it != m_materials.end(); it++) {
		if (it->second) {
			delete it->second;
			it->second = NULL;
		}
	}

	m_materials.empty();
}


void CMaterialManager::AddMaterial(const std::string& materialID,
	CMaterial* material)
{
	std::map<std::string, CMaterial*>::iterator it = m_materials.find(materialID);

	if (it == m_materials.end()) {
		m_materials.insert(std::pair<std::string, CMaterial*>(materialID, material));
	}
}


CMaterial* CMaterialManager::GetMaterial(const std::string& materialID)
{
	std::map<std::string, CMaterial*>::iterator it = m_materials.find(materialID);

	if (it != m_materials.end())
		return it->second;

	return NULL;
}


