//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Template 2D vector
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>

namespace beng
{
	template<class T>
	class Vec2
	{
	public:
		Vec2(T inX, T inY) : x(inX), y(inY)
		{
		}

		Vec2() : x(0), y(0)
		{
		}

		~Vec2()
		{
		}

		float Length() const
		{
			return std::sqrt( (float)(x*x + y*y) );
		}

		// Always assume to return a float version
		Vec2<float> Normalise()
		{
			float length = Length();
			return Vec2<float>(x/length, y/length);
		}

		//----------------------//
		//		Overloads		//
		//----------------------//

		Vec2<T> operator +(const Vec2<T> &other) const
		{
			return Vec2(x + other.x, y + other.y);
		}

		Vec2<T> operator -(const Vec2<T> &other) const
		{
			return Vec2(x - other.x, y - other.y);
		}

		Vec2<T> operator *(const Vec2<T> &other) const
		{
			return Vec2(x * other.x, y * other.y);
		}

		Vec2<T> operator /(const Vec2<T> &other) const
		{
			return Vec2(x / other.x, y / other.y);
		}

		void operator +=(const Vec2<T> &other)
		{
			x += other.x;
			y += other.y;
		}

		void operator -=(const Vec2<T> &other)
		{
			x -= other.x;
			y -= other.y;
		}

		void operator *=(const Vec2<T> &other)
		{
			x *= other.x;
			y *= other.y;
		}

		void operator /=(const Vec2<T> &other)
		{
			x /= other.x;
			y /= other.y;
		}

		bool operator ==(const Vec2<T> &other) const
		{
			return (x == other.x && y == other.y);
		}

		bool operator !=(const Vec2<T> &other) const
		{
			return (x != other.x || y != other.y);
		}

	public:
		T x;
		T y;
	};

	typedef Vec2<int> Vec2i;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;		// For what we're doing, most of the time we won't need it to be double
};


#endif