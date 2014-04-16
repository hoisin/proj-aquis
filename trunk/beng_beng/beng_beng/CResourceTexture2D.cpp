#include "CResourceTexture2D.h"
#include "CTexture2D.h"


CResourceTexture2D::CResourceTexture2D(CTexture2D *pTexture) : m_pTexture(pTexture)
{
}


CResourceTexture2D::~CResourceTexture2D()
{
	VCleanUp();
}


void CResourceTexture2D::VCleanUp()
{
	if(m_pTexture) { 
		delete m_pTexture;
		m_pTexture = NULL;
	}
}