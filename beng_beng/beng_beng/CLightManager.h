//--------------------------------------------------------------------------
//
//	11/03/2015
//
//	Light manager
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CLIGHTMANAGER_H__
#define __CLIGHTMANAGER_H__

#include "GfxDefs.h"

#include <map>

class CLight;

class CLightManager
{
public:
	CLightManager(void);
	~CLightManager(void);

	bool CreateDirectionalLight(const glm::vec3 &pos, float intensity,
		float attenuation, const glm::vec3& col = glm::vec3(1, 1, 1));

	bool CreatePointLight();
	bool CreateSpotLigh();

private:
	std::map<std::string, CLight*> m_mpLights;
};

#endif