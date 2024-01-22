#ifndef NEXT2024_SRC_ENGINE_MATH_MAT4_H_
#define NEXT2024_SRC_ENGINE_MATH_MAT4_H_

#include "Vec3.h"

class Mat4 {
public:
	// returns a new identity matrix
	static Mat4 Identity();

	// returns a new translation matrix with translations provided in the form (x, y, z)
	static Mat4 Translation(Vec3 vec);

	// returns a new rotation matrix with the angles provided in radians in the form (x-axis, y-axis, z-axis)
	static Mat4 Rotation(Vec3 vec);

	// returns a new scale matrix with the given scale factors in the form (x, y, z)
	static Mat4 Scale(Vec3 vec);

	// returns a matrix representing the camera at the given position eye looking at the given target with the given up vector
	static Mat4 LookAt(Vec3 eye, Vec3 target, Vec3 up);

	// returns a matrix representing the perspective projection with the given field of view in degrees, aspect ratio, near plane, and far plane
	static Mat4 Perspective(float fov, float aspectRatio, float near, float far);

	Mat4();

	Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);

	// multiplies this matrix by the given matrix
	Mat4& operator*=(const Mat4& mat);

	// returns a vector representing the product of this matrix and the given vector
	Vec3 operator*(const Vec3& vec) const;

	// transposes this matrix
	Mat4& Transpose();

	std::string ToString() const;

private:
	std::array<float, 16> m_matrix;
};

#endif // NEXT2024_SRC_ENGINE_MATH_NAT4_H_