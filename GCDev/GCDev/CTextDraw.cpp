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


//---------------------------------------------------------------------------
//
//	LoadFontTTF()
//
//	Params:
//	fontFile	-	directory to font file
//	fontSize	-	Size of the font
//
//	Descrition:
//	Loads font to use for drawing text
//
//---------------------------------------------------------------------------
bool CTextDraw::LoadFontTTF(const std::string& fontFile, int fontSize)
{
	m_pFont = TTF_OpenFont(fontFile.c_str(), fontSize);

	if (m_pFont == NULL)
		return false;

	return true;
}


//---------------------------------------------------------------------------
//
//	RenderTextSolid()
//
//	Params:
//	text	-	text to draw
//	textCol	-	colour of the text
//
//	Descrition:
//	Renders text as solid
//
//---------------------------------------------------------------------------
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


//---------------------------------------------------------------------------
//
//	RenderTextShaded()
//
//	Params:
//	text	-	text to draw
//	textCol	-	colour of the text
//	fcCol	-	colour of foreground
//	bgCol	-	colour of background
//
//	Descrition:
//	Renders text with a foreground and background colour
//
//---------------------------------------------------------------------------
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


//---------------------------------------------------------------------------
//
//	RenderTextBlended()
//
//	Params:
//	text	-	text to draw
//	textCol	-	colour of the text
//	fcCol	-	colour of foreground
//
//	Descrition:
//	Renders text with a foreground colour
//
//---------------------------------------------------------------------------
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


//---------------------------------------------------------------------------
//
//	GetTextHeight()
//
//	Descrition:
//	Returns the height of a single line of text
//
//---------------------------------------------------------------------------
Uint16 CTextDraw::GetTextHeight()
{
	if (m_pFont)
		return TTF_FontHeight(m_pFont);

	return 0;
}


//---------------------------------------------------------------------------
//
//	GetTextSize()
//
//	Params:
//	text		-	text to measure
//	outWidth	-	output of width of passed text
//	outHeight	-	output of the height of passed text
//
//	Descrition:
//	Returns the total dimensions of the passed in string of text
//
//---------------------------------------------------------------------------
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