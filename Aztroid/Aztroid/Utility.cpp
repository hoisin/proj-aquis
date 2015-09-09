#include "Utility.h"

namespace gcutility
{
	SDL_Rect CreateSDLRect(int x, int y, int width, int height)
	{
		SDL_Rect sdlRect;
		sdlRect.x = x;
		sdlRect.y = y;
		sdlRect.w = width;
		sdlRect.h = height;

		return sdlRect;
	}


	SDL_Color CreateSDLColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		SDL_Color sdlCol;
		sdlCol.r = r;
		sdlCol.g = g;
		sdlCol.b = b;
		sdlCol.a = 0;

		return sdlCol;
	}
}