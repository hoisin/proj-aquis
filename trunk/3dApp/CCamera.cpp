#include "CCamera.h"

CCamera::CCamera(void)
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_rotZ = 0.0f;

}


CCamera::CCamera(const CCamera& other)
{
}


CCamera::~CCamera(void)
{
}


void CCamera::SetProjection(float fov, float aspect, float near, float far)
{
	m_fov = fov;
	m_aspect = aspect;
	m_near = near;
	m_far = far;
}


void CCamera::SetPosition(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

void CCamera::SetLookAt(float x, float y, float z)
{
	m_lookX = x;
	m_lookY = y;
	m_lookZ = z;
}


void CCamera::SetUp(float x, float y, float z)
{
	m_upX = x;
	m_upY = y;
	m_upZ = z;
}
	

void CCamera::SetRotation(float yaw, float pitch, float roll)
{
	m_rotX = yaw;
	m_rotY = pitch;
	m_rotZ = roll;
}


DirectX::XMFLOAT4X4 CCamera::VGetProjMatrix(void)
{
	DirectX::XMFLOAT4X4 projMat;

	DirectX::XMStoreFloat4x4(&projMat, DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far));

	return projMat;
}

	
DirectX::XMFLOAT4X4 CCamera::VGetViewMatrix(void)
{
	DirectX::XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	DirectX::XMFLOAT4X4 rotationMatrix, viewMat;


	// Setup the vector that points upwards.
	up.x = m_upX;
	up.y = m_upY;
	up.z = m_upZ;

	// Setup the position of the camera in the world.
	position.x = m_posX;
	position.y = m_posY;
	position.z = m_posZ;

	// Setup where the camera is looking by default.
	lookAt.x = m_lookX;
	lookAt.y = m_lookY;
	lookAt.z = m_lookZ;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	yaw = m_rotX * 0.0174532925f;
	pitch   = m_rotY * 0.0174532925f;
	roll  = m_rotZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMStoreFloat4x4(&rotationMatrix, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	DirectX::XMStoreFloat3(&lookAt, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&lookAt), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	DirectX::XMStoreFloat3(&up, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&up), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	// Translate the rotated camera position to the location of the viewer.
	//DirectX::XMStoreFloat3(&lookAt, 
		//DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&lookAt)));

	// Finally create the view matrix from the three updated vectors.
	DirectX::XMStoreFloat4x4(&viewMat, 
		DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&lookAt), DirectX::XMLoadFloat3(&up)));

	return viewMat;

}
