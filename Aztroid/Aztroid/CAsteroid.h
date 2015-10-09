/*
08/10/2015

Asteroid object

*/

#ifndef __CASTEROID_H__
#define __CASTEROID_H__

#include "CObject.h"

class CAsteroid : public CObject
{
public:
	CAsteroid();
	~CAsteroid();

	void VUpdate(float deltaT, CAztroid* pGame) override;
	void VDraw(float deltaT, CGfx* pGfx, int updateTick) override;

	void VMove(EMoveDir dir) override;

private:

};


#endif