#include "CTextureManager.h"


CTexture::CTexture(SDL_Texture* pTexSurface, Uint16 texWidth, Uint16 texHeight) :
pSDLTexture(pTexSurface), width(texWidth), height(texHeight)
{

}


CTexture::CTexture() : pSDLTexture(nullptr), width(0), height(0)
{
}


CTexture::~CTexture()
{
	if (pSDLTexture) {
		SDL_DestroyTexture(pSDLTexture);
		pSDLTexture = nullptr;
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
	if ((row - 1) < (Uint16)rowTotalFrames.size())
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
	m_pTextures = std::vector<CTexture*>();
}


CTextureManager::~CTextureManager()
{
}


int CTextureManager::LoadTexture(const std::string& fileName, SDL_Renderer* pRenderer, 
	CTexture* pOutTexture)
{
	CTexture* pNewTexture = new CTexture;
	SDL_Surface* pLoadingSurface = nullptr;

	// Load texture
	pLoadingSurface = SDL_LoadBMP(fileName.c_str());

	// Clean up if failed load
	if (pLoadingSurface == nullptr) {
		delete pNewTexture;
		pNewTexture = nullptr;
		return -1;
	}

	// Fill details
	pNewTexture->width = pLoadingSurface->w;
	pNewTexture->height = pLoadingSurface->h;

	pNewTexture->animFrame.w = pNewTexture->width;
	pNewTexture->animFrame.h = pNewTexture->height;

	// Now create the SDL_Texture
	pNewTexture->pSDLTexture = SDL_CreateTextureFromSurface(pRenderer, pLoadingSurface);
	SDL_FreeSurface(pLoadingSurface);

	m_pTextures.push_back(pNewTexture);

	return m_pTextures.size() - 1;
}


int CTextureManager::LoadTexture(const std::string& fileName, SDL_Renderer* pRenderer,
	SDL_Color key, CTexture* pOutTexture)
{
    CTexture* pNewTexture = new CTexture;
	SDL_Surface* pLoadingSurface = nullptr;

	pLoadingSurface = SDL_LoadBMP(fileName.c_str());

    // Clean up if failed load
	if (pLoadingSurface == nullptr) {
        delete pNewTexture;
        pNewTexture = nullptr;
        return -1;
    }

	Uint32 colourKey = SDL_MapRGB(pLoadingSurface->format, key.r, key.g, key.b);

	SDL_SetColorKey(pLoadingSurface, 1, colourKey);

	pNewTexture->width = pLoadingSurface->w;
	pNewTexture->height = pLoadingSurface->h;

    pNewTexture->animFrame.w = pNewTexture->width;
    pNewTexture->animFrame.h = pNewTexture->height;

	pNewTexture->pSDLTexture = SDL_CreateTextureFromSurface(pRenderer, pLoadingSurface);
	SDL_FreeSurface(pLoadingSurface);

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

    return nullptr;
}