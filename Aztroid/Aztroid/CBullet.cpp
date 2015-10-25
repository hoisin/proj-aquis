#include "CBullet.h"
#include "Utility.h"

CBullet::CBullet() : m_updateCount(0), m_lifeTime(0)
{
}



CBullet::~CBullet()
{
}


void CBullet::VUpdate(float deltaT, CAztroid* pGame)
{
	gcmath::Vec2<float> moveVec = m_dir * (float)m_speed;

	m_prevPos = m_pos;
	m_pos += moveVec;

	gcmath::Rect<int> bulletWorldCBox = m_cBox;
	bulletWorldCBox.left += m_pos.x;
	bulletWorldCBox.right += m_pos.x;
	bulletWorldCBox.top += m_pos.y;
	bulletWorldCBox.bottom += m_pos.y;

	if (!pGame->GetWorldDimension().IsContained(bulletWorldCBox)) {
		m_pos = m_prevPos;
		m_dir *= -1.f;
	}

	m_updateCount += deltaT;

	if (m_updateCount > m_lifeTime) {
		m_updateCount = 0;
		m_bActive = false;
	}
}


void CBullet::VDraw(float deltaT, CGfx* pGfx, int updateTick)
{
	gcmath::Vec2<float> interp;
	int interpRot = 0;
	float lerp = deltaT / (float)updateTick;

	interp.x = gcutility::LinearInterpolate(m_prevPos.x, m_pos.x, lerp);
	interp.y = gcutility::LinearInterpolate(m_prevPos.y, m_pos.y, lerp);

	pGfx->DrawTexture(m_spriteID, (int)interp.x, (int)interp.y, gcutility::CreateSDLRect(m_cBox));
}


void CBullet::VMove(EMoveDir dir)
{
}


void CBullet::SetLifeTime(int time)
{
	m_lifeTime = time;
}