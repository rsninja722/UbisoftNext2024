//-----------------------------------------------------------------------------
// Vec3.cpp
// vector class for 3D vectors
//-----------------------------------------------------------------------------
#include "stdafx.h"

#include <math.h>
#include <algorithm>
#include "Vec3.h"

Vec3::Vec3() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(1.0f)
{
}

Vec3::Vec3(float x, float y, float z) : m_x(x), m_y(y), m_z(z), m_w(1.0f)
{
}

Vec3::Vec3(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

Vec3 Vec3::operator+(const Vec3& vec) const
{
	return Vec3(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
}

Vec3& Vec3::operator+=(const Vec3& vec)
{
	m_x += vec.m_x;
	m_y += vec.m_y;
	m_z += vec.m_z;
	return *this;
}

Vec3 Vec3::operator-(const Vec3& vec) const
{
	return Vec3(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
}

Vec3& Vec3::operator-=(const Vec3& vec)
{
	m_x -= vec.m_x;
	m_y -= vec.m_y;
	m_z -= vec.m_z;
	return *this;
}

Vec3 Vec3::ScalarMultiply(float scalar) const
{
	return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
}

Vec3& Vec3::ScalarMultiplyEquals(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;
	return *this;
}

Vec3 Vec3::operator/(float scalar) const
{
	return Vec3(m_x / scalar, m_y / scalar, m_z / scalar);
}

Vec3& Vec3::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	m_z /= scalar;
	return *this;
}

float Vec3::DotProduct(const Vec3& vec) const
{
	return (m_x * vec.m_x + m_y * vec.m_y, +m_z * vec.m_z);
}

Vec3 Vec3::CrossProduct(const Vec3& vec) const
{
	return Vec3(m_y * vec.m_z - m_z * vec.m_y, m_z * vec.m_x - m_x * vec.m_z, m_x * vec.m_y - m_y * vec.m_x);
}

Vec3& Vec3::CrossProductEquals(const Vec3& vec)
{
	m_x = m_y * vec.m_z - m_z * vec.m_y;
	m_y = m_z * vec.m_x - m_x * vec.m_z;
	m_z = m_x * vec.m_y - m_y * vec.m_x;
	return *this;
}

float Vec3::Magnitude() const
{
	return sqrtf(powf(m_x, 2) + powf(m_y, 2) + powf(m_z, 2));
}

Vec3 Vec3::Normalize() const
{
	return *this / this->Magnitude();
}

Vec3& Vec3::NormalizeEquals()
{
	return *this /= this->Magnitude();
}

float Vec3::DistanceTo(const Vec3& vec) const
{
	return sqrtf(powf(m_x - vec.m_x, 2) + powf(m_y - vec.m_y, 2) + powf(m_z - vec.m_z, 2));
}

Vec2 Vec3::AngleTo(const Vec3& vec) const
{
	return Vec2(atan2f(vec.m_y - m_y, vec.m_x - m_x), atan2f(vec.m_z - m_z, vec.m_x - m_x));
}

Vec3 Vec3::Slerp(const Vec3& vec, float percentage) const
{
	float dot = this->DotProduct(vec);

	dot = dot < -1.0f ? -1.0f : (dot > 1.0f ? 1.0f : dot);

	float theta = acosf(dot) * percentage;

	Vec3 relativeVec = vec - (*this).ScalarMultiply(dot);

	relativeVec.NormalizeEquals();

	return (*this).ScalarMultiply(cosf(theta)) + relativeVec.ScalarMultiply(sinf(theta));
}

std::string Vec3::ToString() const
{
	return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ") ";
}

float Vec3::GetX() const
{
	return m_x;
}

float Vec3::GetY() const
{
	return m_y;
}

float Vec3::GetZ() const
{
	return m_z;
}

float Vec3::GetW() const
{
	return m_w;
}