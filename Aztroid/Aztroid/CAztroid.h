/*
04/09/2015

Main game class

*/

#ifndef __CAZTROID_H__
#define __CAZTROID_H__

#include <map>
#include <memory>
#include <vector>
#include <string>

#include "GCMath.h"

class CObject;
class CGfx;

typedef std::vector<std::shared_ptr<CObject>> VectorObjPtr;

class CAztroid
{
public:
	CAztroid();
	~CAztroid();

	bool Initialise(CGfx* pGfx, int worldWidth, int worldHeight, int updateTick);

	void LoadLevel(int level);

	void Update(float deltaT);
	void Draw(float deltaT, CGfx* pGfx);

	CObject* GetObject(const std::string& objGroup, int objIndex);

	CObject* SpawnBullet(gcmath::Rect<int> spawnerObjCollisionRect,
		const gcmath::Vec2<float>& pos, const gcmath::Vec2<float>& dir);

	int GetUpdateTick() { return m_updateTick; }
	gcmath::Rect<int> GetWorldDimension() { return m_worldSize; }

private:
	std::map<std::string, VectorObjPtr> m_mEntities;

	gcmath::Rect<int> m_worldSize;

	int m_updateTick;
	int m_loopTick;

	int m_freeBulletIdx;
};


#endif