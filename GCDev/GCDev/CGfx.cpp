#include "CGfx.h"

#include "SDL.h"
#include "CTextureManager.h"
#include "CTextDraw.h"
#include "Utility.h"

CGfx::CGfx() : m_pWindow(nullptr), m_pSurface(nullptr), m_pTextureMgr(nullptr), m_pDrawText(nullptr),
m_winWidth(0), m_winHeight(0), m_winTitle("")
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
//	Params:
//	winWidth	-	The window width
//	winHeight	-	The window height
//	winTitle	-	The window title
//	winXPos		-	Initial X position of the window
//	winYPos		-	Initial Y position of the window
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

	// Position window to default position
	if (winXPos == -1)
		winXPos = SDL_WINDOWPOS_UNDEFINED;

	if (winYPos == -1)
		winYPos = SDL_WINDOWPOS_UNDEFINED;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;
	else
	{
		// Attempt to create the window
		m_pWindow = SDL_CreateWindow(winTitle.c_str(), winXPos, winYPos, winWidth, winHeight,
			SDL_WINDOW_SHOWN);

		// Fail if no window created
		if (m_pWindow == nullptr)
			return false;
		else
			m_pSurface = SDL_GetWindowSurface(m_pWindow);
	}

	// Init SDL_TTF for text drawing
	if (TTF_Init() == -1)
		return false;

	// Instantiate text drawer and texture manager
	m_pDrawText = new CTextDraw;
	m_pTextureMgr = new CTextureManager;

	return true;
}

//---------------------------------------------------------------------------
//
//	LoadTexture()
//
//	Params:
//	textureFile	-	Location of texture file
//
//	Descrition:
//	Loads a texture. Returns the index/ID if loaded (-1 if not).
//
//---------------------------------------------------------------------------
int CGfx::LoadTexture(const std::string& textureFile)
{
	return m_pTextureMgr->LoadTexture(textureFile);
}


//---------------------------------------------------------------------------
//
//	LoadTexture()
//
//	Params:
//	textureFile	-	Location of texture file
//	key			-	Colour key used to identify as alpha (transparent)
//
//	Descrition:
//	Loads a texture and applies alpha (transparent) to colours matching key.
//	Returns the index/ID if loaded (-1 if not).
//
//---------------------------------------------------------------------------
int CGfx::LoadTexture(const std::string& textureFile, const SDL_Color& key)
{
    return m_pTextureMgr->LoadTexture(textureFile, key);
}


//---------------------------------------------------------------------------
//
//	BeginDraw()
//
//	Params:
//	bClear	-	Flag whether to clear screen
//	r		-	Red component to clear screen to
//	g		-	Green component to clear screen to
//	b		-	Blue component to clear screen to
//
//	Descrition:
//	Called before attempting any drawing calls
//
//---------------------------------------------------------------------------
void CGfx::BeginDraw(bool bClear, Uint8 r, Uint8 g, Uint8 b)
{
	if (bClear)
		SDL_FillRect(m_pSurface, NULL, SDL_MapRGB(m_pSurface->format, r, g, b));
}


//---------------------------------------------------------------------------
//
//	EndDraw()
//
//	Descrition:
//	Called after all draw calls have been made. Presents drawn screen
//
//---------------------------------------------------------------------------
void CGfx::EndDraw()
{
	SDL_UpdateWindowSurface(m_pWindow);
}


//---------------------------------------------------------------------------
//
//	DrawRect()
//
//	Params:
//	posX	-	X position to draw rectangle
//	posY	-	Y position to draw rectangle
//	width	-	Width of the rectangle
//	height	-	Height of the rectangle
//	r		-	Red component of the rectangle
//	g		-	Green component of the rectangle
//	b		-	Blue component of the rectangle
//
//	Descrition:
//	Draws a rectangle
//
//---------------------------------------------------------------------------
void CGfx::DrawRect(int posX, int posY, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect tempRect = gcutility::CreateSDLRect(posX, posY, width, height);

	SDL_FillRect(m_pSurface, &tempRect, SDL_MapRGB(m_pSurface->format, r, g, b));
}


//---------------------------------------------------------------------------
//
//	DrawRect()
//
//	Params:
//	drawRect	-	Rectangle to draw
//	r			-	Red component of the rectangle
//	g			-	Green component of the rectangle
//	b			-	Blue component of the rectangle
//
//	Descrition:
//	Draws a rectangle
//
//---------------------------------------------------------------------------
void CGfx::DrawRect(const SDL_Rect& drawRect, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_FillRect(m_pSurface, &drawRect, SDL_MapRGB(m_pSurface->format, r, g, b));
}


//---------------------------------------------------------------------------
//
//	DrawTexture()
//
//	Params:
//	texIdx		- The texture index
//	posX		- X position to draw the texture
//	posY		- Y position to draw the texture
//
//	Descrition:
//	Draws the entire specified textures
//
//---------------------------------------------------------------------------
void CGfx::DrawTexture(int texIdx, int posX, int posY)
{
	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;

	SDL_BlitSurface(m_pTextureMgr->GetTexture(texIdx)->pSurface, NULL, m_pSurface, &dst);
}


//---------------------------------------------------------------------------
//
//	DrawTexture()
//
//	Params:
//	texIdx		- The texture index
//	drawFrame	- The specific area of the texture to draw
//	posX		- X position to draw the texture
//	posY		- Y position to draw the texture
//
//	Descrition:
//	Draws the specified area of texture to draw
//
//---------------------------------------------------------------------------
void CGfx::DrawTexture(int texIdx, const SDL_Rect& drawFrame, int posX, int posY)
{
	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;

	SDL_BlitSurface(m_pTextureMgr->GetTexture(texIdx)->pSurface, &drawFrame, m_pSurface, &dst);
}


//---------------------------------------------------------------------------
//
//	GetTextureDimensions()
//
//	Params:
//	texIdx		- The texture index
//	outWidth	- Returned width of whole texture
//	outHeight	- Returned height of whole texture
//
//	Descrition:
//	Returns the entire texture dimensions
//
//---------------------------------------------------------------------------
void CGfx::GetTextureDimensions(int textureID, int& outWidth, int& outHeight)
{
	outWidth = m_pTextureMgr->GetTexture(textureID)->width;
	outHeight = m_pTextureMgr->GetTexture(textureID)->height;
}


//---------------------------------------------------------------------------
//
//	GetTextureAnimFrameDimensions()
//
//	Params:
//	texIdx		- The texture index
//	outWidth	- Returned width of the animation frame rectangle
//	outHeight	- Returned height of he animation frame rectangle
//
//	Descrition:
//	Returns the dimenions of the animation rectangle
//
//---------------------------------------------------------------------------
void CGfx::GetTextureAnimFrameDimensions(int textureID, int& outWidth, int& outHeight)
{
	outWidth = m_pTextureMgr->GetTexture(textureID)->animFrame.w;
	outHeight = m_pTextureMgr->GetTexture(textureID)->animFrame.h;
}


//---------------------------------------------------------------------------
//
//	LoadFont()
//
//	Params:
//	fontFile	-	file location of font file
//	fontSize	-	size of the font to use
//
//	Descrition:
//	Loads font to use to draw text
//
//---------------------------------------------------------------------------
bool CGfx::LoadFont(const std::string& fontFile, int fontSize)
{
	if (m_pDrawText) {
		if (m_pDrawText->LoadFontTTF(fontFile, fontSize))
			return true;
	}
	
	return false;
}


//---------------------------------------------------------------------------
//
//	DrawText()
//
//	Params:
//	text		-	text to draw
//	posX		-	x positon to draw text
//	posY		-	y position to draw text
//	textCol		-	colour of text
//
//	Descrition:
//	Draws text
//
//---------------------------------------------------------------------------
void CGfx::DrawText(const std::string& text, int posX, int posY, const SDL_Color& textCol)
{
	if (m_pDrawText) {
		auto pTextSurface = m_pDrawText->RenderTextSolid(text, textCol);
		SDL_Rect dst;
		dst.x = posX;
		dst.y = posY;

		SDL_BlitSurface(pTextSurface, NULL, m_pSurface, &dst);
	}
}


//---------------------------------------------------------------------------
//
//	DrawText()
//
//	Descrition:
//	Returns height of single line of text
//
//---------------------------------------------------------------------------
unsigned int CGfx::GetFontHeight()
{
	if (m_pDrawText)
		return m_pDrawText->GetTextHeight();

	return 0;
}


//---------------------------------------------------------------------------
//
//	DrawText()
//
//	Params:
//	text		-	text to draw
//	outWidth	-	return width of text
//	outHeight	-	return height of text
//
//	Descrition:
//	Returns dimenions of specified text
//
//---------------------------------------------------------------------------
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

	if (m_pWindow) {
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}

	TTF_Quit();
}