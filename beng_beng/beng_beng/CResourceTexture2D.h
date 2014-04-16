//--------------------------------------------------------------------------
//
//	16/04/2014
//
//	2D texture resource class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCETEXTURE2D_H__
#define __CRESOURCETEXTURE2D_H__

#include "IResource.h"

class CTexture2D;

class CResourceTexture2D : public IResource
{
public:
	CResourceTexture2D(CTexture2D *pTexture);
	~CResourceTexture2D();

	EResourceType VGetType() { return eResourceTexture2D; }

	void VCleanUp();

public:
	CTexture2D *m_pTexture;
};


#endif