/*
	30/07/2015

	Implementation for graphics component

*/

#ifndef __CGFX_H__
#define __CGFX_H__

#include <string>
#include <SDL.h>

class CTextureManager;
class CTextDraw;

class CGfx
{
public:
	CGfx();
	~CGfx();

	bool Initialise(unsigned int winWidth, unsigned int winHeight, const std::string& winTitle,
		int winXPos = -1, int winYPos = -1);

	int LoadTexture(const std::string& textureFile);
    int LoadTexture(const std::string& texturFile, const SDL_Color& key);

	void BeginDraw(bool bClear = false, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);
	void EndDraw();

	void DrawRect(int posX, int posY, int width, int height, Uint8 r, Uint8 g, Uint8 b);
	void DrawRect(const SDL_Rect& drawRect, Uint8 r, Uint8 g, Uint8 b);

	void DrawTexture(int texIdx, int posX, int posY);
	void DrawTexture(int texIdx, const SDL_Rect& drawFrame, int posX, int posY);

	void GetTextureDimensions(int textureID, int& outWidth, int& outHeight);
	void GetTextureAnimFrameDimensions(int textureID, int& outWidth, int& outHeight);

	// Font drawing
	bool LoadFont(const std::string& fontFile, int fontSize);
	void DrawText(const std::string& text, int posX, int posY, const SDL_Color& textCol);
	unsigned int GetFontHeight();
	void GetTextSize(const std::string& text, int& outWidth, int& outHeight);

	int GetWindowWidth() { return m_winWidth; }
	int GetWindowHeight() { return m_winHeight; }

private:
	void Close();

private:
	SDL_Window*				m_pWindow;
	SDL_Surface*			m_pSurface;

	CTextureManager*		m_pTextureMgr;		// Texture manager
	CTextDraw*				m_pDrawText;		// Text drawing handler

	unsigned int			m_winWidth;
	unsigned int			m_winHeight;

	std::string				m_winTitle;
};


#endif
