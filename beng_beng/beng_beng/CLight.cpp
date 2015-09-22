#include "CLight.h"


CLight::CLight() : m_col(glm::vec3(0, 0, 0)), m_type(eLightNone)
{
}


CLight::~CLight()
{
}



CAmbientLight::CAmbientLight() : m_intensity(0)
{
}


CAmbientLight::~CAmbientLight()
{
}


CDirectionalLight::CDirectionalLight() : m_intensity(0), m_direction(glm::vec3(0, 0, 0))
{
}


CDirectionalLight::~CDirectionalLight()
{
}


CPointLight::CPointLight() : m_position(glm::vec3(0, 0, 0)), m_intensity(0), m_attenuation(0)
{
}


CPointLight::~CPointLight()
{
}


CSpotLight::CSpotLight() : m_position(glm::vec3(0, 0, 0)), m_direction(glm::vec3(0, 0, 0)),
	m_coneAngle(0), m_intensity(0), m_attenuation(0)
{
}


CSpotLight::~CSpotLight()
{
}