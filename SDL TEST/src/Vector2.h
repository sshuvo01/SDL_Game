#pragma once

class Vector2
{
public:
	Vector2(int x, int y);
	Vector2();
	Vector2(const Vector2& v) = default;
	Vector2(Vector2&& v) = default;
	~Vector2();
	/*----------*/
	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator*(int m);
	Vector2 operator*(const Vector2& v);
	Vector2 operator+=(const Vector2& v);
	Vector2& operator=(const Vector2& v);
	int& operator[](unsigned int index);
	const int& operator[](unsigned int index) const;
	friend Vector2 operator*(int m, const Vector2& v);
	inline int X() const { return m_X; }
	inline int Y() const { return m_Y; }
private:
	int		m_X;
	int		m_Y;
};
