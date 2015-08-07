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
	void VDraw(unsigned int deltaT, CGfx* pGfx) override;

	void SetSpeed(int speed);
	void SetDirection(const gcmath::Vec2<float>& dir);

	int GetSpeed();
	gcmath::Vec2<float> GetDirection();

private:
	int m_speed;
	gcmath::Vec2<float> m_direction;

};


#endif