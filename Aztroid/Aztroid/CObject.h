/*
	04/09/2015

	Base game object
*/


#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "GCMath.h"

class CGfx;

class CObject
{
public:
	CObject() {}
	virtual ~CObject() {}

	virtual void VUpdate(float deltaT) = 0;
	virtual void VDraw(float deltaT, CGfx* pGfx) = 0;

protected:
	gcmath::Vec2<int> m_pos;
	gcmath::Vec2<int> m_prevPos;
	gcmath::Rect<int> m_cBox;		// Collision box

	int m_spriteID;

	bool m_bActive;
};

#endif