#include "CGfx.h"

#include "SDL.h"
#include "CTextureManager.h"
#include "CTextDraw.h"
#include "Utility.h"

CGfx::CGfx() : m_pWindow(nullptr), m_pSurface(nullptr), m_pTextureMgr(nullptr), m_pDrawText(nullptr),
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
	m_winTitle = winTitle;

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
			m_pMainRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
			//m_pSurface = SDL_GetWindowSurface(m_pWindow);
	}

	// Init SDL_TTF
	if (TTF_Init() == -1)
		return false;

	m_pDrawText = new CTextDraw;

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
	return m_pTextureMgr->LoadTexture(textureFile, m_pMainRenderer);
}


int CGfx::LoadTexture(const std::string& textureFile, const SDL_Color& key)
{
    return m_pTextureMgr->LoadTexture(textureFile, m_pMainRenderer, key);
}


void CGfx::BeginDraw(bool bClear, Uint8 r, Uint8 g, Uint8 b)
{
	if (bClear) {
		SDL_SetRenderDrawColor(m_pMainRenderer, r, g, b, 0);
		SDL_RenderClear(m_pMainRenderer);
	}
}


void CGfx::EndDraw()
{
	SDL_RenderPresent(m_pMainRenderer);
}


void CGfx::DrawRect(int posX, int posY, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect tempRect = gcutility::CreateSDLRect(posX, posY, width, height);

	SDL_SetRenderDrawColor(m_pMainRenderer, r, g, b, 255);
	SDL_RenderFillRect(m_pMainRenderer, &tempRect);
}


void CGfx::DrawRect(const SDL_Rect& drawRect, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(m_pMainRenderer, r, g, b, 255);
	SDL_RenderFillRect(m_pMainRenderer, &drawRect);
}


void CGfx::DrawTexture(int texIdx, int posX, int posY, double angleDegree, SDL_RendererFlip flip,
	int centerRotX, int centerRotY)
{
	SDL_Rect dst; 
	dst.x = posX;
	dst.y = posY;
	dst.w = m_pTextureMgr->GetTexture(texIdx)->width;
	dst.h = m_pTextureMgr->GetTexture(texIdx)->height;

	SDL_Point point;
	point.x = (dst.w / 2) + centerRotX;
	point.y = (dst.h / 2) + centerRotY;

	SDL_RenderCopyEx(m_pMainRenderer, m_pTextureMgr->GetTexture(texIdx)->pSDLTexture, NULL, &dst, angleDegree, &point, flip);
}


void CGfx::DrawTexture(int texIdx, const SDL_Rect& drawFrame, int posX, int posY, double angleDegree, SDL_RendererFlip flip,
	int centerRotX, int centerRotY)
{
	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.w = drawFrame.w;
	dst.h = drawFrame.h;

	SDL_Point point;
	point.x = (dst.w / 2) + centerRotX;
	point.y = (dst.h / 2) + centerRotY;

	SDL_RenderCopyEx(m_pMainRenderer, m_pTextureMgr->GetTexture(texIdx)->pSDLTexture, &drawFrame, &dst, angleDegree, &point, flip);
}


void CGfx::GetTextureDimensions(int textureID, int& outWidth, int& outHeight)
{
	outWidth = m_pTextureMgr->GetTexture(textureID)->width;
	outHeight = m_pTextureMgr->GetTexture(textureID)->height;
}


void CGfx::GetTextureAnimFrameDimensions(int textureID, int& outWidth, int& outHeight)
{
	outWidth = m_pTextureMgr->GetTexture(textureID)->animFrame.w;
	outHeight = m_pTextureMgr->GetTexture(textureID)->animFrame.h;
}


bool CGfx::LoadFont(const std::string& fontFile, int fontSize)
{
	if (m_pDrawText) {
		if (m_pDrawText->LoadFontTTF(fontFile, fontSize))
			return true;
	}
	
	return false;
}


void CGfx::DrawText(const std::string& text, int posX, int posY, const SDL_Color& textCol)
{
	if (m_pDrawText) {
		auto pTextSurface = m_pDrawText->RenderTextSolid(text, textCol);
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pMainRenderer, pTextSurface);
		
		SDL_Rect dst;
		dst.x = posX;
		dst.y = posY;

		SDL_RenderCopy(m_pMainRenderer, pTexture, NULL, &dst);

		SDL_FreeSurface(pTextSurface);
		SDL_DestroyTexture(pTexture);
		//SDL_BlitSurface(pTextSurface, NULL, m_pSurface, &dst);
	}
}


unsigned int CGfx::GetFontHeight()
{
	if (m_pDrawText)
		return m_pDrawText->GetTextHeight();

	return 0;
}


void CGfx::GetTextSize(const std::string& text, int& outWidth, int& outHeight)
{
	if (m_pDrawText)
		m_pDrawText->GetTextSize(text, outWidth, outHeight);
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

	if (m_pDrawText) {
		delete m_pDrawText;
		m_pDrawText = nullptr;
	}

	if (m_pSurface) {
		SDL_FreeSurface(m_pSurface);
		m_pSurface = nullptr;
	}

	if (m_pMainRenderer) {
		SDL_DestroyRenderer(m_pMainRenderer);
		m_pMainRenderer = nullptr;
	}

	if (m_pWindow) {
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}

	TTF_Quit();
}