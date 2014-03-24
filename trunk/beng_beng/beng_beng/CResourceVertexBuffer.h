//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Vertex buffer resource class
//
//	Author: SeaFooD © 2014
//
//	Note to self...
//
//	The way vertex buffers are allocated are different from DirectX it seems.
//	Brief read of OpenGL docs suggest the following:
//	- Unlike DirectX where the vertex buffer can be allocated all at once, 
//		OpenGL requires you to create a buffer for each vertex attribute.
//		These are known as vertex buffer objects (VBOs).
//		i.e. buffer for position, buffer for colour, etc...
//
//	- To indicate which buffers go with which (i.e. which vertex buffer goes with colour buffer).
//		OpenGL has the functionality to group the created VBOs.
//		By grouping them, you define a vertex structure (e.g. position, normal, colour).
//		To group them by creating vertex array objects (VAOs).
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCEVERTEXBUFFER_H__
#define __CRESOURCEVERTEXBUFFER_H__

#include "IResource.h"

class CResourceVertexBuffer : public IResource
{
public:
	CResourceVertexBuffer();
	~CResourceVertexBuffer();

	EResourceType VGetType();

	void VCleanUp();

protected:

};


#endif