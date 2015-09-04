/*
	04/09/2015

	Class representing the player ship
*/

#ifndef __CSHIP_H__
#define __CSHIP_H__

#include "CObject.h"

class CShip : public CObject
{
public:
	CShip();
	~CShip();

	void VUpdate(float deltaT) override;
	void VDraw(float deltaT, CGfx* pGfx) override;

private:

};



#endif