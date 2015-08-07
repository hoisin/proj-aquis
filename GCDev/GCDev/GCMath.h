/*
	04/08/2015

	Math crap.
	Stuff not complete, adding as we need....
*/

#ifndef __GCMATH_H__
#define __GCMATH_H__

namespace gcmath
{

	template<class T>
	class Vec2
	{
	public:
		template<typename T>
		Vec2(const Vec2<T>& other)
		{
			x = other.x;
			y = other.y;
		}

		template<typename T>
		Vec2(T _x, T _y)
		{
			x = _x;
			y = _y;
		}

		Vec2()
		{
			x = 0;
			y = 0;
		}

		~Vec2()
		{
		}

		template <typename T>
		inline bool operator==(const Vec2<T>& rhs)
		{
			return  (x == rhs.x && y == rhs.y);
		}

		template <typename T>
		inline bool operator!=(const Vec2<T>& rhs)
		{
			return !(*this == rhs);
		}

		template <typename T>
		inline void operator=(const Vec2<T>& other)
		{
			x = other.x;
			y = other.y;
			
		}

		template <typename T>
		inline Vec2<T> operator+(const Vec2<T>& rhs)
		{
			auto newVec = *this;
			newVec.x += rhs.x;
			newVec.y += rhs.y;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator-(const Vec2<T>& rhs)
		{
			auto newVec = *this;
			newVec.x -= rhs.x;
			newVec.y -= rhs.y;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator*(const Vec2<T>& rhs)
		{
			auto newVec = *this;
			newVec.x *= rhs.x;
			newVec.y *= rhs.y;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator/(const Vec2<T>& rhs)
		{
			auto newVec = *this;
			if (rhs.x > 0) newVec.x /= rhs.x;
			if (rhs.y > 0) newVec.y /= rhs.y;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator+(T val)
		{
			auto newVec = *this;
			newVec.x += val;
			newVec.y += val;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator-(T val)
		{
			auto newVec = *this;
			newVec.x -= val;
			newVec.y -= val;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator*(T val)
		{
			auto newVec = *this;
			newVec.x *= val;
			newVec.y *= val;
			return newVec;
		}

		template <typename T>
		inline Vec2<T> operator/(T val)
		{
			auto newVec = *this;
			newVec.x /= val;
			newVec.y /= val;
			return newVec;
		}

		template <typename T>
		inline Vec2<T>& operator+=(const Vec2<T>& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		template <typename T>
		inline Vec2<T>& operator-=(const Vec2<T>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		template <typename T>
		inline Vec2<T>& operator*=(const Vec2<T>& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;

			return *this;
		}

		template <typename T>
		inline Vec2<T>& operator/=(const Vec2<T>& rhs)
		{
			if (rhs.x > 0) x /= rhs.x;
			if (rhs.y > 0) y /= rhs.y;

			return *this;
		}
		
		template <typename T>
		inline Vec2<T> Normalize()
		{
			double den = x * x + y * y;
			x /= den;
			y /= den;
			return *this;
		}


	public:
		T x;
		T y;
	};


	template<class T>
	class Rect
	{
	public:
		template <typename T>
		Rect(const Rect<T>& other)
		{
			left = other.left;
			right = other.right;
			top = other.top;
			bottom = other.bottom;
		}

		template <typename T>
		Rect(T l, T r, T t, T b)
		{
			left = l;
			right = r;
			top = t;
			bottom = b;
		}

		Rect()
		{
			left = 0;
			right = 0;
			top = 0;
			bottom = 0;
		}

		~Rect()
		{
		}

		template <typename T>
		inline bool operator==(const Rect<T>& rhs)
		{
			return (left == rhs.left && right == rhs.right &&
				top == rhs.top && bottom == rhx.bottom);
		}

		template <typename T>
		inline bool operator!=(const Rect<T>& rhs)
		{
			return !(*this == rhs);
		}

		template <typename T>
		inline CRect<T>& operator+=(const Vec2<T>& rhs)
		{
			l += rhs.x;
			r += rhs.x;
			t += rhs.y;
			b += rhs.y;
		}

		template <typename T>
		bool Intersects(const Rect<T>& other)
		{
			if (left > other.right || top > other.bottom ||
				bottom < other.top || right < other.left)
				return false;

			return true;
		}

       
        int GetWidth()
        {
            return right - left;
        }

     
        int GetHeight()
        {
            return bottom - top;
        }


	public:
		T left;
		T right;
		T top;
		T bottom;
	};

}


#endif