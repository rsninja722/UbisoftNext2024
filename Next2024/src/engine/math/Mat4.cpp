//-----------------------------------------------------------------------------
// Mat4.cpp
// A 4x4 matrix class for 3D transformations
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Mat4.h"

Mat4 Mat4::Identity()
{
	return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::Translation(Vec3 vec)
{
	return Mat4(1.0f, 0.0f, 0.0f, vec.GetX(),
		0.0f, 1.0f, 0.0f, vec.GetY(),
		0.0f, 0.0f, 1.0f, vec.GetZ(),
		0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::Rotation(Vec3 vec)
{
	float a = vec.GetX();
	float b = vec.GetY();
	float c = vec.GetZ();

	return Mat4(cosf(a) * cosf(b), cosf(a) * sinf(b) * sinf(c) - sinf(a) * cosf(c), cosf(a) * sinf(b) * cosf(c) + sinf(a) * sinf(c), 0.0f,
		sinf(a) * cosf(b), sinf(a) * sinf(b) * sinf(c) + cosf(a) * cosf(c), sinf(a) * sinf(b) * cosf(c) - cosf(a) * sinf(c), 0.0f,
		-sinf(b), cosf(b) * sinf(c), cosf(b) * cosf(c), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::Scale(Vec3 vec)
{
	return Mat4(vec.GetX(), 0.0f, 0.0f, 0.0f,
		0.0f, vec.GetY(), 0.0f, 0.0f,
		0.0f, 0.0f, vec.GetZ(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::LookAt(Vec3 eye, Vec3 target, Vec3 up) {
	Vec3 f = (target - eye).Normalize(); // forwards
	Vec3 r = (f.CrossProduct(up)).Normalize();
	Vec3 u = r.CrossProduct(f).Normalize();

	return Mat4(r.GetX(), r.GetY(), r.GetZ(), -r.DotProduct(eye),
		u.GetX(), u.GetY(), u.GetZ(), -u.DotProduct(eye),
		-f.GetX(), -f.GetY(), -f.GetZ(), -f.DotProduct(eye),
		0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 Mat4::Perspective(float fov, float aspectRatio, float near, float far)
{
	float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

	return Mat4(fovRad * aspectRatio, 0.0f, 0.0f, 0.0f,
		0.0f, fovRad, 0.0f, 0.0f,
		0.0f, 0.0f, far / (far - near), 1.0f,
		0.0f, 0.0f, (-far * near) / (far - near), 0.0f);
}

Mat4::Mat4() : m_matrix{ 0.0f }
{
}

Mat4::Mat4(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) : m_matrix{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 }
{
}

Mat4& Mat4::operator*=(const Mat4& mat)
{
	std::array<float, 16> temp = m_matrix;

	m_matrix[0] = temp[0] * mat.m_matrix[0] + temp[1] * mat.m_matrix[4] + temp[2] * mat.m_matrix[8] + temp[3] * mat.m_matrix[12];
	m_matrix[1] = temp[0] * mat.m_matrix[1] + temp[1] * mat.m_matrix[5] + temp[2] * mat.m_matrix[9] + temp[3] * mat.m_matrix[13];
	m_matrix[2] = temp[0] * mat.m_matrix[2] + temp[1] * mat.m_matrix[6] + temp[2] * mat.m_matrix[10] + temp[3] * mat.m_matrix[14];
	m_matrix[3] = temp[0] * mat.m_matrix[3] + temp[1] * mat.m_matrix[7] + temp[2] * mat.m_matrix[11] + temp[3] * mat.m_matrix[15];

	m_matrix[4] = temp[4] * mat.m_matrix[0] + temp[5] * mat.m_matrix[4] + temp[6] * mat.m_matrix[8] + temp[7] * mat.m_matrix[12];
	m_matrix[5] = temp[4] * mat.m_matrix[1] + temp[5] * mat.m_matrix[5] + temp[6] * mat.m_matrix[9] + temp[7] * mat.m_matrix[13];
	m_matrix[6] = temp[4] * mat.m_matrix[2] + temp[5] * mat.m_matrix[6] + temp[6] * mat.m_matrix[10] + temp[7] * mat.m_matrix[14];
	m_matrix[7] = temp[4] * mat.m_matrix[3] + temp[5] * mat.m_matrix[7] + temp[6] * mat.m_matrix[11] + temp[7] * mat.m_matrix[15];

	m_matrix[8] = temp[8] * mat.m_matrix[0] + temp[9] * mat.m_matrix[4] + temp[10] * mat.m_matrix[8] + temp[11] * mat.m_matrix[12];
	m_matrix[9] = temp[8] * mat.m_matrix[1] + temp[9] * mat.m_matrix[5] + temp[10] * mat.m_matrix[9] + temp[11] * mat.m_matrix[13];
	m_matrix[10] = temp[8] * mat.m_matrix[2] + temp[9] * mat.m_matrix[6] + temp[10] * mat.m_matrix[10] + temp[11] * mat.m_matrix[14];
	m_matrix[11] = temp[8] * mat.m_matrix[3] + temp[9] * mat.m_matrix[7] + temp[10] * mat.m_matrix[11] + temp[11] * mat.m_matrix[15];

	m_matrix[12] = temp[12] * mat.m_matrix[0] + temp[13] * mat.m_matrix[4] + temp[14] * mat.m_matrix[8] + temp[15] * mat.m_matrix[12];
	m_matrix[13] = temp[12] * mat.m_matrix[1] + temp[13] * mat.m_matrix[5] + temp[14] * mat.m_matrix[9] + temp[15] * mat.m_matrix[13];
	m_matrix[14] = temp[12] * mat.m_matrix[2] + temp[13] * mat.m_matrix[6] + temp[14] * mat.m_matrix[10] + temp[15] * mat.m_matrix[14];
	m_matrix[15] = temp[12] * mat.m_matrix[3] + temp[13] * mat.m_matrix[7] + temp[14] * mat.m_matrix[11] + temp[15] * mat.m_matrix[15];

	return *this;
}

Vec3 Mat4::operator*(const Vec3& vec) const
{
	return Vec3(m_matrix[0] * vec.GetX() + m_matrix[1] * vec.GetY() + m_matrix[2] * vec.GetZ() + m_matrix[3] * vec.GetW(),
		m_matrix[4] * vec.GetX() + m_matrix[5] * vec.GetY() + m_matrix[6] * vec.GetZ() + m_matrix[7] * vec.GetW(),
		m_matrix[8] * vec.GetX() + m_matrix[9] * vec.GetY() + m_matrix[10] * vec.GetZ() + m_matrix[11] * vec.GetW(),
		m_matrix[12] * vec.GetX() + m_matrix[13] * vec.GetY() + m_matrix[14] * vec.GetZ() + m_matrix[15] * vec.GetW());
}

Mat4& Mat4::Transpose()
{
	std::array<float, 16> temp = m_matrix;

	m_matrix[1] = temp[4];
	m_matrix[2] = temp[8];
	m_matrix[3] = temp[12];

	m_matrix[4] = temp[1];
	m_matrix[6] = temp[9];
	m_matrix[7] = temp[13];

	m_matrix[8] = temp[2];
	m_matrix[9] = temp[6];
	m_matrix[11] = temp[14];

	m_matrix[12] = temp[3];
	m_matrix[13] = temp[7];
	m_matrix[14] = temp[11];

	return *this;
}

std::string Mat4::ToString() const
{
	std::string result = "Matrix: (";

	for (int i = 0; i < 16; i++)
	{
		result += std::to_string(m_matrix[i]) + ", ";
	}

	return result + ") ";
}
