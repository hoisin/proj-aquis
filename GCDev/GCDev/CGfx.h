/*
	30/07/2015

	Implementation for graphics component

*/

#ifndef __CGFX_H__
#define __CGFX_H__

#include <string>
#include <SDL.h>

class CTextureManager;

class CGfx
{
public:
	CGfx();
	~CGfx();

	bool Initialise(unsigned int winWidth, unsigned int winHeight, const std::string& winTitle,
		int winXPos = -1, int winYPos = -1);

	int LoadTexture(const std::string& textureFile);

	void DrawTexture();

private:
	void Close();

private:
	SDL_Window*				m_pWindow;
	SDL_Surface*			m_pSurface;

	CTextureManager*		m_pTextureMgr;

	unsigned int			m_winWidth;
	unsigned int			m_winHeight;

	std::string				m_winTitle;
};


#endif
