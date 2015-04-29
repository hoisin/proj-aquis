#include "CTextureManager.h"
#include "CTexture2D.h"
#include "CTextureLoader.h"

#include <string>


CTextureManager::CTextureManager(void) : m_pTextureLoader(NULL)
{
	m_pTextureLoader = new CTextureLoader;
}


CTextureManager::~CTextureManager(void)
{
	std::map<std::string, CTexture2D*>::iterator it;

	for(it = m_mpTexture.begin(); it != m_mpTexture.end(); it++) {
		delete it->second;
		it->second = NULL;
	}

	m_mpTexture.empty();

	if(m_pTextureLoader) {
		delete m_pTextureLoader;
		m_pTextureLoader = NULL;
	}
}


bool CTextureManager::LoadTexture(const std::string& textureId, 
	const std::string& textureFile)
{
	unsigned int width = 0, height = 0;
	unsigned char* pTextureData = 0;
	ETextureFormat eTexFormat = eTextureFormatNone;
	unsigned int bpp = 0;
	CTexture2D* pNewTexture = new CTexture2D;

	if (m_pTextureLoader->LoadFile(textureFile, width, height, eTexFormat, bpp, &pTextureData)) {

		// For now we assume bits per pixel only range from 1 and 3
		switch (eTexFormat)
		{
		case eTextureFormatBMP:
			if (bpp == 1) {
				pNewTexture->LoadTexture(width, height, GL_LUMINANCE, GL_RED, GL_UNSIGNED_BYTE, pTextureData);
			}
			else {
				pNewTexture->LoadTexture(width, height, GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, pTextureData);
			}
			break;

		case eTextureFormatTGA:
			if (bpp == 1) {
				pNewTexture->LoadTexture(width, height, GL_LUMINANCE, GL_RED, GL_UNSIGNED_BYTE, pTextureData);
			}
			else {
				pNewTexture->LoadTexture(width, height, GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, pTextureData);
			}
			break;

		case eTextureFormatPNG:
			if (bpp == 1) {
				pNewTexture->LoadTexture(width, height, GL_LUMINANCE, GL_RED, GL_UNSIGNED_BYTE, pTextureData);
			}
			else {
				pNewTexture->LoadTexture(width, height, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, pTextureData);
			}
			break;

		default:
			break;
		}

		//pNewTexture->LoadTexture(width, height, GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, pTextureData);

		m_mpTexture.insert(std::pair<std::string, CTexture2D*>(textureId, pNewTexture));

		// Clean up loaded data
		if(pTextureData) {
			delete [] pTextureData;
			pTextureData = NULL;
		}

		return true;
	}

	if (pNewTexture) {
		delete pNewTexture;
		pNewTexture = NULL;
	}

	return false;
}


CTexture2D* CTextureManager::GetTexture(const std::string& textureID)
{
	std::map<std::string, CTexture2D*>::iterator it = m_mpTexture.find(textureID);

	if(it != m_mpTexture.end())
		return it->second;

	return NULL;
}
