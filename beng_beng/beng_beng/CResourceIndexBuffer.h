//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Index buffer
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCEINDEXBUFFER_H__
#define __CRESOURCEIDNEXBUFFER_H__

#include "IResource.h"

struct MeshData;
class CIndexBuffer;

class CResourceIndexBuffer : public IResource
{
public:
	CResourceIndexBuffer(MeshData *pData);
	~CResourceIndexBuffer();

	EResourceType VGetType() { return eResourceIndexBuffer; }

	void VCleanUp();

public:
	CIndexBuffer *m_pIdxBuffer;
};

#endif