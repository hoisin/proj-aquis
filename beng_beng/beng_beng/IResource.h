//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Base interface class for deriving other resource types
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __IRESOURCE_H__
#define __IRESOURCE_H__


enum EResourceType
{
	eResourceVertexBuffer,
	eResourceTotal
};


class IResource 
{
public:
	IResource() {}
	~IResource() {}

	// Must override!
	virtual EResourceType VGetType() = 0;

	// Must override!
	virtual void VCleanUp() = 0;
};

#endif