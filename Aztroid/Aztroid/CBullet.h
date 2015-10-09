/*
08/10/2015

Bullet object

*/

#ifndef __CBULLET_H__
#define __CBULLET_H__

#include "CObject.h"

class CBullet : public CObject
{
public:
	CBullet();
	~CBullet();

	void VUpdate(float deltaT, CAztroid* pGame) override;
	void VDraw(float deltaT, CGfx* pGfx, int updateTick) override;

	void VMove(EMoveDir dir) override;

	void SetLifeTime(int time);

private:
	int m_updateCount;
	int m_lifeTime;

};


#endif