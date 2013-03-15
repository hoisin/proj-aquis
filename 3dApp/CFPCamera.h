/*
	11/02/2013
	First Person camera class
*/

#ifndef __CFPCAMERA_H__
#define __CFPCAMREA_H__

#include "CCamera.h"

class CFPCamera : public CCamera
{
protected:
	float m_viewX, m_viewY, m_viewZ;
	float m_rightX, m_rightY, m_rightZ;

public:
	CFPCamera(void);
	CFPCamera(const CFPCamera& other);
	~CFPCamera(void);

	void SetViewDirection(float x, float y, float z);
	void SetRight(float x, float y, float z);

	void MoveForward(float value);
	void MoveBackward(float value);
	void StrafeLeft(float value);
	void StrafeRight(float value);

	void RotatePitch(float degreeVal);
	void RotateYaw(float degreeVal);

	virtual DirectX::XMFLOAT4X4 VGetViewMatrix(void); 
};

#endif