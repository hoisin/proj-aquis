//--------------------------------------------------------------------------
//
//	19/03/2014
//
//	Template 3D vector
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>

namespace beng
{
	template<class T>
	class Vec3
	{
	public:
		Vec3(T inX, T inY, T inZ) : x(inX), y(inY), z(inZ)
		{
		}

		Vec3() : x(0), y(0), z(0)
		{
		}

		~Vec3()
		{
		}

		float Length() const
		{
			return std::sqrt( (float)(x*x + y*y + z*z) );
		}

		// Always assume to return a float version
		Vec3<float> Normalise()
		{
			float length = Length();
			return Vec3<float>(x/length, y/length, z/length);
		}


		//----------------------//
		//		Overloads		//
		//----------------------//

		Vec3<T> operator +(const Vec3<T> &other) const
		{
			return Vec3(x + other.x, y + other.y, z + other.z);
		}

		Vec3<T> operator -(const Vec3<T> &other) const
		{
			return Vec3(x - other.x, y - other.y, z - other.z);
		}

		Vec3<T> operator *(const Vec3<T> &other) const
		{
			return Vec3(x * other.x, y * other.y, z * other.z);
		}

		Vec3<T> operator /(const Vec3<T> &other) const
		{
			return Vec3(x / other.x, y / other.y, z / other.z);
		}

		void operator +=(const Vec3<T> &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}

		void operator -=(const Vec3<T> &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		void operator *=(const Vec3<T> &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
		}

		void operator /=(const Vec3<T> &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		}

		bool operator ==(const Vec3<T> &other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool operator !=(const Vec3<T> &other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

	public:
		T x, y, z;
	};

	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;
};

#endif