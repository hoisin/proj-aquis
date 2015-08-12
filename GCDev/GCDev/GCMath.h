/*
	04/08/2015

	Math crap.
	Stuff not complete, adding as we need....
*/

#ifndef __GCMATH_H__
#define __GCMATH_H__

namespace gcmath
{
	//-------------------------------------------------------------------------
	//	Vector 2
	//-------------------------------------------------------------------------
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
		inline Vec2<T> operator=(const Vec2<T>& other)
		{
			x = other.x;
			y = other.y;
			return *this;
			
		}

		template <typename T>
		inline Vec2<T> operator+(const Vec2<T>& rhs)
		{
			return Vec2<T>(x + rhs.x, y + rhs.y);
		}

		template <typename T>
		inline Vec2<T> operator-(const Vec2<T>& rhs)
		{
			return Vec2<T>(x - rhs.x, y - rhs.y);;
		}

		template <typename T>
		inline Vec2<T> operator*(const Vec2<T>& rhs)
		{
			return Vec2<T>(x * rhs.x, y * rhs.y);
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
			return Vec2<T>(x + val, y + val);
		}

		template <typename T>
		inline Vec2<T> operator-(T val)
		{
			return Vec2<T>(x - val, y - val);;
		}

		template <typename T>
		inline Vec2<T> operator*(T val)
		{
			return Vec2<T>(x * val, y * val);;
		}

		template <typename T>
		inline Vec2<T> operator/(T val)
		{
			auto newVec = *this;
			if (val != 0)  {
				newVec.x /= val;
				newVec.y /= val;
			}
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
		inline Vec2<T>& operator*=(T val)
		{
			x *= val;
			y *= val;
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


	//-------------------------------------------------------------------------
	//	Rectangle
	//-------------------------------------------------------------------------

	enum EdgeType {
		ELeft,
		ERight,
		ETop,
		EBottom,
		EInvalid,
		ETotalEdges
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
		inline Rect<T>& operator=(const Rect<T>& other)
		{
			left = other.left;
			right = other.right;
			top = other.top;
			bottom = other.bottom;

			return *this;
		}

		template <typename T>
		inline Rect<T>& operator+=(const Vec2<T>& rhs)
		{
			left += rhs.x;
			right += rhs.x;
			top += rhs.y;
			bottom += rhs.y;

			return *this;
		}

		template <typename T>
		bool Intersects(const Rect<T>& other)
		{
			if (left >= other.right || top >= other.bottom ||
				bottom <= other.top || right <= other.left)
				return false;

			return true;
		}

		template <typename T>
		inline bool IsContained(const Rect<T>& other)
		{
			// Determines if other rectangle it completely inside
			// (no intersects)
			return (left <= other.left &&
				right >= other.right &&
				top <= other.top &&
				bottom >= other.bottom);
		}

		template <typename T>
		inline Rect<T> MoveInside(const Rect<T>& other)
		{
			auto outRect = other;

			if ((outRect.right - outRect.left) > (right - left) || (outRect.bottom - outRect.top) > (bottom - top))
				return outRect;

			if (outRect.left < left) {
				auto diff = left - outRect.left;
				outRect.left += diff;
				outRect.right += diff;
			}

			if (outRect.right > right) {
				auto diff = outRect.right - right;
				outRect.left -= diff;
				outRect.right -= diff;
			}

			if (outRect.top < top) {
				auto diff = top - outRect.top;
				outRect.top += diff;
				outRect.bottom += diff;
			}

			if (outRect.bottom > bottom) {
				auto diff = outRect.bottom - bottom;
				outRect.top -= diff;
				outRect.bottom -= diff;
			}

			return outRect;
		}

		template <typename T>
		inline Rect<T> MoveOutside(const Rect<T>& other, T offset = 0)
		{
			auto outRect = other;

			// If left side
			if (outRect.left < left && outRect.right > left) {
				int diff = (outRect.right - left) + offset;
				outRect.left -= diff;
				outRect.right -= diff;
			}

			// If right side
			if (outRect.left < right && outRect.right > right) {
				int diff = (right - outRect.left) + offset;
				outRect.left += diff;
				outRect.right += diff;
			}

			// If top side
			if (outRect.top < top && outRect.bottom > top) {
				int diff = (outRect.bottom - top) + offset;
				outRect.top -= diff;
				outRect.bottom -= diff;
			}

			// If bottom side
			if (outRect.top < bottom && outRect.bottom > bottom) {
				int diff = (bottom - outRect.top) + offset;
				outRect.top += diff;
				outRect.right += diff;
			}

			return outRect;
		}

		template <typename T>
		bool IsIntersectingEdge(const Rect<T>& rect, EdgeType edge)
		{
			if (!Intersects(rect))
				return false;

			switch (edge) {
			case EdgeType::ELeft:
				if (rect.left < left)
					return true;
				break;

			case EdgeType::ERight:
				if (rect.right > right)
					return true;
				break;

			case EdgeType::ETop:
				if (rect.top < top)
					return true;
				break;

			case EdgeType::EBottom:
				if (rect.bottom > bottom)
					return true;
				break;

			default:
				break;
			}

			return false;
		}

		template <typename T>
        T GetWidth() const
        {
            return right - left;
        }

		template <typename T>
        T GetHeight() const
        {
            return bottom - top;
        }

	public:
		T left;
		T right;
		T top;
		T bottom;
	};


	//-------------------------------------------------------------------------
	//	Circle
	//-------------------------------------------------------------------------

	template <class T>
	class Circle
	{
	public: 
		template <typename T>
		Circle(const Circle<T>& other) : x(other.x), y(other.y), radius(other.radius)
		{
		}

		template <typename T>
		Circle(T xPos, T yPos, T rad) : : x(xPos), y(yPos), radius(rad)
		{
		}

		template <typename T>
		Circle() : x(0), y(0), radius(0)
		{
		}

		~Circle()
		{
		}

	public:
		T x;
		T y;
		T radius;
	};

}


#endif