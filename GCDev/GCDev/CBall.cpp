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

	// Record old position
	m_prevPosition = m_position;

	// Move the object
	m_position.x += (int)tempVec.x;
	m_position.y += (int)tempVec.y;

	// Check for boundary collision
	auto calRect = m_collisionRect;
	calRect += m_position;

	// Check of object to object collision
	//	- Bricks & paddle
}


void CBall::VDraw(unsigned int deltaT, CGfx* pGfx)
{
    // Position is to be the center of the entity.
    // Drawing is based on the top left of the texture.
    int xPos = 0, yPos = 0;

    xPos = m_position.x - (m_drawFrame.GetWidth() / 2);
    yPos = m_position.y - (m_drawFrame.GetHeight() / 2);

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