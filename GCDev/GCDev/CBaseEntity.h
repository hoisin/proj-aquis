/*
	04/08/2015

	Base entity object
*/


#ifndef __CBASEENTITY_H__
#define __CBASEENTITY_H__

#include "GCMath.h"

#include "CGfx.h"
#include "CBreakOut.h"

class CBaseEntity
{
public:
    CBaseEntity() : m_bActive(false), m_spriteID(-1) {}
	~CBaseEntity() {}

	virtual void VUpdate(unsigned int deltaT, CBreakOut* pGame) = 0;
	virtual void VDraw(unsigned int deltaT, CGfx* pGfx) = 0;
	virtual void VOnCollision(bool bCollided, gcmath::Rect<int>* otherCollision = nullptr) = 0;

    void SetActive(bool bFlag) { m_bActive = bFlag; }
	void SetPosition(const gcmath::Vec2<int>& newPos) { m_position = newPos; }			// Top left of graphic
	void SetPositionCentered(const gcmath::Vec2<int>& newPos);							// Position based on center of graphic
	void SetSpriteID(int spriteID) { m_spriteID = spriteID; }
	void SetCollisionRect(const gcmath::Rect<int>& newRect) { m_collisionRect = newRect; }
    void SetTextureFrame(const gcmath::Rect<int>& newRect) { m_drawFrame = newRect; }

    bool IsActive() { return m_bActive; }
	int GetSpriteID() { return m_spriteID;  }
	gcmath::Vec2<int> GetPosition() { return m_position; }
	gcmath::Vec2<int> GetPrevPosition() { return m_prevPosition; }
	gcmath::Rect<int> GetCollisionRect() { return m_collisionRect; }
    gcmath::Rect<int> GetDrawFrame() { return m_drawFrame; }

	// Following returns center position vector from a specified position that is top-left
	gcmath::Vec2<int> CalcPosition(const gcmath::Rect<int>& rect);
	gcmath::Vec2<int> CalcPosition(const gcmath::Vec2<int>& vec);
	gcmath::Rect<int> CalcPosRect(const gcmath::Rect<int>& rect);

	gcmath::Rect<int> GetWorldCollisionRect();

protected:
    bool m_bActive;
	int m_spriteID;
	gcmath::Vec2<int> m_position;
	gcmath::Vec2<int> m_prevPosition;
	gcmath::Rect<int> m_collisionRect;
    gcmath::Rect<int> m_drawFrame;
};

#endif