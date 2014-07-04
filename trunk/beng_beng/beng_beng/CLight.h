//--------------------------------------------------------------------------
//
//	04/07/2014
//
//	Light class, more of a data storage struct
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CLIGHT_H__
#define __CLIGHT_H__

#include "GfxDefs.h"

class CLight
{
public:
	CLight(ELightType type, const glm::vec3 &pos = glm::vec3(0, 0, 0), const glm::vec3 &col = glm::vec3(1, 1, 1), 
		float intensity = 0, float attenuation = 0, float coneAngle = 0);
	CLight(void);
	~CLight(void);

	ELightType GetType(void) { m_type; }

public:
	glm::vec3 m_pos;
	glm::vec3 m_col;
	float m_intensity;

	float m_attenuation;	// Distance light will reach
	float m_coneAngle;		// For spot light type
	
	ELightType m_type;
};

#endif