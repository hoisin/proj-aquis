/*
	10/03/2015

	Object factory class
*/

#ifndef __COBJECTFACTORY_H__
#define __COBJECTFACTORY_H__


enum EObjectType
{
	eAsteroid,
	eShip,
	eSmallBullet,
	eTotalObjTypes
};

class CObject;

class CObjectFactory
{
public:
	CObjectFactory();
	~CObjectFactory();

	CObject* CreateObject(EObjectType type);
};


#endif