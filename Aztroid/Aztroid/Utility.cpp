#include "Utility.h"

#include <math.h>

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


	double GetRadians(float degrees)
	{
		return degrees * (M_PI / 180);
	}

	
	double GetDegrees(float radians)
	{
		return radians * (180 / M_PI);
	}


	// Returns interpolated value between two values
	float LinearInterpolate(float startVal, float endVal, float interpVal)
	{
		return (startVal + ((endVal - startVal) * interpVal));
	}

	int ClampValue(int inVal, int minClamp, int maxClamp)
	{
		if (inVal < minClamp)
			return (inVal += abs(minClamp));

		if (inVal > maxClamp)
			return (inVal -= abs(maxClamp));

		// Do nothing if input value does not exceed limits
		return inVal;
	}
}