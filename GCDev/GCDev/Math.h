/*
	04/08/2015

	Header for including all custom math classes
*/

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
	Vec2<T>& operator=(const Vec2<T>& other)
	{
		x = other.x;
		y = other.y;
		return this;
	}
	
	template <typename T>
	Vec2<T>& operator+(const Vec2<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template <typename T>
	Vec2<T>& operator-(const Vec2<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template <typename T>
	Vec2<T>& operator*(const Vec2<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	template <typename T>
	Vec2<T>& operator/(const Vec2<T>& rhs)
	{
		if(rhs.x > 0) x /= rhs.x;
		if(rhs.y > 0) y /= rhs.y;
		return *this;
	}

	template <typename T>
	void operator+=(const Vec2<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}

	template <typename T>
	Vec2<T>& operator-=(const Vec2<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
	}

	template <typename T>
	Vec2<T>& operator*=(const Vec2<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
	}

	template <typename T>
	Vec2<T>& operator/=(const Vec2<T>& rhs)
	{
		if (rhs.x > 0) x /= rhs.x;
		if (rhs.y > 0) y /= rhs.y;
	}


public:
	T x;
	T y;
};