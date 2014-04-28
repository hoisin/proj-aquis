//--------------------------------------------------------------------------
//
//	11/04/2014
//
//	Base camera class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include <glm\glm.hpp>

#define PI 3.14159265

class CCamera
{
public:
	CCamera(const glm::vec3 &pos, const glm::vec3 &up, const glm::vec3 &look, 
		float zNear, float zFar, float aspectRatio, float fovV);
	CCamera();
	virtual ~CCamera();

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

protected:
	float ResetAngle180(float angle);		//resets angle back to 0 when over 180 or under -180
	float RestrictAngle90(float angle);		//restricts angle to 90 - (-90)

public:
	// View matrix stuff
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_look;

	// Projection matrix stuff
	float m_zNear;
	float m_zFar;
	float m_aspectRatio;
	float m_fovV;
};

#endif