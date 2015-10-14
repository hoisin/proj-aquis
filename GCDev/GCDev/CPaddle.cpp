#include "CPaddle.h"

CPaddle::CPaddle() : m_leftMove(0), m_rightMove(0)
{
}


CPaddle::~CPaddle()
{
}


void CPaddle::VUpdate(unsigned int deltaT, CBreakOut* pGame)
{
	m_prevPosition = m_position;

	if (m_leftMove != 0) {
		m_position.x += m_leftMove;
		m_leftMove = 0;
	}

	if (m_rightMove != 0) {
		m_position.x += m_rightMove;
		m_rightMove = 0;
	}

	auto rectCollision = CalcPosRect(m_collisionRect);
	auto worldRect = pGame->GetWorldSize();

	// Check if object has reached the edges of world (screen)
	if (!worldRect.IsContained(rectCollision))
	{
		// Set position at exactly the edge
		auto newRect = pGame->GetWorldSize().MoveInside(rectCollision);
		m_position = CalcPosition(newRect);
	}
}


void CPaddle::VDraw(unsigned int deltaT, unsigned int updateTickRate,  CGfx* pGfx)
{
	// Update loop tick value
	m_loopTick += deltaT;

	// Reset if greater than updateTickRate
	if (m_loopTick > updateTickRate)
		m_loopTick = 0;

	gcmath::Vec2<float> m_interpPos;
	float interpVal = m_loopTick / updateTickRate;
	m_interpPos.x = gcutility::LinearInterpolate((float)m_prevPosition.x, (float)m_position.x, interpVal);
	m_interpPos.y = gcutility::LinearInterpolate((float)m_prevPosition.y, (float)m_position.y, interpVal);

	// Position is to be the center of the entity.
	// Drawing is based on the top left of the texture.
    int xPos = 0, yPos = 0;

	xPos = m_interpPos.x - (m_drawFrame.GetWidth<int>() / 2);
	yPos = m_interpPos.y - (m_drawFrame.GetHeight<int>() / 2);

    pGfx->DrawTexture(m_spriteID, xPos, yPos);
}


void CPaddle::VOnCollision(bool bCollided, CBreakOut* pGame, gcmath::Rect<int>* otherCollision)
{
	// Do something
}


void CPaddle::MoveLeft(int val)
{
	m_leftMove -= val;
}


void CPaddle::MoveRight(int val)
{
	m_rightMove += val;
}