/*
	10/03/2015

	Object factory class
*/

#ifndef __COBJECTMANAGER_H__
#define __COBJECTMANAGER_H__

#include "GCMath.h"


struct STransform {
	gcmath::Vec2<float> m_pos;
	gcmath::Vec2<float> m_prevPos;
	gcmath::Vec2<float> m_dir;
	int m_speed;
};

struct SPhysics {
	gcmath::Rect<int> m_cBox;		// Collision box
};

enum EObjectType
{
	eAsteroid,
	eShip,
	eSmallBullet,
	eTotalObjTypes
};

class CObject;

class CObjectManager
{
public:
	CObjectManager();
	~CObjectManager();

	CObject* CreateObject(EObjectType type);
};


#endif