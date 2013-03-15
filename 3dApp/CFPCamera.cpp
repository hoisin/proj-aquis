#include "CFPCamera.h"

CFPCamera::CFPCamera(void)
{
}


CFPCamera::CFPCamera(const CFPCamera& other)
{
}


CFPCamera::~CFPCamera(void)
{
}


void CFPCamera::SetViewDirection(float x, float y, float z)
{
	// Ensure its a unit vector
	float mod = sqrt((x * x) + (y * y) + (z * z));

	m_viewX = x / mod;
	m_viewY = y / mod;
	m_viewZ = z / mod;
}


void CFPCamera::SetRight(float x, float y, float z)
{
	// Ensure its a unit vector
	float mod = sqrt((x * x) + (y * y) + (z * z));

	m_rightX = x;
	m_rightY = y;
	m_rightZ = z;
}


void CFPCamera::MoveForward(float value)
{
	DirectX::XMFLOAT3 viewDir;

	viewDir.x = m_viewX * value;
	viewDir.y = m_viewY * value;
	viewDir.z = m_viewZ * value;

	DirectX::XMFLOAT3 position;

	// Setup the position of the camera in the world.
	position.x = m_posX;
	position.y = m_posY;
	position.z = m_posZ;

	DirectX::XMFLOAT4X4 rotationMatrix;
	float yaw, pitch, roll;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	yaw = m_rotX * 0.0174532925f;
	pitch   = m_rotY * 0.0174532925f;
	roll  = m_rotZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMStoreFloat4x4(&rotationMatrix, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	DirectX::XMStoreFloat3(&viewDir, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&viewDir), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	// Translate the rotated camera position to the location of the viewer.
	DirectX::XMStoreFloat3(&position, 
		DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&viewDir)));

	// Get updated position
	m_posX = position.x;
	m_posY = position.y;
	m_posZ = position.z;
}


void CFPCamera::MoveBackward(float value)
{
	DirectX::XMFLOAT3 viewDir;

	viewDir.x = m_viewX * value;
	viewDir.y = m_viewY * value;
	viewDir.z = m_viewZ * value;

	DirectX::XMFLOAT3 position;

	// Setup the position of the camera in the world.
	position.x = m_posX;
	position.y = m_posY;
	position.z = m_posZ;

	DirectX::XMFLOAT4X4 rotationMatrix;
	float yaw, pitch, roll;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	yaw = m_rotX * 0.0174532925f;
	pitch   = m_rotY * 0.0174532925f;
	roll  = m_rotZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMStoreFloat4x4(&rotationMatrix, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	DirectX::XMStoreFloat3(&viewDir, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&viewDir), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	// Translate the rotated camera position to the location of the viewer.
	DirectX::XMStoreFloat3(&position, 
		DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&viewDir)));

	// Get updated position
	m_posX = position.x;
	m_posY = position.y;
	m_posZ = position.z;
}


void CFPCamera::StrafeLeft(float value)
{
	DirectX::XMFLOAT3 right;

	right.x = m_rightX * value;
	right.y = m_rightY * value;
	right.z = m_rightZ * value;

	DirectX::XMFLOAT3 position;

	// Setup the position of the camera in the world.
	position.x = m_posX;
	position.y = m_posY;
	position.z = m_posZ;

	DirectX::XMFLOAT4X4 rotationMatrix;
	float yaw, pitch, roll;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	yaw = m_rotX * 0.0174532925f;
	pitch = m_rotY * 0.0174532925f;
	roll  = m_rotZ * 0.0174532925f;;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMStoreFloat4x4(&rotationMatrix, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	DirectX::XMStoreFloat3(&right, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&right), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	// Translate the rotated camera position to the location of the viewer.
	DirectX::XMStoreFloat3(&position, 
		DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&right)));

	// Get updated position
	m_posX = position.x;
	m_posY = position.y;
	m_posZ = position.z;
}


void CFPCamera::StrafeRight(float value)
{
	DirectX::XMFLOAT3 right;

	right.x = m_rightX * value;
	right.y = m_rightY * value;
	right.z = m_rightZ * value;

	DirectX::XMFLOAT3 position;

	// Setup the position of the camera in the world.
	position.x = m_posX;
	position.y = m_posY;
	position.z = m_posZ;

	DirectX::XMFLOAT4X4 rotationMatrix;
	float yaw, pitch, roll;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	yaw = m_rotX * 0.0174532925f;
	pitch = m_rotY * 0.0174532925f;
	roll  = m_rotZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMStoreFloat4x4(&rotationMatrix, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	DirectX::XMStoreFloat3(&right, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&right), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	// Translate the rotated camera position to the location of the viewer.
	DirectX::XMStoreFloat3(&position, 
		DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&right)));

	// Get updated position
	m_posX = position.x;
	m_posY = position.y;
	m_posZ = position.z;
}


void CFPCamera::RotatePitch(float degreeVal)
{
	m_rotY += degreeVal;
}

	
void CFPCamera::RotateYaw(float degreeVal)
{
	m_rotX += degreeVal;
}


DirectX::XMFLOAT4X4 CFPCamera::VGetViewMatrix(void)
{
	DirectX::XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	DirectX::XMFLOAT4X4 rotationMatrix, viewMat;

	DirectX::XMFLOAT3 viewDir;

	viewDir.x = m_viewX;
	viewDir.y = m_viewY;
	viewDir.z = m_viewZ;

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
	pitch  = m_rotY * 0.0174532925f;
	roll  = m_rotZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMStoreFloat4x4(&rotationMatrix, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll));

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	DirectX::XMStoreFloat3(&viewDir, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&viewDir), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	DirectX::XMStoreFloat3(&up, 
		DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&up), DirectX::XMLoadFloat4x4(&rotationMatrix)));

	// Translate the rotated camera position to the location of the viewer.
	DirectX::XMStoreFloat3(&lookAt, 
		DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&viewDir)));

	// Finally create the view matrix from the three updated vectors.
	DirectX::XMStoreFloat4x4(&viewMat, 
		DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&lookAt), DirectX::XMLoadFloat3(&up)));

	return viewMat;

}
