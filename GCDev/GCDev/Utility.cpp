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

	// Returns interpolated value between two values
	float LinearInterpolate(float startVal, float endVal, float interpVal)
	{
		return (startVal + ((endVal - startVal) * interpVal));
	}
}