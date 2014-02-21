//-----------------------------------------------------------
//
//	Date: 21/02/2014
//	Author: Matthew Tsang
//
//	Interface class for resources.
//
//	When using with resource manager, the resource manager will
//	return queried resource as IResource. User needs to call
//	VGetType(..) to ID the resource type and cast to that
//	resource type.
//
//-----------------------------------------------------------

#ifndef __IRESOURCE_H__
#define __IRESOURCE_H__


enum EResourceType
{
	eResourceTexture,
	eResourceMeshData,
	eResourceVertexBuffer,
	eResourceIndexBuffer,
	eResourceModelData,
	eResourceShader,
	eTotalResource
};


class IResource
{
public:
	IResource(void) {}
	virtual ~IResource(void) {}

	// Must return your own type!
	virtual EResourceType VGetType(void) = 0;

	// Must clean up your own stuff!
	virtual void VCleanUp(void) = 0;

	// Not sure whether to go through with this.....
	virtual void* VGetData(void) { return 0; }
};


#endif