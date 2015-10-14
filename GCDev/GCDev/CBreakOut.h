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

	void SetLevel(unsigned int levelNum, unsigned int screenWidth, unsigned int screenHeight);

	void Update(unsigned int deltaT);

	void Draw(unsigned int deltaT, CGfx* pGfx);

	std::vector<std::shared_ptr<CBaseEntity>>* GetEntities(const std::string& key);
	CBaseEntity* GetEntity(const std::string& key, unsigned int index);

	gcmath::Rect<int> GetWorldSize() { return m_worldSize; }

	void ReduceBrickCount() { m_remainingBricks--; }

	bool IsClear() { return (m_remainingBricks <= 0); }
	int GetCurrentLevel() { return m_currentLevel; }
	int GetMaxLevels();

	void SetUpdateTick(int updateTick);
	int GetUpdateTick() { return m_updateTick; }

private:
	void LoadLevel(CLevel* pLevel);

private:
	std::map<std::string, std::vector<std::shared_ptr<CBaseEntity>>> m_entities;
    
    int m_brickTextureID;
    gcmath::Rect<int> m_brickDrawFrame;

	gcmath::Rect<int> m_worldSize;

	std::shared_ptr<CLevel> m_levelMgr;
	int m_currentLevel;
	int m_remainingBricks;

	int m_updateTick;		// Frequency of the update method call in ms


	// Variables to determine the size of the world and prevent entities from going beyond.
	// Only creating world size as big as the screen
	int m_worldWidth;
	int m_worldHeight;
};


#endif