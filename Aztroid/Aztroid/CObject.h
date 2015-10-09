/*
	04/09/2015

	Base game object
*/


#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "GCMath.h"
#include "CGfx.h"

//class CAztroid;
#include "CAztroid.h"

enum EMoveDir
{
	eLeft,
	eRight,
	eUp,
	eDown,
	eTotalDir
};


class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual void VUpdate(float deltaT, CAztroid* pGame) = 0;
	virtual void VDraw(float deltaT, CGfx* pGfx, int updateTick) = 0;

	bool IsActive() { return m_bActive; }

	virtual void VMove(EMoveDir dir) = 0;

	virtual void VFire() {}

	void SetCollisionBox(const gcmath::Rect<int>& collisionRect) {	m_cBox = collisionRect; }
	void SetPosition(const gcmath::Vec2<int>& pos) { m_pos = pos; }
	void SetPrevPosition(const gcmath::Vec2<int>& prevPos) { m_prevPos = prevPos; }
	void SetDirection(const gcmath::Vec2<float>& dir) { m_dir = dir; }
	void SetSpeed(int speed) { m_speed = speed; }
	void SetSpriteID(int spriteID) { m_spriteID = spriteID; }
	void SetActive(bool bFlag) { m_bActive = bFlag; }

	gcmath::Rect<int> GetCollisionRect() { return m_cBox; }

protected:
	gcmath::Rect<int> m_cBox;		// Collision box
	gcmath::Vec2<float> m_pos;
	gcmath::Vec2<float> m_prevPos;
	gcmath::Vec2<float> m_dir;

	int m_speed;
	int m_spriteID;
	bool m_bActive;
};

#endif