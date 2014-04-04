#include "CResourceShader.h"
#include "GfxDefs.h"

CResourceShader::CResourceShader(CShader *pShader) : m_pShader(pShader)
{
}


CResourceShader::~CResourceShader()
{
	VCleanUp();
}


//------------------------------------------------------------------
//
//	VCleanUp(..)
//
//	Performs any clean up required
//
//------------------------------------------------------------------
void CResourceShader::VCleanUp()
{
	if(m_pShader) {
		delete m_pShader;
		m_pShader = NULL;
	}
}