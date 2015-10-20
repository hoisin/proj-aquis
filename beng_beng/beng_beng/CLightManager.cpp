//--------------------------------------------------------------------------
//
//	11/03/2015
//
//	Light manager
//
//	Author: Matt � 2015
//
//--------------------------------------------------------------------------


#include "CLightManager.h"

CLightManager::CLightManager(void)
{
}


CLightManager::~CLightManager(void)
{
	for (int count = 0; count < (int)m_vLights.size(); count++) {
		if (m_vLights[count]) {
			delete m_vLights[count];
			m_vLights[count] = nullptr;
		}
	}

	m_vLights.clear();
}


bool CLightManager::CreateAmbientLight(const glm::vec3& colour, float intensity)
{
	// Create ambient light if non exist
	if (!m_bAmbLight) {

		auto newAmbLight = new SLight;
		newAmbLight->type = ELightType::eLightAmb;
		newAmbLight->colour = colour;
		newAmbLight->intensity = intensity;

		// Flag as already created light
		m_bAmbLight = true;

		return true;
	}

	// Fail if already an ambient light created
	return false;
}


bool CLightManager::CreateDirectionalLight(const glm::vec3& colour, float intensity, const glm::vec3& direction)
{
	return true;
}


bool CLightManager::CreatePointLight(const glm::vec3& colour, float intensity, const glm::vec3& position, float attenuation)
{
	return true;
}


bool CLightManager::CreateSpotLight(const glm::vec3& colour, float intensity, const glm::vec3& position, float attenuation,
	float coneAngle, float coneAttenuation)
{
	return true;
}
