#ifndef NEXT2024_SRC_ENGINE_MATH_VEC2_H_
#define NEXT2024_SRC_ENGINE_MATH_VEC2_H_

class Vec2 {
public:
	Vec2();

	Vec2(float x, float y);

	// returns a new vector with the components added
	Vec2 operator+(const Vec2& vec) const;

	// adds the components of the given vector to this vector
	Vec2& operator+=(const Vec2& vec);

	// returns a new vector with the components subtracted
	Vec2 operator-(const Vec2& vec) const;

	// subtracts the components of the given vector from this vector
	Vec2& operator-=(const Vec2& vec);

	// returns a new vector with the components multiplied by the given scalar
	Vec2 ScalarMultiply(float scalar) const;

	// multiplies the components of this vector by the given scalar
	Vec2& ScalarMultiplyEquals(float scalar);

	// returns a new vector with the components divided by the given scalar
	Vec2 operator/(float scalar) const;

	// divides the components of this vector by the given scalar
	Vec2& operator/=(float scalar);

	float DotProduct(const Vec2& vec) const;

	float Magnitude() const;

	// returns a normalized copy of this vector
	Vec2 Normalize() const;

	// normalizes this vector
	Vec2& NormalizeEquals();

	float DistanceTo(const Vec2& vec) const;

	float AngleTo(const Vec2& vec) const;

	std::string ToString() const;

	float GetX() const;

	float GetY() const;

private:
	float m_x, m_y;
};

#endif  // NEXT2024_SRC_ENGINE_MATH_VEC2_H_