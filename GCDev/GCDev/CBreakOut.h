/*
	04/08/2015

	Break out game
*/

#ifndef __CBREAKOUT_H__
#define __CBREAKOUT_H__

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "GCMath.h"

class CGfx;
class CBaseEntity;
class CLevel;

class CBreakOut
{
public:
	CBreakOut();
	~CBreakOut();

	bool Initialise(CGfx* pGfx);

	void SetLevel(unsigned int levelNum, unsigned int screenWidth);

	void Update(unsigned int deltaT);

	void Draw(unsigned int deltaT, CGfx* pGfx);

	std::vector<std::shared_ptr<CBaseEntity>>* GetEntities(const std::string& key);

	gcmath::Rect<int> GetWorldSize() { return m_worldSize; }

private:
	void LoadLevel(CLevel* pLevel);

private:
	std::map<std::string, std::vector<std::shared_ptr<CBaseEntity>>> m_entities;
    
    int m_brickTextureID;
    gcmath::Rect<int> m_brickDrawFrame;

	gcmath::Rect<int> m_worldSize;


	// Variables to determine the size of the world and prevent entities from going beyond.
	// Only creating world size as big as the screen
	int m_worldWidth;
	int m_worldHeight;
};


#endif