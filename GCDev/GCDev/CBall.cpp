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

	auto rectCollision = m_collisionRect;
	rectCollision += gcmath::Vec2<int>(m_position.x - (m_collisionRect.GetWidth<int>() / 2),
		m_position.y - (m_collisionRect.GetHeight<int>() / 2));

	// Check of object to object collision
	//	- Bricks & paddle
	if (!pGame->GetWorldSize().IsContained(rectCollision))
	{
		m_position = m_prevPosition;
		m_direction *= -1.f;
	}

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

	auto rectCollision = m_collisionRect;
	rectCollision += gcmath::Vec2<int>(m_position.x - (m_collisionRect.GetWidth<int>() / 2),
		m_position.y - (m_collisionRect.GetHeight<int>() / 2));

	SDL_Rect temp;
	temp.x = rectCollision.left;
	temp.y = rectCollision.top;
	temp.w = rectCollision.GetWidth<int>();
	temp.h = rectCollision.GetHeight<int>();

    pGfx->DrawTexture(m_spriteID, xPos, yPos);
	pGfx->DrawRect(temp, 255, 0, 0);
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