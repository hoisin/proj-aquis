#include "CLevel.h"


CLevel::CLevel()
{
}


CLevel::~CLevel()
{
}


void CLevel::AddBrick(const gcmath::Vec2<int>& newBrickPos)
{
	auto newBrick = newBrickPos;

	m_brickPositions.push_back(newBrick);
}


