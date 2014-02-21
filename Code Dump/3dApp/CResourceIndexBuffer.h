//-----------------------------------------------------------
//
//	Date: 21/02/2014
//	Author: Matthew Tsang
//
//	Resource class holding an index buffer
//
//-----------------------------------------------------------

#ifndef __CRESOURCEINDEXBUFFER_H__
#define __CRESOURCEINDEXBUFFER_H__

#include "IResource.h"

class ID3D11Buffer;

class CResourceIndexBuffer : public IResource
{
protected:
	ID3D11Buffer* m_pIndexBuffer;

public:
	CResourceIndexBuffer(ID3D11Buffer *pInData);
	~CResourceIndexBuffer(void);

	EResourceType VGetType(void);

	void VCleanUp(void);

	void* VGetData(void);
};


#endif