#ifndef NEXT2024_SRC_ENGINE_MATH_VEC3_H_
#define NEXT2024_SRC_ENGINE_MATH_VEC3_H_

#include "Vec2.h"

class Vec3 {
public:
	Vec3();

	Vec3(float x, float y, float z);

	Vec3(float x, float y, float z, float w);

	// returns a new vector with the components added
	Vec3 operator+(const Vec3& vec) const;

	// adds the components of the given vector to this vector
	Vec3& operator+=(const Vec3& vec);

	// returns a new vector with the components subtracted
	Vec3 operator-(const Vec3& vec) const;

	// subtracts the components of the given vector from this vector
	Vec3& operator-=(const Vec3& vec);

	// returns a new vector with the components multiplied by the given scalar
	Vec3 ScalarMultiply(float scalar) const;

	// multiplies the components of this vector by the given scalar
	Vec3& ScalarMultiplyEquals(float scalar);

	// returns a new vector with the components divided by the given scalar
	Vec3 operator/(float scalar) const;

	// divides the components of this vector by the given scalar
	Vec3& operator/=(float scalar);

	float DotProduct(const Vec3& vec) const;

	// returns a vector representing tthe cross product
	Vec3 CrossProduct(const Vec3& vec) const;

	// sets this vector to the cross product with the given vector
	Vec3& CrossProductEquals(const Vec3& vec);

	float Magnitude() const;

	// returns a normalized copy of this vector
	Vec3 Normalize() const;

	// normalizes this vector
	Vec3& NormalizeEquals();

	float DistanceTo(const Vec3& vec) const;

	// returns the angle between the vectors in the form of (angle on x-y plane, angle on x-z plane)
	Vec2 AngleTo(const Vec3& vec) const;

	std::string ToString() const;

	float GetX() const;

	float GetY() const;

	float GetZ() const;

	float GetW() const;
private:
	float m_x, m_y, m_z, m_w;
};

#endif  // NEXT2024_SRC_ENGINE_MATH_VEC3_H_