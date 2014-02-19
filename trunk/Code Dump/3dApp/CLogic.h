/*
	Date: 13/02/2013
	Logic interface class
*/

#ifndef __CLOGIC_H__
#define __CLOGIC_H__

#include "ILogic.h"

class CLogic : public ILogic
{
public:
	CLogic(void);
	virtual ~CLogic(void);

	virtual bool VInitialise(void);

	virtual void VUpdate(float deltaTime);


};

#endif