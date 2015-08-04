/*
	04/08/2015

	Class representing the paddle
*/

#ifndef __CPADDLE_H__
#define __CPADDLE_H__

#include "CBaseEntity.h"

class CPaddle : public CBaseEntity
{
public:
	CPaddle();
	~CPaddle();

	void VUpdate(unsigned int deltaT) override;
	void VDraw(unsigned int deltaT) override;
};

#endif