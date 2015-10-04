#include "CObjectFactory.h"
#include "CObject.h"
#include "CShip.h"

CObjectFactory::CObjectFactory()
{
}


CObjectFactory::CObjectFactory()
{
}


CObject* CObjectFactory::CreateObject(EObjectType type)
{
	switch (type)
	{
	case eShip:
		return new CShip;

	default:
		return nullptr;
	}
}