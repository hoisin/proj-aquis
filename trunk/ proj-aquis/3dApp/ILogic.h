/*
	Date: 13/02/2013
	Logic interface class
*/

#ifndef __ILOGIC_H__
#define __ILOGIC_H__

class ILogic
{
public:
	ILogic(void) {}
	virtual ~ILogic(void) {}

	virtual bool VInitialise(void) = 0;

	virtual void VUpdate(float deltaTime) = 0;


};

#endif