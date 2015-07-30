#include "CTextureManager.h"


CTexture::CTexture(SDL_Surface* pTexSurface, Uint16 texWidth, Uint16 texHeight) :
pSurface(pTexSurface), width(texWidth), height(texHeight)
{

}


CTexture::CTexture() : pSurface(nullptr), width(0), height(0)
{
}


CTexture::~CTexture()
{
	if (pSurface) {
		SDL_FreeSurface(pSurface);
		pSurface = nullptr;
	}
}


//---------------------------------------------------------------------------
//
//	GetTotalRowAnimations()
//
//	Params:
//	row		- The animation row to query
//
//	Descrition:
//	Returns the number of animation frames for the specified animation row
//
//---------------------------------------------------------------------------
Uint16 CTexture::GetTotalRowAnimations(Uint16 row)
{
	if ((row - 1) < rowTotalFrames.size())
		return rowTotalFrames[row - 1];

	return 0;
}


//---------------------------------------------------------------------------
//
//	GetTotalTypesAnimations()
//
//	Descrition:
//	Returns the number of animation types for the texture
//
//---------------------------------------------------------------------------
Uint16 CTexture::GetTotalTypesAnimations()
{
	return (Uint16)rowTotalFrames.size();
}




CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{
}


int CTextureManager::LoadTexture(const std::string& fileName, CTexture* pOutTexture)
{
	CTexture* pNewTexture = new CTexture;

	pNewTexture->pSurface = SDL_LoadBMP(fileName.c_str());

	// Clean up if failed load
	if (pNewTexture->pSurface == nullptr) {
		delete pNewTexture;
		pNewTexture = nullptr;
		return -1;
	}

	pNewTexture->width = pNewTexture->pSurface->w;
	pNewTexture->height = pNewTexture->pSurface->h;

	m_pTextures.push_back(pNewTexture);

	return m_pTextures.size() - 1;
}


void CTextureManager::SetTextureAnimationFrame(Uint16 texIdx, Uint16 width, Uint16 height)
{
	if (texIdx < m_pTextures.size()) {
		SDL_Rect frameRect;
		frameRect.w = width;
		frameRect.h = height;
		m_pTextures[texIdx]->animFrame = frameRect;
	}
}


void CTextureManager::AddTotalFrames(Uint16 texIdx, Uint16 totalFrames)
{
	if (texIdx < m_pTextures.size()) {
		m_pTextures[texIdx]->rowTotalFrames.push_back(totalFrames);
	}
}


Uint16 CTextureManager::GetTotalFramesRow(Uint16 texIdx, Uint16 animRow)
{
	if (texIdx < m_pTextures.size()) {
		return m_pTextures[texIdx]->rowTotalFrames[animRow];
	}

	return 0;
}


CTexture* CTextureManager::GetTexture(Uint16 texIdx)
{
	if (texIdx < m_pTextures.size()) {
		return m_pTextures[texIdx];
	}
}