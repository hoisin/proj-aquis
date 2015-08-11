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

	// Move the object
	m_position.x += (int)tempVec.x;
	m_position.y += (int)tempVec.y;

	// Check world boundary
	WorldBoundsCheck(pGame);

	// Record old position
	m_prevPosition = m_position;
}


void CBall::VDraw(unsigned int deltaT, CGfx* pGfx)
{
    // Position is to be the center of the entity.
    // Drawing is based on the top left of the texture.
    int xPos = 0, yPos = 0;

    xPos = m_position.x - (m_drawFrame.GetWidth<int>() / 2);
	yPos = m_position.y - (m_drawFrame.GetHeight<int>() / 2);

    pGfx->DrawTexture(m_spriteID, xPos, yPos);
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