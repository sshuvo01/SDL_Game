#include "Vector2.h"

Vector2::Vector2(int x, int y)
	:m_X(x), m_Y(y)
{
}

Vector2::Vector2()
	:m_X(0), m_Y(0)
{
}

Vector2::~Vector2() 
{ 
}

Vector2 Vector2::operator+(const Vector2 & v)
{
	return Vector2(m_X + v.m_X, m_Y + v.m_Y);
}

Vector2 Vector2::operator-(const Vector2 & v)
{
	return Vector2(m_X - v.m_X, m_Y - v.m_Y);
}

Vector2 Vector2::operator*(int m)
{
	return Vector2(m_X * m, m_Y * m);
}

Vector2 Vector2::operator*(const Vector2 & v)
{
	return Vector2(m_X * v.m_X, m_Y * v.m_Y);
}

Vector2 Vector2::operator+=(const Vector2 & v)
{
	return Vector2(m_X += v.X(), m_Y += v.Y());
}

Vector2 & Vector2::operator=(const Vector2 & v)
{
	// TODO: insert return statement here
	m_X = v.m_X;
	m_Y = v.m_Y;
	return *this;
}

int & Vector2::operator[](unsigned int index)
{
	// TODO: insert return statement here
	if (index == 0) return m_X;
	if (index == 1) return m_Y;
}

Vector2 operator*(int m, const Vector2 & v)
{
	return Vector2(m * v.m_X, m * v.m_Y);
}
