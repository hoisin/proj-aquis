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
	CLight(void);
	virtual ~CLight(void);

	ELightType GetType(void) { m_type; }

public:
	glm::vec3 m_col;
	ELightType m_type;
};


class CAmbientLight : public CLight
{
public:
	CAmbientLight();
	~CAmbientLight();

public:
	float m_intensity;
};


class CDirectionalLight : CLight
{
public:
	CDirectionalLight();
	~CDirectionalLight();

public:
	float m_intensity;
	glm::vec3 m_direction;
};


class CPointLight : public CLight
{
public:
	CPointLight();
	~CPointLight();

public:
	glm::vec3 m_position;
	float m_intensity;
	float m_attenuation;
};


class CSpotLight : CLight
{
public:
	CSpotLight();
	~CSpotLight();

public:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	float m_coneAngle;
	float m_intensity;
	float m_attenuation;
};

#endif