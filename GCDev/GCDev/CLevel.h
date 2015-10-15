/*
	05/08/2015

	Class managing level data
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

	bool LoadLevelData(const std::string& fileDir);

public:
	std::vector <std::vector<gcmath::Vec2<int>>> m_bricks;
};

#endif