//-----------------------------------------------------------------------------
// Mat3.cpp
// A 3x3 matrix class for 2D transformations
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Mat3.h"

Mat3 Mat3::Identity()
{
	return Mat3(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Mat3 Mat3::Translation(Vec2 vec)
{
	return Mat3(1.0f, 0.0f, vec.GetX(),
		0.0f, 1.0f, vec.GetY(),
		0.0f, 0.0f, 1.0f);
}

Mat3 Mat3::Rotation(float angle)
{
	return Mat3(cos(angle), -sin(angle), 0.0f,
		sin(angle), cos(angle), 0.0f,
		0.0f, 0.0f, 1.0f);
}

Mat3 Mat3::Scale(Vec2 vec)
{
	return Mat3(vec.GetX(), 0.0f, 0.0f,
		0.0f, vec.GetY(), 0.0f,
		0.0f, 0.0f, 1.0f);
}

Mat3::Mat3() : m_matrix{ 0.0f }
{
}

Mat3::Mat3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) : m_matrix{ m00, m01, m02, m10, m11, m12, m20, m21, m22 }
{
}

Mat3& Mat3::operator*=(const Mat3& mat)
{
	std::array<float, 9> temp = m_matrix;

	m_matrix[0] = temp[0] * mat.m_matrix[0] + temp[1] * mat.m_matrix[3] + temp[2] * mat.m_matrix[6];
	m_matrix[1] = temp[0] * mat.m_matrix[1] + temp[1] * mat.m_matrix[4] + temp[2] * mat.m_matrix[7];
	m_matrix[2] = temp[0] * mat.m_matrix[2] + temp[1] * mat.m_matrix[5] + temp[2] * mat.m_matrix[8];

	m_matrix[3] = temp[3] * mat.m_matrix[0] + temp[4] * mat.m_matrix[3] + temp[5] * mat.m_matrix[6];
	m_matrix[4] = temp[3] * mat.m_matrix[1] + temp[4] * mat.m_matrix[4] + temp[5] * mat.m_matrix[7];
	m_matrix[5] = temp[3] * mat.m_matrix[2] + temp[4] * mat.m_matrix[5] + temp[5] * mat.m_matrix[8];

	m_matrix[6] = temp[6] * mat.m_matrix[0] + temp[7] * mat.m_matrix[3] + temp[8] * mat.m_matrix[6];
	m_matrix[7] = temp[6] * mat.m_matrix[1] + temp[7] * mat.m_matrix[4] + temp[8] * mat.m_matrix[7];
	m_matrix[8] = temp[6] * mat.m_matrix[2] + temp[7] * mat.m_matrix[5] + temp[8] * mat.m_matrix[8];

	return *this;
}

Vec2 Mat3::operator*(const Vec2& vec) const
{
	return Vec2(m_matrix[0] * vec.GetX() + m_matrix[1] * vec.GetY(),
		m_matrix[3] * vec.GetX() + m_matrix[4] * vec.GetY());
}


Mat3& Mat3::Invert()
{
	float det = m_matrix[0] * (m_matrix[4] * m_matrix[8] - m_matrix[5] * m_matrix[7]) -
		m_matrix[1] * (m_matrix[3] * m_matrix[8] - m_matrix[5] * m_matrix[6]) +
		m_matrix[2] * (m_matrix[3] * m_matrix[7] - m_matrix[4] * m_matrix[6]);

	if (det == 0.0f)
	{
		return *this;
	}

	float invDet = 1.0f / det;

	std::array<float, 9> temp = m_matrix;
	m_matrix[0] = (temp[4] * temp[8] - temp[5] * temp[7]) * invDet;
	m_matrix[1] = (temp[2] * temp[7] - temp[1] * temp[8]) * invDet;
	m_matrix[2] = (temp[1] * temp[5] - temp[2] * temp[4]) * invDet;
	m_matrix[3] = (temp[5] * temp[6] - temp[3] * temp[8]) * invDet;
	m_matrix[4] = (temp[0] * temp[8] - temp[2] * temp[6]) * invDet;
	m_matrix[5] = (temp[2] * temp[3] - temp[0] * temp[5]) * invDet;
	m_matrix[6] = (temp[3] * temp[7] - temp[4] * temp[6]) * invDet;
	m_matrix[7] = (temp[1] * temp[6] - temp[0] * temp[7]) * invDet;
	m_matrix[8] = (temp[0] * temp[4] - temp[1] * temp[3]) * invDet;

	return *this;
}

Mat3& Mat3::Transpose()
{
	std::array<float, 9> temp = m_matrix;
	m_matrix[1] = temp[3];
	m_matrix[2] = temp[6];
	m_matrix[3] = temp[1];
	m_matrix[5] = temp[7];
	m_matrix[6] = temp[2];
	m_matrix[7] = temp[5];

	return *this;
}