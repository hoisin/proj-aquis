//--------------------------------------------------------------------------
//
//	04/04/2014
//
//	Shader resource class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCESHADER_H__
#define __CRESOURCESHADER_H__

#include "IResource.h"

class CShader;

class CResourceShader : public IResource
{
public:
	CResourceShader(CShader *pShader);
	~CResourceShader();

	EResourceType VGetType() { return eResourceShader; }

	void VCleanUp();

public:
	CShader *m_pShader;
};

#endif
