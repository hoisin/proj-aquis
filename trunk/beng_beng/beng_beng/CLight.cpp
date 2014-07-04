#include "CLight.h"


CLight::CLight(ELightType type, const glm::vec3 &pos, const glm::vec3 &col, float intensity, float attenuation, float coneAngle)
	: m_type(type), m_pos(pos), m_col(col), m_intensity(intensity), m_attenuation(attenuation), m_coneAngle(coneAngle)
{
}

CLight::CLight(void) : m_type(eLightNone), m_pos(glm::vec3(0, 0, 0)), m_col(glm::vec3(0, 0, 0)), m_intensity(0), m_attenuation(0), m_coneAngle(0)
{
}


CLight::~CLight()
{
}


