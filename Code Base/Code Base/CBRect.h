/*
	28/09/2015

	Author: Matty

	Rectangle class.
	Assumptions:
	Left is decreasing and right is increasing.
	Going up is decreasing and going down is increasing.
	Therefore a rectangle of size (10, 10) at position (0,0):
	Left = 0
	Top = 0
	Right = 10
	Bottom = 10
*/


#ifndef __CBRECTANGLE_H__
#define __CBRECTANGLE_H__


namespace cbmath
{
	template <class T>
	class Rect
	{
	public:
		template <typename T>
		Rect(const Rect<T>& other) : left(other.left), top(other.top),
			right(other.right), bottom(other.bottom)
		{
		}

		template <typename T>
		Rect(T _left, T _top, T _right, T _bottom) : left(_left), top(_top),
			right(_right), bottom(_bottom)
		{
		}

		Rect() : left(0), top(0), right(0), bottom(0)
		{
		}

		~Rect()
		{
		}

		template <typename T>
		bool operator ==(const Rect<T>& rhs)
		{
			return (left == rhs.left && top == rhs.top &&
				right == rhs.right && bottom == rhs.bottom);
		}

		template <typename T>
		bool operator !=(const Rect<T>& rhs)
		{
			return !(*this == rhs);
		}

		template <typename T>
		T GetWidth()
		{
			return (right - left);
		}

		template <typename T>
		T GetHeight()
		{
			return (bottom - top);
		}

		// This only checks for intersection.
		// Will flag true if other rectangle is completely inside.
		template <typename T>
		bool IsIntersect(const Rect<T>& other)
		{
			return (right <= other.left || left >= other.right ||
				bottom <= other.top || top >= other.bottom);
		}

		// Checks if passed in rect is completely inside of current rect
		template <typename T>
		bool IsContained(const Rect<T>& other)
		{
			return (left < other.left && right > other.right &&
				top < other.top && bottom > other.bottom);
		}

		template <typename T>
		void GetCenterPoint(T& x, T& y)
		{
			x = GetWidth<T>() / 2;
			y = GetHeight<T>() / 2;
		}

	public:
		T left;
		T top;
		T right;
		T bottom;
	};
};


#endif