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

	void VUpdate(float deltaT, CAztroid* pGame) override;
	void VDraw(float deltaT, CGfx* pGfx, int updateTick) override;

	void VMove(EMoveDir dir) override;

	void VFire() override;

	void SetRotationSpeed(int rotSpeed);
	void SetCurrentRotation(int rotVal);

private:
	bool m_updateDir[eTotalDir];
	bool m_bFire;

	int m_rotSpeed;			// Rotation in degrees
	int m_prevRotation;
	int m_currentRotation;	
};



#endif