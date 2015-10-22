#include "CObjectManager.h"
#include "CObject.h"
#include "CShip.h"

CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
}


CObject* CObjectManager::CreateObject(EObjectType type)
{
	switch (type)
	{
	case eShip:
		return new CShip;

	default:
		return nullptr;
	}
}