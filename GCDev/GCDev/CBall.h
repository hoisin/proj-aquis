/*
	05/08/2015

	Moving ball
*/

#ifndef __CBALL_H__
#define __CBALL_H__

#include "CBaseEntity.h"

class CBall : public CBaseEntity
{
public:
	CBall();
	~CBall();

	void VUpdate(unsigned int deltaT, CBreakOut* pGame) override;
	void VDraw(unsigned int deltaT, unsigned int updateTickRate,  CGfx* pGfx) override;
	void VOnCollision(bool bCollided, CBreakOut* pGame, gcmath::Rect<int>* otherCollision = nullptr) override;

	void SetSpeed(int speed);
	void SetDirection(const gcmath::Vec2<float>& dir);

	int GetSpeed();
	gcmath::Vec2<float> GetDirection();

private:
	void WorldBoundsCheck(CBreakOut* pGame);

private:
	int m_speed;
	gcmath::Vec2<float> m_direction;

};


#endif