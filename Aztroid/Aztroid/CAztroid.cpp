#include "CAztroid.h"
#include "CGfx.h"
#include "CObject.h"
#include "CShip.h"
#include "CBullet.h"
#include "Utility.h"

CAztroid::CAztroid() : m_updateTick(0), m_loopTick(0), m_freeBulletIdx(0)
{
}


CAztroid::~CAztroid()
{
	// Clear map to decrement reference counter on objects so that it is deleted
	m_mEntities.clear();
}


bool CAztroid::Initialise(CGfx* pGfx, int worldWidth, int worldHeight, int updateTick)
{
	m_worldSize.left = 0;
	m_worldSize.right = worldWidth;
	m_worldSize.top = 0;
	m_worldSize.bottom = worldHeight;

	// Setup entity map
	auto shipEntityVec = std::pair<std::string, VectorObjPtr>("ships", VectorObjPtr());
	auto asteroidEntityVec = std::pair<std::string, VectorObjPtr>("asteroids", VectorObjPtr());
	auto bulletEntityVec = std::pair<std::string, VectorObjPtr>("bullets", VectorObjPtr());

	m_mEntities = std::map<std::string, VectorObjPtr>();
	m_mEntities.insert(shipEntityVec);
	m_mEntities.insert(bulletEntityVec);
	m_mEntities.insert(asteroidEntityVec);

	// Setup assets
	int shipTexture = pGfx->LoadTexture("..\\Assets\\ship.bmp", 
		gcutility::CreateSDLColor(0, 255, 0));

	int bulletTexture = pGfx->LoadTexture("..\\Assets\\energyBullet.bmp",
		gcutility::CreateSDLColor(0, 255, 0));

	// Create entity instances
	std::shared_ptr<CShip> pObjShip(new CShip());
	pObjShip->SetCollisionBox(gcmath::Rect<int>(0, 32, 0, 32));
	pObjShip->SetPosition(gcmath::Vec2<int>(0, 0));
	pObjShip->SetPrevPosition(gcmath::Vec2<int>(100, 100));
	pObjShip->SetDirection(gcmath::Vec2<float>(1.f, 0.f));
	pObjShip->SetSpeed(10);
	pObjShip->SetSpriteID(shipTexture);
	pObjShip->SetActive(true);

	pObjShip->SetRotationSpeed(10);

	m_mEntities["ships"].push_back(pObjShip);

	for (int i = 0; i < 200; i++) {
		std::shared_ptr<CBullet> pBullet(new CBullet());
		pBullet->SetCollisionBox(gcmath::Rect<int>(0, 16, 0, 16));
		pBullet->SetPosition(gcmath::Vec2<int>(0, 0));
		pBullet->SetPrevPosition(gcmath::Vec2<int>(0, 0));
		pBullet->SetDirection(gcmath::Vec2<float>(1.f, 0.f));
		pBullet->SetSpeed(20);
		pBullet->SetSpriteID(bulletTexture);
		pBullet->SetActive(false);
		pBullet->SetLifeTime(2000);

		m_mEntities["bullets"].push_back(pBullet);
	}

	m_updateTick = updateTick;

	return true;
}


void CAztroid::LoadLevel(int level)
{

}


void CAztroid::Update(float deltaT)
{
	for (auto const &entityVec : m_mEntities) {
		for (auto const &entityIt : entityVec.second) {
			if (entityIt->IsActive())
				entityIt->VUpdate(deltaT, this);
		}
	}

	m_loopTick = 0;
}


void CAztroid::Draw(float deltaT, CGfx* pGfx)
{
	if (m_loopTick < m_updateTick)
		m_loopTick += deltaT;
	else
		m_loopTick = m_updateTick;

	for (auto const &entityVec : m_mEntities) {
		for (auto const &entityIt : entityVec.second) {
			if (entityIt->IsActive())
				entityIt->VDraw(m_loopTick, pGfx, m_updateTick);
		}
	}
}


CObject* CAztroid::GetObject(const std::string& objGrp, int objIndex)
{
	if (objIndex >= 0) {
		auto it = m_mEntities.find(objGrp);

		if (it != m_mEntities.end()) {
			if (objIndex < (int)it->second.size())
				return it->second[objIndex].get();
		}
	}
	
	return nullptr;
}


CObject* CAztroid::SpawnBullet(gcmath::Rect<int> spawnerObjCollisionRect, 
	const gcmath::Vec2<float>& pos, const gcmath::Vec2<float>& dir)
{
	auto bulletVec = m_mEntities.find("bullets");

	if (bulletVec != m_mEntities.end()) {
		int counter = 0;

		while (counter < bulletVec->second.size()) {
			if (!bulletVec->second[m_freeBulletIdx]->IsActive()) {

				// Calculate exact spawn position
				float spawnX = pos.x + (dir.x * (spawnerObjCollisionRect.GetWidth<int>() / 2
					+ bulletVec->second[m_freeBulletIdx]->GetCollisionRect().GetWidth<int>() / 2)) +
					bulletVec->second[m_freeBulletIdx]->GetCollisionRect().GetWidth<int>() / 2;
				float spawnY = pos.y + (dir.y * (spawnerObjCollisionRect.GetHeight<int>() / 2
					+ bulletVec->second[m_freeBulletIdx]->GetCollisionRect().GetHeight<int>() / 2)) +
					bulletVec->second[m_freeBulletIdx]->GetCollisionRect().GetHeight<int>() / 2;

				gcmath::Vec2<float> spawnPos(spawnX, spawnY);

				bulletVec->second[m_freeBulletIdx]->SetActive(true);
				bulletVec->second[m_freeBulletIdx]->SetPosition(spawnPos);
				bulletVec->second[m_freeBulletIdx]->SetPrevPosition(spawnPos);
				bulletVec->second[m_freeBulletIdx]->SetDirection(dir);

				int returnIdx = m_freeBulletIdx;

				m_freeBulletIdx++;
				if (m_freeBulletIdx >= bulletVec->second.size())
					m_freeBulletIdx = 0;

				return bulletVec->second[returnIdx].get();
			}

			m_freeBulletIdx++;
			if (m_freeBulletIdx >= bulletVec->second.size())
				m_freeBulletIdx = 0;
		}
	}

	return nullptr;
}