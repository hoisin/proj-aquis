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
	eResourceMeshData,
	eResourceVertexBuffer,
	eResourceIndexBuffer,
	eResourceModelMesh,
	eResourceShader,
	eResourceTexture2D,
	eResourceTotal
};


class IResource 
{
public:
	IResource() {}
	virtual ~IResource() {}

	// Must override!
	virtual EResourceType VGetType() = 0;

	// Must override!
	virtual void VCleanUp() = 0;
};

#endif