/*
	10/08/2015

	Utility crap
*/

#ifndef __UTILITY_H__
#define __UTILITY_H__


#include "SDL.h"

namespace gcutility
{

	SDL_Rect CreateRect(int x, int y, int width, int height)
	{
		SDL_Rect sdlRect;
		sdlRect.x = x;
		sdlRect.y = y;
		sdlRect.w = width;
		sdlRect.h = height;

		return sdlRect;
	}

}

#endif