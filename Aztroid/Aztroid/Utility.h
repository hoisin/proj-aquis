/*
	10/08/2015

	Utility crap
*/
#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "SDL.h"
#include "GCMath.h"

namespace gcutility
{
	template <typename T>
	SDL_Rect CreateSDLRect(const gcmath::Rect<T>& rect)
	{
		SDL_Rect newRect;
		newRect.x = rect.left;
		newRect.y = rect.top;
		newRect.w = rect.GetWidth<T>();
		newRect.h = rect.GetHeight<T>();

		return newRect;
	}

	SDL_Rect CreateSDLRect(int x, int y, int width, int height);

	SDL_Color CreateSDLColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	
	double GetRadians(float degrees);
	double GetDegrees(float radians);

	float LinearInterpolate(float startVal, float endVal, float interpVal);

	int ClampValue(int inVal, int minClamp, int maxClamp);
}

#endif