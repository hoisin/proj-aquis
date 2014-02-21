//-----------------------------------------------------------
//
//	Date: 21/02/2014
//	Author: Matthew Tsang
//
//	Resource class holding a vertex buffer
//
//-----------------------------------------------------------

#ifndef __CRESOURCEVERTEXBUFFER_H__
#define __CRESOURCEVERTEXBUFFER_H__

#include "IResource.h"

class ID3D11Buffer;

class CResourceVertexBuffer : public IResource
{
protected:
	ID3D11Buffer* m_pVertexBuffer;

public:
	CResourceVertexBuffer(ID3D11Buffer *pInData);
	~CResourceVertexBuffer(void);

	EResourceType VGetType(void);

	void VCleanUp(void);

	void* VGetData(void);
};


#endif