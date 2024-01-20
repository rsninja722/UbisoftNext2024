//-----------------------------------------------------------------------------
// Vec2.cpp
// vector class for 2D vectors
//-----------------------------------------------------------------------------
#include "stdafx.h"

#include "Vec2.h"

Vec2::Vec2() : m_x(0.0f), m_y(0.0f)
{
}

Vec2::Vec2(float x, float y) : m_x(x), m_y(y)
{
}

Vec2 Vec2::operator+(const Vec2& vec) const
{
	return Vec2(m_x + vec.m_x, m_y + vec.m_y);
}

Vec2& Vec2::operator+=(const Vec2& vec)
{
	m_x += vec.m_x;
	m_y += vec.m_y;
	return *this;
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
	return Vec2(m_x - vec.m_x, m_y - vec.m_y);
}

Vec2& Vec2::operator-=(const Vec2& vec)
{
	m_x -= vec.m_x;
	m_y -= vec.m_y;
	return *this;
}

Vec2 Vec2::ScalarMultiply(float scalar) const
{
	return Vec2(m_x * scalar, m_y * scalar);
}

Vec2& Vec2::ScalarMultiplyEquals(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	return *this;
}

Vec2 Vec2::operator/(float scalar) const
{
	return Vec2(m_x / scalar, m_y / scalar);
}

Vec2& Vec2::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	return *this;
}

float Vec2::DotProduct(const Vec2& vec) const
{
	return (m_x * vec.m_x + m_y * vec.m_y);
}

float Vec2::Magnitude() const
{
	return sqrtf(powf(m_x, 2) + powf(m_y, 2));
}

Vec2 Vec2::Normalize() const
{
	return *this / this->Magnitude();
}

Vec2& Vec2::NormalizeEquals()
{
	return *this /= this->Magnitude();
}

float Vec2::DistanceTo(const Vec2& vec) const
{
	return sqrtf(powf(m_x - vec.m_x, 2) + powf(m_y - vec.m_y, 2));
}

float Vec2::AngleTo(const Vec2& vec) const
{
	return atan2f(vec.m_y - m_y, vec.m_x - m_x);
}

std::string Vec2::ToString() const
{
	return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}

float Vec2::GetX() const
{
	return m_x;
}

float Vec2::GetY() const
{
	return m_y;
}
