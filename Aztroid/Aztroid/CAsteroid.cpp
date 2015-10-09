#include "CAsteroid.h"
#include "Utility.h"

CAsteroid::CAsteroid()
{
}



CAsteroid::~CAsteroid()
{
}


void CAsteroid::VUpdate(float deltaT, CAztroid* pGame)
{
}


void CAsteroid::VDraw(float deltaT, CGfx* pGfx, int updateTick)
{
	gcmath::Vec2<float> interp;
	int interpRot = 0;
	float lerp = deltaT / (float)updateTick;

	interp.x = gcutility::LinearInterpolate(m_prevPos.x, m_pos.x, lerp);
	interp.y = gcutility::LinearInterpolate(m_prevPos.y, m_pos.y, lerp);

	pGfx->DrawTexture(m_spriteID, (int)interp.x, (int)interp.y);
}


void CAsteroid::VMove(EMoveDir dir)
{
}