#include "CTextDraw.h"


CTextDraw::CTextDraw() : m_pFont(nullptr)
{
}


CTextDraw::~CTextDraw()
{
	if (m_pRenderedText) {
		SDL_FreeSurface(m_pRenderedText);
		m_pRenderedText = nullptr;
	}

	if (m_pFont) {
		TTF_CloseFont(m_pFont);
		m_pFont = nullptr;
	}
}


bool CTextDraw::LoadFontTTF(const std::string& fontFile, int fontSize)
{
	m_pFont = TTF_OpenFont(fontFile.c_str(), fontSize);

	if (m_pFont == NULL)
		return false;

	return true;
}


SDL_Surface* CTextDraw::RenderTextSolid(const std::string& text, const SDL_Color textCol)
{
	if (m_pFont) {
		if (m_pRenderedText) {
			SDL_FreeSurface(m_pRenderedText);
			m_pRenderedText = nullptr;
		}

		m_pRenderedText = TTF_RenderText_Solid(m_pFont, text.c_str(), textCol);

		return m_pRenderedText;
	}

	return nullptr;
}


SDL_Surface* CTextDraw::RenderTextShaded(const std::string& text, const SDL_Color textCol,
	const SDL_Color fgCol, const SDL_Color bgCol)
{
	if (m_pFont) {
		if (m_pRenderedText) {
			SDL_FreeSurface(m_pRenderedText);
			m_pRenderedText = nullptr;
		}

		m_pRenderedText = TTF_RenderText_Shaded(m_pFont, text.c_str(), fgCol, bgCol);

		return m_pRenderedText;
	}

	return nullptr;
}


SDL_Surface* CTextDraw::RenderTextBlended(const std::string& text, SDL_Color fgCol)
{
	if (m_pFont) {
		if (m_pRenderedText) {
			SDL_FreeSurface(m_pRenderedText);
			m_pRenderedText = nullptr;
		}

		m_pRenderedText = TTF_RenderText_Blended(m_pFont, text.c_str(), fgCol);

		return m_pRenderedText;
	}

	return nullptr;
}


Uint16 CTextDraw::GetTextHeight()
{
	if (m_pFont)
		return TTF_FontHeight(m_pFont);

	return 0;
}


void CTextDraw::GetTextSize(const std::string& text, int& outWidth, int& outHeight)
{
	if (m_pFont)
		TTF_SizeText(m_pFont, text.c_str(), &outWidth, &outHeight);
	else
	{
		outWidth = 0;
		outHeight = 0;
	}
}