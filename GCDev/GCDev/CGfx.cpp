#include "CGfx.h"

#include "SDL.h"
#include "CTextureManager.h"

CGfx::CGfx() : m_pWindow(nullptr), m_pSurface(nullptr), m_pTextureMgr(nullptr), 
m_winWidth(0), m_winHeight(0)
{
}


CGfx::~CGfx()
{
	Close();
}


//---------------------------------------------------------------------------
//
//	Intialise()
//
//	Descrition:
//	Initialises graphics component. Returns false if fails.
//
//---------------------------------------------------------------------------
bool CGfx::Initialise(unsigned int winWidth, unsigned int winHeight, const std::string& winTitle,
	int winXPos, int winYPos)
{
	m_winWidth = winWidth;
	m_winHeight = winHeight;

	if (winXPos == -1)
		winXPos = SDL_WINDOWPOS_UNDEFINED;

	if (winYPos == -1)
		winYPos = SDL_WINDOWPOS_UNDEFINED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;
	else
	{
		m_pWindow = SDL_CreateWindow(winTitle.c_str(), winXPos, winYPos, winWidth, winHeight,
			SDL_WINDOW_SHOWN);

		if (m_pWindow == nullptr)
			return false;
		else
			m_pSurface = SDL_GetWindowSurface(m_pWindow);
	}

	m_pTextureMgr = new CTextureManager;

	return true;
}

//---------------------------------------------------------------------------
//
//	LoadTexture()
//
//	Descrition:
//	Loads a texture. Returns the index/ID if loaded (-1 if not).
//
//---------------------------------------------------------------------------
int CGfx::LoadTexture(const std::string& textureFile)
{
	return m_pTextureMgr->LoadTexture("..\\Assets\\backgroundTest.bmp");
}


//---------------------------------------------------------------------------
//
//	DrawTexture()
//
//	Descrition:
//	Draws a texture
//
//---------------------------------------------------------------------------
void CGfx::DrawTexture()
{
	SDL_BlitSurface(m_pTextureMgr->GetTexture(0)->pSurface, NULL, m_pSurface, NULL);

	SDL_UpdateWindowSurface(m_pWindow);
}


//---------------------------------------------------------------------------
//
//	Close()
//
//	Descrition:
//	Cleans up graphics component and closes
//
//---------------------------------------------------------------------------
void CGfx::Close()
{
	if (m_pTextureMgr){
		delete m_pTextureMgr;
		m_pTextureMgr = nullptr;
	}

	if (m_pSurface) {
		SDL_FreeSurface(m_pSurface);
		m_pSurface = nullptr;
	}

	if (m_pWindow) {
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}
}