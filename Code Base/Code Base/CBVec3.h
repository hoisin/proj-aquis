/*
22/09/2015

Author: Matty

Template vector 3 class
*/


#ifndef __CBVEC3_H__
#define __CBVEC3_H__

namespace cbmath
{
	template <class T>
	class Vec3
	{
	public:
		template <typename T>
		Vec3(const Vec3<T>& other) : x(other.x), y(other.y), z(other.z)
		{
		}

		template <typename T>
		Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
		{
		}

		Vec3() : x(0), y(0), z(0)
		{
		}

		~Vec3()
		{
		}


		// ====================== Operators ======================
		template <typename T>
		inline bool operator ==(const Vec3<T>& rhs)
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z);
		}

		template <typename T>
		inline bool operator !=(const Vec3<T>& rhs)
		{
			return !(*this == rhs);
		}

		template <typename T>
		inline void operator =(const Vec3<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}

		template <typename T>
		inline Vec3<T> operator +(const Vec3<T>& rhs)
		{
			return Vec3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		template <typename T>
		inline Vec3<T> operator -(T val)
		{
			return Vec3<T>(x + val, y + val, z + val);
		}

		template <typename T>
		inline Vec3<T> operator *(const Vec3<T>& rhs)
		{
			return Vec3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		template <typename T>
		inline Vec3<T> operator *(T val)
		{
			return Vec3<T>(x *val, y * val, z * val);
		}

		template <typename T>
		inline Vec3<T> operator /(const Vec3<T>& rhs)
		{
			auto newVec = *this;
			if (rhs.x != 0) newVec.x /= rhs.x;
			if (rhs.y != 0) newVec.y /= rhs.y;
			if (rhs.z != 0) newVec.z /= rhs.z;
			return newVec;
		}

		template <typename T>
		inline Vec3<T> operator /(T val)
		{
			auto newVec = *this;
			if (val != 0) {
				newVec.x /= val;
				newVec.y /= val;
				newVec.z /= val;
			}
			return newVec;
		}

	public:
		T x;
		T y;
		T z;
	};
};

#endif