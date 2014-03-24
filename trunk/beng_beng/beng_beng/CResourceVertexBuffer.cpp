#include "CResourceVertexBuffer.h"

CResourceVertexBuffer::CResourceVertexBuffer()
{
}


CResourceVertexBuffer::~CResourceVertexBuffer()
{
}


//------------------------------------------------------------------
//
//	CResourceVertexBuffer(..)
//
//	Returns the resource type
//
//------------------------------------------------------------------
EResourceType CResourceVertexBuffer::VGetType()
{
	return eResourceVertexBuffer;
}


//------------------------------------------------------------------
//
//	VCleanUp(..)
//
//	Performs any clean up required
//
//------------------------------------------------------------------
void CResourceVertexBuffer::VCleanUp()
{
}
