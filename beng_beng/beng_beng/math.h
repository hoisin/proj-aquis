//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Main math header
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------


#ifndef __MATH_H__
#define __MATH_H__

#include <cmath>
#include "Vec2.h"

namespace beng
{
	//--------------------------//
	//		Vec2 operations		//
	//--------------------------//
	template<typename T>
	float Dot(typename Vec2<T> a, typename Vec2<T> b)
	{
		return (float)(a.x * b.x + a.y * b.y);
	}

	template<typename T>
	float Angle(typename Vec2<T> a, typename Vec2<T> b)
	{
		return acos( Dot(a.Normalise(), b.Normalise()) );
	}
};


#endif