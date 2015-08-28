//--------------------------------------------------------------------------
//
//	11/03/2015
//
//	Light manager
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------


#include "CLightManager.h"
#include "CLight.h"


CLightManager::CLightManager(void)
{
}


CLightManager::~CLightManager(void)
{
	for (auto it : m_mpLights) {
		delete it.second;
		it.second = nullptr;
	}
}


bool CLightManager::CreateDirectionalLight(const glm::vec3 &pos, float intensity,
	float attenuation, const glm::vec3& col)
{
	return true;
}