#ifndef NEXT2024_SRC_ENGINE_MATH_MAT3_H_
#define NEXT2024_SRC_ENGINE_MATH_NAT3_H_

#include "Vec2.h"

class Mat3 {
public:
	// returns a new identity matrix
	static Mat3 Identity();

	// returns a new translation matrix with translations provided in the form (x, y)
	static Mat3 Translation(Vec2 vec);

	// returns a new rotation matrix with the given angle in radians
	static Mat3 Rotation(float angle);

	// returns a new scale matrix with the given scale factors in the form (x, y)
	static Mat3 Scale(Vec2 vec);

	Mat3();

	Mat3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

	// multiplies this matrix by the given matrix
	Mat3& operator*=(const Mat3& mat);

	// returns a vector representing the product of this matrix and the given vector
	Vec2 operator*(const Vec2& vec) const;

	// inverts this matrix
	Mat3& Invert();

	// transposes this matrix
	Mat3& Transpose();

private:
	std::array<float, 9> m_matrix;
};

#endif // NEXT2024_SRC_ENGINE_MATH_NAT3_H_