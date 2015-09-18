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