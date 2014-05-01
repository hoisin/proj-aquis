#include "CCamera.h"
#include <glm\gtc\matrix_transform.hpp>

CCamera::CCamera(const glm::vec3 &pos, const glm::vec3 &up, const glm::vec3 &look, 
	float zNear, float zFar, float aspectRatio, float fovV) : m_position(pos), m_up(up), m_look(look),
	m_zNear(zNear), m_zFar(zFar), m_aspectRatio(aspectRatio), m_fovV(fovV)
{
}


CCamera::CCamera() : m_position(glm::vec3(0,0,0)), m_up(glm::vec3(0,0,0)), m_look(glm::vec3(0,0,0)),
	m_zNear(0), m_zFar(0), m_aspectRatio(0), m_fovV(0)
{
}


CCamera::~CCamera()
{
}


//------------------------------------------------------------------
//
//	GetProjectionMatrix(..)
//
//	Calculates and returns the projection matrix based on the camera
//	settings.
//	
//	Note: Optimisation possible by storing the calulated matrix and 
//	only recalculate when camera settings are changed
//
//------------------------------------------------------------------
glm::mat4 CCamera::GetProjectionMatrix()
{
	// Manual calculation of projection matrix
	//float h, w, q;

	//w = (float)1/tan(m_fovV*0.5);	// 1/tan(x) == cot(x)
	//h = (float)1/tan(m_fovV*0.5);	// 1/tan(x) == cot(x)
	//q = m_zFar/(m_zFar - m_zNear);

	//glm::mat4 projMat = glm::mat4(1.0f);

	//projMat[0].x = w;
	//projMat[1].y = h;
	//projMat[2].z = q;
	//projMat[3].z = -q*m_zNear;
	//projMat[2].w = 1;

	//return projMat;

	// Consider using radians for FoV
	return glm::perspective(m_fovV, m_aspectRatio, m_zNear, m_zFar);
}


//------------------------------------------------------------------
//
//	GetViewMatrix(..)
//
//	Calculates and returns the view matrix based on the camera
//	settings.
//	
//	Note: Optimisation possible by storing the calulated matrix and 
//	only recalculate when camera settings are changed
//
//------------------------------------------------------------------
glm::mat4 CCamera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_look, m_up);
}


//------------------------------------------------------------------
//
//	ResetAngle180(..)
//
//	Params:
//	angle	-	angle in degrees
//
//	Calulates the passed angle to be in between -180 to 180
//
//------------------------------------------------------------------
float CCamera::ResetAngle180(float angle)
{
	float temp = angle;
	if(angle > (180 * (PI/180)))
		temp +=  (float)(-360 * (PI/180));

	if(angle < (-180 * (PI/180)))
		temp +=  (float)(360 * (PI/180));

	return temp;
}


//------------------------------------------------------------------
//
//	RestrictAngle90(..)
//
//	Params:
//	angle	-	angle in degrees
//
//	Calulates the passed angle to be in between -90 to 90
//
//------------------------------------------------------------------
float CCamera::RestrictAngle90(float angle)
{
	float temp = angle;

	// Using 89.99 to avoid gimbal lock
	float maxBound = (float)(89.99*(PI/180));
	float minBound = (float)(-89.99*(PI/180));

	if(angle > maxBound)
		temp = maxBound;

	if(angle < minBound)
		temp = minBound;

	return temp;
}