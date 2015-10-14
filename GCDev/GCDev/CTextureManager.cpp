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




// ================================ CTextureManager ===================================


CTextureManager::CTextureManager()
{
	m_pTextures = std::vector<CTexture*>();
}


CTextureManager::~CTextureManager()
{
}


//---------------------------------------------------------------------------
//
//	LoadTexture()
//
//	Params:
//	fileName	-	texture file location
//	pOutTexture -	return handle of loaded texture
//
//	Descrition:
//	Loads specified texture, returns the stored index position in vector
//
//---------------------------------------------------------------------------
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

	pNewTexture->animFrame.w = pNewTexture->width;
	pNewTexture->animFrame.h = pNewTexture->height;

	m_pTextures.push_back(pNewTexture);

	return m_pTextures.size() - 1;
}


//---------------------------------------------------------------------------
//
//	LoadTexture()
//
//	Params:
//	fileName	-	texture file location
//	key			-	colour key used to ID alpha (transparency)
//	pOutTexture -	return handle of loaded texture
//
//	Descrition:
//	Loads specified texture with alpha key,
//	returns the stored index position in vector
//
//---------------------------------------------------------------------------
int CTextureManager::LoadTexture(const std::string& fileName, SDL_Color key, CTexture* pOutTexture)
{
    CTexture* pNewTexture = new CTexture;

    pNewTexture->pSurface = SDL_LoadBMP(fileName.c_str());

    // Clean up if failed load
    if(pNewTexture->pSurface == nullptr) {
        delete pNewTexture;
        pNewTexture = nullptr;
        return -1;
    }

    Uint32 colourKey = SDL_MapRGB(pNewTexture->pSurface->format, key.r, key.g, key.b);

    SDL_SetColorKey(pNewTexture->pSurface, 1, colourKey);

    pNewTexture->width = pNewTexture->pSurface->w;
    pNewTexture->height = pNewTexture->pSurface->h;

    pNewTexture->animFrame.w = pNewTexture->width;
    pNewTexture->animFrame.h = pNewTexture->height;

    m_pTextures.push_back(pNewTexture);

    return m_pTextures.size() - 1;
}


//---------------------------------------------------------------------------
//
//	SetTextureAnimationFrame()
//
//	Params:
//	texIdx	-	texture index
//	width	-	width of the animation rectangle
//	height	-	height of the animation rectangle
//
//	Descrition:
//	Sets the animation rectangle size
//
//---------------------------------------------------------------------------
void CTextureManager::SetTextureAnimationFrame(Uint16 texIdx, Uint16 width, Uint16 height)
{
	if (texIdx < m_pTextures.size()) {
		SDL_Rect frameRect;
		frameRect.w = width;
		frameRect.h = height;
		m_pTextures[texIdx]->animFrame = frameRect;
	}
}


//---------------------------------------------------------------------------
//
//	AddTotalFrames()
//
//	Params:
//	texIdx		-	texture index
//	totalFrames	-	total of frames for new animation sequence
//
//	Descrition:
//	Adds data for new animation sequence
//
//---------------------------------------------------------------------------
void CTextureManager::AddTotalFrames(Uint16 texIdx, Uint16 totalFrames)
{
	if (texIdx < m_pTextures.size()) {
		m_pTextures[texIdx]->rowTotalFrames.push_back(totalFrames);
	}
}


//---------------------------------------------------------------------------
//
//	GetTotalFramesRow()
//
//	Params:
//	texIdx		-	texture index
//	animRow		-	which animation sequence to query
//
//	Descrition:
//	Returns the total frame of animation for specified animation sequence
//
//---------------------------------------------------------------------------
Uint16 CTextureManager::GetTotalFramesRow(Uint16 texIdx, Uint16 animRow)
{
	if (texIdx < m_pTextures.size()) {
		return m_pTextures[texIdx]->rowTotalFrames[animRow];
	}

	return 0;
}


//---------------------------------------------------------------------------
//
//	GetTexture()
//
//	Params:
//	texIdx		-	texture index
//
//	Descrition:
//	Returns specified texture
//
//---------------------------------------------------------------------------
CTexture* CTextureManager::GetTexture(Uint16 texIdx)
{
	if (texIdx < m_pTextures.size()) {
		return m_pTextures[texIdx];
	}

    return nullptr;
}