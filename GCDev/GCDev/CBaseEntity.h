/*
	04/08/2015

	Base entity object
*/


#ifndef __CBASEENTITY_H__
#define __CBASEENTITY_H__

class CBaseEntity
{
public:
	CBaseEntity() {}
	~CBaseEntity() {}

	virtual void VUpdate(unsigned int deltaT) = 0;
	virtual void VDraw(unsigned int deltaT) = 0;

protected:
	int m_spriteID;
};

#endif