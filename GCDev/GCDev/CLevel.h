/*
	05/08/2015

	Class containing level data
*/


#ifndef __CLEVEL_H__
#define __CLEVEL_H__

#include <vector>
#include "gcmath.h"

class CLevel
{
public:
	CLevel();
	~CLevel();

	void AddBrick(const gcmath::Vec2<int>& newBrickPos);

public:
	std::vector<gcmath::Vec2<int>> m_brickPositions;
};

#endif