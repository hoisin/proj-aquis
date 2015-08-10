#include "CPaddle.h"

CPaddle::CPaddle()
{
}


CPaddle::~CPaddle()
{
}


void CPaddle::VUpdate(unsigned int deltaT, CBreakOut* pGame)
{
}


void CPaddle::VDraw(unsigned int deltaT, CGfx* pGfx)
{
	// Position is to be the center of the entity.
	// Drawing is based on the top left of the texture.
    int xPos = 0, yPos = 0;

    xPos = m_position.x - (m_drawFrame.GetWidth<int>() / 2);
    yPos = m_position.y - (m_drawFrame.GetHeight<int>() / 2);

    pGfx->DrawTexture(m_spriteID, xPos, yPos);
}