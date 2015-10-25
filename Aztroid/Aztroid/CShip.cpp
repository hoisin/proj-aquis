#include "CShip.h"
#include "Utility.h"
#include "CAztroid.h"
#include "CBullet.h"

CShip::CShip() : m_rotSpeed(0), m_currentRotation(0), m_prevRotation(0), m_bFire(false)
{
	m_dir = gcmath::Vec2<float>(0.f, 0.f);

	for (int i = 0; i < eTotalDir; i++)
		m_updateDir[i] = false;
}



CShip::~CShip()
{
}


void CShip::VUpdate(float deltaT, CAztroid* pGame)
{
	if (m_bFire) {
		CBullet* pBullet = (CBullet*)pGame->SpawnBullet(m_cBox, m_pos, m_dir);
		m_bFire = false;

		// Ships get updated after bullets.
		// Therefore invoke update of spawned bullets ourselves
		pBullet->VUpdate(deltaT, pGame);
	}

	gcmath::Vec2<float> moveVec = m_dir * (float)m_speed;

	// Update previous position and rotation
	m_prevRotation = m_currentRotation;
	m_prevPos = m_pos;

	if (m_updateDir[eLeft])
		m_currentRotation -= m_rotSpeed;

	if (m_updateDir[eRight])
		m_currentRotation += m_rotSpeed;

	// Calculate new direction
	m_dir.x = (float)cos(gcutility::GetRadians((float)m_currentRotation));
	m_dir.y = (float)sin(gcutility::GetRadians((float)m_currentRotation));

	if (m_updateDir[eUp]) {	
		m_pos.x += moveVec.x;
		m_pos.y += moveVec.y;
	}

	if (m_updateDir[eDown]) {
		m_pos.x -= moveVec.x;
		m_pos.y -= moveVec.y;
	}

	gcmath::Rect<int> shipWorldCBox = m_cBox;
	shipWorldCBox.left += m_pos.x;
	shipWorldCBox.right += m_pos.x;
	shipWorldCBox.top += m_pos.y;
	shipWorldCBox.bottom += m_pos.y;

	if (!pGame->GetWorldDimension().IsContained(shipWorldCBox)) {
		m_pos = m_prevPos;
	}

	// Clamp rotation value between -360 & 360 degrees
	gcutility::ClampValue(m_prevRotation, -360, 360);
	gcutility::ClampValue(m_currentRotation, -360, 360);

	for (int i = 0; i < eTotalDir; i++)
		m_updateDir[i] = false;


}


void CShip::VDraw(float deltaT, CGfx* pGfx, int updateTick)
{
	gcmath::Vec2<float> interp;
	int interpRot = 0;
	float lerp = deltaT / (float)updateTick;
	
	interp.x = gcutility::LinearInterpolate(m_prevPos.x, m_pos.x, lerp);
	interp.y = gcutility::LinearInterpolate(m_prevPos.y, m_pos.y, lerp);
	interpRot = gcutility::LinearInterpolate(m_prevRotation, m_currentRotation, lerp);

	pGfx->DrawTexture(m_spriteID, (int)interp.x, (int)interp.y,
		gcutility::CreateSDLRect(m_cBox), interpRot);
}


void CShip::VMove(EMoveDir dir)
{
	if (dir < eTotalDir)
		m_updateDir[dir] = true;
}


void CShip::VFire()
{
	m_bFire = true;
}


void CShip::SetRotationSpeed(int rotSpeed)
{
	m_rotSpeed = rotSpeed;
}


void CShip::SetCurrentRotation(int rotVal)
{
	m_currentRotation = rotVal;
}