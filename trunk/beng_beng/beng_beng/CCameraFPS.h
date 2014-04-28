//--------------------------------------------------------------------------
//
//	11/04/2014
//
//	FPS camera class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CCAMERAFPS_H__
#define __CCAMERAFPS_H__

#include "CCamera.h"

class CCameraFPS : public CCamera
{
public:
	CCameraFPS(const glm::vec3 &pos, const glm::vec3 &up, const glm::vec3 &look, 
		float zNear, float zFar, float aspectRatio, float fovV);
	~CCameraFPS();

	void MoveForward(float amt);
	void MoveBack(float amt);
	void StrafeLeft(float amt);
	void StrafeRight(float amt);

	void RotateYaw(float degrees);
	void RotatePitch(float degrees);

public:
	float m_horizontalAngle;
	float m_verticalAngle;
};

#endif