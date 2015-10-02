/*
	28/09/2015

	Author: Matty

	Rectangle class.
*/

#ifndef __CBCIRCLE_H__
#define __CBCIRCLE_H__

#include <math.h>

namespace cbmath
{
	template <class T>
	class Circle
	{
	public:
		template <typename T>
		Circle(const Circle<T>& other) : radius(other.radius), x(other.x), y(other.y)
		{
		}

		template <typename T>
		Circle(T _radius, T _x, T_y) : radius(_radius), x(_x), y(_y)
		{
		}

		Circle() : radius(0), x(0), y(0)
		{
		}

		~Circle()
		{
		}

		template <typename T>
		bool operator ==(const Circle<T>& rhs)
		{
			return (radius == rhs.radius && x == rhs.x && y == rhs.y);
		}

		template <typename T>
		bool operator != (const Circle<T>& rhs)
		{
			return !(*this == rhs);
		}

		template <typename T>
		bool IsIntersect(const Circle<T>& other)
		{
			T pX = abs(x - other.x);
			T pY = abs(y - other.y);
			T length = sqrt((pX * pX + pY * pY));
			return (length < (radius + other.radius));
		}

		template <typename T>
		bool IsContained(const Circle<T>& other)
		{
			T pX = abs(x - other.x);
			T pY = abs(y - other.y);
			T length = sqrt((pX * pX + pY * pY));
			return (radius > (length + other.radius));
		}

		template <typename T>
		T GetDiameter()
		{
			return radius * radius;
		}

	public:
		T radius;
		T x;
		T y;
	};
};


#endif