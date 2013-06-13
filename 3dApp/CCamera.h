/*
	Date: 01/02/2013
	Base Camera class
*/

#pragma once
#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include <DirectXMath.h>

class CCamera
{
protected:
	float m_posX,	m_posY,		m_posZ;
	float m_lookX,	m_lookY,	m_lookZ;
	float m_upX,	m_upY,		m_upZ;
	float m_rotX,	m_rotY,		m_rotZ;
	float m_fov,	m_aspect,	m_near,		m_far;

	//DirectX::XMFLOAT4X4 m_viewMat;

public:
	CCamera(void);
	CCamera(const CCamera& other);
	virtual ~CCamera(void);

	void SetProjection(float fov, float aspect, float near, float far);
	void SetPosition(float x, float y, float z);
	void SetLookAt(float x, float y, float z);
	void SetUp(float x, float y, float z);
	void SetRotation(float yaw, float pitch, float roll);

	virtual DirectX::XMFLOAT4X4 VGetProjMatrix(void);
	virtual DirectX::XMFLOAT4X4 VGetViewMatrix(void); 
};

#endif