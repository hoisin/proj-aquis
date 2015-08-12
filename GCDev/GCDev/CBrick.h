/*
	05/08/2015

	Destructable bricks in break out
*/

#ifndef __CBRICK_H__
#define __CBRICK_H__

#include "CBaseEntity.h"

class CBrick : public CBaseEntity
{
public:
	CBrick();
	~CBrick();

	void VUpdate(unsigned int deltaT, CBreakOut* pGame) override;
	void VDraw(unsigned int deltaT, CGfx* pGfx) override;
	void VOnCollision(bool bCollided, gcmath::Rect<int>* otherCollision = nullptr) override;

private:

};

#endif