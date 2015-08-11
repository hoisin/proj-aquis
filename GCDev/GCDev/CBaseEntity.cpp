#include "CBaseEntity.h"


void CBaseEntity::SetPositionCentered(const gcmath::Vec2<int>& pos)
{
	m_position.x = pos.x - (m_drawFrame.GetWidth<int>() / 2);
	m_position.y = pos.y - (m_drawFrame.GetHeight<int>() / 2);
}


gcmath::Vec2<int> CBaseEntity::CalcPosition(const gcmath::Rect<int>& rect)
{
	return gcmath::Vec2<int>(rect.left + (rect.GetWidth<int>() / 2),
		rect.top + (rect.GetHeight<int>() / 2));
}


gcmath::Vec2<int> CBaseEntity::CalcPosition(const gcmath::Vec2<int>& vec)
{
	return gcmath::Vec2<int>(vec.x + (m_collisionRect.GetWidth<int>() / 2),
		vec.y + (m_collisionRect.GetHeight<int>() / 2));
}


gcmath::Rect<int> CBaseEntity::CalcPosRect(const gcmath::Rect<int>& rect)
{
	auto newRect = rect;
	newRect += gcmath::Vec2<int>(m_position.x - (rect.GetWidth<int>() / 2),
		m_position.y - (rect.GetHeight<int>() / 2));

	return newRect;
}