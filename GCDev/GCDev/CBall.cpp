#include "CBall.h"

CBall::CBall()
{
}


CBall::~CBall()
{
}


void CBall::VUpdate(unsigned int deltaT, CBreakOut* pGame)
{
	auto tempVec = m_direction * (float)m_speed;

	m_prevPosition = m_position;

	// Move the object
	m_position.x += (int)tempVec.x;
	m_position.y += (int)tempVec.y;

	// Check world boundary
	WorldBoundsCheck(pGame);
}


void CBall::VDraw(unsigned int deltaT, unsigned int updateTickRate,  CGfx* pGfx)
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

	xPos = (int)m_interpPos.x - (m_drawFrame.GetWidth<int>() / 2);
	yPos = (int)m_interpPos.y - (m_drawFrame.GetHeight<int>() / 2);

    pGfx->DrawTexture(m_spriteID, xPos, yPos);
}


void CBall::VOnCollision(bool bCollided, CBreakOut* pGame, gcmath::Rect<int>* otherCollision)
{
	if (bCollided) {
		if (otherCollision) {
			if (m_position.y < otherCollision->top || m_position.y > otherCollision->bottom)
				m_direction.y *= -1.f;
			else
				m_direction.x *= -1.f;
		}
	}	
}


void CBall::SetSpeed(int speed)
{
	m_speed = speed;			
}


void CBall::SetDirection(const gcmath::Vec2<float>& dir)
{
	m_direction = dir;
}


int CBall::GetSpeed()
{
	return m_speed;
}


gcmath::Vec2<float> CBall::GetDirection()
{
	return m_direction;
}


void CBall::WorldBoundsCheck(CBreakOut* pGame)
{
	auto rectCollision = CalcPosRect(m_collisionRect);
	auto worldRect = pGame->GetWorldSize();

	// Check if object has reached the edges of world (screen)
	if (!worldRect.IsContained(rectCollision))
	{
		if (worldRect.IsIntersectingEdge(rectCollision, gcmath::EdgeType::ELeft) ||
			worldRect.IsIntersectingEdge(rectCollision, gcmath::EdgeType::ERight)) {
			m_direction.x *= -1.f;
		}

		if (worldRect.IsIntersectingEdge(rectCollision, gcmath::EdgeType::ETop) ||
			worldRect.IsIntersectingEdge(rectCollision, gcmath::EdgeType::EBottom)) {
			m_direction.y *= -1.f;
		}

		// Set position at exactly the edge
		auto newRect = pGame->GetWorldSize().MoveInside(rectCollision);
		m_position = CalcPosition(newRect);
	}
}