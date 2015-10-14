/*
	Uses SDL_TFF to draw text.

	Expansion to perform custom draw text (from sprite sheets)
*/

#ifndef __CTEXTDRAW_H__
#define __CTEXTDRAW_H__

#include <string>

#include "SDL_ttf.h"

class CTextDraw
{
public:
	CTextDraw();
	~CTextDraw();

	bool LoadFontTTF(const std::string& fontFile, int fontSize);

	// Renders text
	SDL_Surface* RenderTextSolid(const std::string& text, const SDL_Color textCol);

	// Renders text with foreground and background colour
	SDL_Surface* RenderTextShaded(const std::string& text, const SDL_Color textCol,
		const SDL_Color fgCol, const SDL_Color bgCol);

	// Renders text with foreground colour
	SDL_Surface* RenderTextBlended(const std::string& text, const SDL_Color fgCol);

	SDL_Surface* GetRenderedText() { return m_pRenderedText; }

	Uint16 GetTextHeight();
	void GetTextSize(const std::string& text, int& outWidth, int& outHeight);

private:
	TTF_Font* m_pFont;				
	SDL_Surface* m_pRenderedText;	// The rendered text as a surface
};

#endif