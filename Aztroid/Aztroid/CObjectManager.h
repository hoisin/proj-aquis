/*
	10/03/2015

	Object factory class
*/

#ifndef __COBJECTMANAGER_H__
#define __COBJECTMANAGER_H__

#include <vector>
#include "GCMath.h"
#include "CGfx.h"

struct SObjDataTransform {
	gcmath::Rect<int> m_cBox;		// Stores the collision box and world position of obj
	gcmath::Vec2<float> m_dir;		// Direction the obj is facing
	gcmath::Vec2<int> m_prevPos;	// For collision event and graphic interpolation
	int m_speed;					// Scalar to apply to direction for movement
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

	int CreateObject(EObjectType type, const SObjDataTransform& pData);

private:
	std::vector<SDrawData*> m_objGfxData;
};


#endif