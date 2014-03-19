//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Template 4D vector
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __VEC4_H__
#define __VEC4_H__

#include <cmath>

namespace beng
{
	template<class T>
	class Vec4
	{
	public:
		Vec4(T inX, T inY, T inZ, T inW) : x(inX), y(inY), z(inZ), w(inW)
		{
		}

		Vec4() : x(0), y(0), z(0), w(0)
		{
		}

		~Vec4()
		{
		}

		float Length() const
		{
			return std::sqrt( (float)(x*x + y*y + z*z + w*w) );
		}

		// Always assume to return a float version
		Vec4<float> Normalise()
		{
			float length = Length();
			return Vec4<float>(x/length, y/length, z/length, w/length);
		}


		//----------------------//
		//		Overloads		//
		//----------------------//

		Vec4<T> operator +(const Vec4<T> &other) const
		{
			return Vec4(x + other.x, y + other.y, z + other.z , w + other.w);
		}

		Vec4<T> operator -(const Vec4<T> &other) const
		{
			return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		Vec4<T> operator *(const Vec4<T> &other) const
		{
			return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		Vec4<T> operator /(const Vec4<T> &other) const
		{
			return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		void operator +=(const Vec4<T> &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
		}

		void operator -=(const Vec4<T> &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
		}

		void operator *=(const Vec4<T> &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
		}

		void operator /=(const Vec4<T> &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
		}

		bool operator ==(const Vec4<T> &other) const
		{
			return (x == other.x && y == other.y && z == other.z && w == other.w);
		}

		bool operator !=(const Vec4<T> &other) const
		{
			return (x != other.x || y != other.y || z != other.z || w != other.w);
		}

	public:
		T x, y, z, w;
	};

	typedef Vec4<int> Vec4i;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;
};

#endif