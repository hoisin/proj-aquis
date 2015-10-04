#include "CAztroid.h"
#include "CGfx.h"

CAztroid::CAztroid()
{
}


CAztroid::~CAztroid()
{
}


void CAztroid::LoadLevel(int level)
{

}


void CAztroid::Update(float deltaT)
{
	for (auto const &entityVec : m_mEntities) {
		for (auto const &entityIt : entityVec.second) {
			if (entityIt->IsActive())
				entityIt->VUpdate(deltaT);
		}
	}
}


void CAztroid::Draw(float deltaT, CGfx* pGfx)
{
	for (auto const &entityVec : m_mEntities) {
		for (auto const &entityIt : entityVec.second) {
			if (entityIt->IsActive())
				entityIt->VDraw(deltaT, pGfx);
		}
	}
}


CObject* CAztroid::GetObject(const std::string& objGrp, int objIndex)
{
	if (objIndex > 0) {
		auto it = m_mEntities.find(objGrp);

		if (it != m_mEntities.end()) {
			if (objIndex < it->second.size())
				return it->second[objIndex].get();
		}
	}
}