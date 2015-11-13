/*
	22/09/2015

	Author: Matty

	Template vector 2 class
*/

#ifndef CBVEC2_H_
#define CBVEC2_H_

namespace cbmath
{

	template<class T>
	class Vec2
	{
	public:
		template<typename T>
		Vec2(const Vec2<T>& other) : x(other.x), y(other.y)
		{
		}

		template<typename T>
		Vec2(T _x, T _y) : x(_x), y(_y)
		{
		}

		Vec2() : x(0), y(0)
		{
		}

		~Vec2()
		{
		}


		// ========================= Operators =========================
		template<typename T>
		inline bool operator ==(const Vec2<T>& rhs)
		{
			return (x == rhs.x && y == rhs.y);
		}

		template<typename T>
		inline bool operator !=(const Vec2<T>& rhs)
		{
			return !(*this == rhs);
		}

		template <typename T>
		inline void operator =(const Vec2<T> rhs)
		{
			x = rhs.x; y = rhs.y;
		}

		template <typename T>
		inline Vec2<T> operator +(const Vec2<T>& rhs)
		{
			return Vec2<T>(x + rhs.x, y + rhs.y);
		}

		template <typename T>
		inline Vec2<T> operator +(T val)
		{
			return Vec2<T>*(x + val, y + val);
		}

		template <typename T>
		inline Vec2<T> operator -(const Vec2<T>& rhs)
		{
			return Vec<T>(x - rhs.x, y - rhs.y);
		}
		
		template <typename T>
		inline Vec2<T> operator -(T val)
		{
			return Vec2<T>(x - val, y - val);
		}

		template <typename T>
		inline Vec2<T> operator *(const Vec2<T>& rhs)
		{
			return Vec<T>(x * rhs.x, y * rhs.y);
		}

		template <typename T>
		inline Vec2<T> operator *(T val)
		{
			return Vec2<T>(x * val, y * val)
		}

		template <typename T>
		inline Vec2<T> operator /(const Vec2<T>& rhs)
		{
			auto newVec = *this;
			if (rhs.x != 0) newVec.x /= rhs.x;
			if (rhs.y != 0) newVec.y /= rhs.y;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator /(T val)
		{
			auto newVec = *this;
			if (val != 0) {
				newVec.x /= val;
				newVec.y /= val;
			}
			return newVec;
		}

		template <typename T>
		inline void operator +=(const Vec2<T>& rhs)
		{
			x += rhs.x; y += rhs.y;
		}

		template <typename T>
		inline void operator +=(T val)
		{
			x += val; y += val;
		}

		template <typename T>
		inline void operator-=(const Vec2<T>& rhs)
		{
			x -= rhs.x; y -= rhs.y;
		}

		template <typename T>
		inline void operator -=(T val)
		{
			x -= val; y -= val;
		}

		template <typename T>
		inline void operator*=(const Vec2<T>& rhs)
		{
			x *= rhs.x; y *= rhs.y;
		}

		template <typename T>
		inline void operator *=(T val)
		{
			x *= val; y *= val;
		}


		template <typename T>
		inline void operator /=(const Vec2<T>& rhs)
		{
			if (rhs.x != 0) x /= rhs.x;
			if (rhs.y != 0) y /= rhs.y;
		}

		template <typename T>
		inline void operator /=(T val)
		{
			if (val != 0) {
				x /= val;
				y /= val;
			}
		}


		// ================== Extra methods ==================

		template <typename T>
		T Length()
		{
			return sqrt((x * x) + (y * y));
		}

		void Normalise()
		{
			T mag = sqrt((x * x) + (y * y));
			if (mag > 0) {
				x /= mag;
				y /= mag;
			}
		}

		template <typename T>
		T Dot(const Vec2<T>& other)
		{
			return ((x * other.x) + (y * other.y));
		}

	public:
		T x;
		T y;
	};
}


#endif