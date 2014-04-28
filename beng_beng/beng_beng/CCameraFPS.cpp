#include "CCameraFPS.h"


CCameraFPS::CCameraFPS(const glm::vec3 &pos, const glm::vec3 &up, const glm::vec3 &look, 
		float zNear, float zFar, float aspectRatio, float fovV) :
	CCamera(pos, up, look, zNear, zFar, aspectRatio, fovV)
{
}


CCameraFPS::~CCameraFPS()
{
}


void CCameraFPS::MoveForward(float amt)
{
	if(amt < 0)
		amt *= -1;

	//view direction
	float viewDirX = m_look.x - m_position.x;
	float viewDirY = m_look.y - m_position.y;
	float viewDirZ = m_look.z - m_position.z;

	m_position.x += amt*viewDirX;
	m_position.y += amt*viewDirY;	//remove this to prevent player moving up when facing up
	m_position.z += amt*viewDirZ;

	//left handed coordinate system
	//calculate interest
	m_look.x = m_position.x + sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y + sin(m_verticalAngle);
	m_look.z = m_position.z + cos(m_horizontalAngle)*cos(m_verticalAngle); 
}


void CCameraFPS::MoveBack(float amt)
{
	if(amt > 0)
		amt *= -1;

	//view direction
	float viewDirX = m_look.x - m_position.x;
	float viewDirY = m_look.y - m_position.y;
	float viewDirZ = m_look.z - m_position.z;

	m_position.x += amt*viewDirX;
	m_position.y += amt*viewDirY;	//remove this to prevent player moving up when facing up
	m_position.z += amt*viewDirZ;

	//left handed coordinate system
	//calculate interest
	m_look.x = m_position.x + sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y + sin(m_verticalAngle);
	m_look.z = m_position.z + cos(m_horizontalAngle)*cos(m_verticalAngle); 
}


void CCameraFPS::StrafeLeft(float amt)
{
	if(amt > 0)
		amt *= -1;

	//view direction
	float viewDirX = m_look.x - m_position.x;
	float viewDirZ = m_look.z - m_position.z;

	//left handed coordinate system
	m_position.x -= cos(m_horizontalAngle)*amt;
	//m_position.m_y += amt*m_look.y;
	m_position.z += sin(m_horizontalAngle)*amt;

	//left handed coordinate system
	//calculate interest
	m_look.x = m_position.x + sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y + sin(m_verticalAngle);
	m_look.z = m_position.z + cos(m_horizontalAngle)*cos(m_verticalAngle); 
}


void CCameraFPS::StrafeRight(float amt)
{
	if(amt < 0)
		amt *= -1;

	//view direction
	float viewDirX = m_look.x - m_position.x;
	float viewDirZ = m_look.z - m_position.z;

	//left handed coordinate system
	m_position.x -= cos(m_horizontalAngle)*amt;
	//m_position.m_y += amt*m_look.y;
	m_position.z += sin(m_horizontalAngle)*amt;

	//left handed coordinate system
	//calculate interest
	m_look.x = m_position.x + sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y + sin(m_verticalAngle);
	m_look.z = m_position.z + cos(m_horizontalAngle)*cos(m_verticalAngle); 
}


void CCameraFPS::RotateYaw(float degrees)
{
	m_horizontalAngle += (float)(degrees * (PI/180));

	m_horizontalAngle = ResetAngle180(m_horizontalAngle);

	//left handed coordinate system
	//calculate interest
	m_look.x = m_position.x + sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y + sin(m_verticalAngle);
	m_look.z = m_position.z + cos(m_horizontalAngle)*cos(m_verticalAngle); 
}


void CCameraFPS::RotatePitch(float degress)
{
	m_verticalAngle -= (float)(degress * (PI/180));

	m_verticalAngle= RestrictAngle90(m_verticalAngle);

	//left handed coordinate system
	//calculate interest
	m_look.x = m_position.x + sin(m_horizontalAngle)*cos(m_verticalAngle);
	m_look.y = m_position.y + sin(m_verticalAngle);
	m_look.z = m_position.z + cos(m_horizontalAngle)*cos(m_verticalAngle); 
}

