#ifndef NEXT2024_SRC_ENGINE_RENDER_TRIANGLE_H_
#define NEXT2024_SRC_ENGINE_RENDER_TRIANGLE_H_

#include "engine/math/Vec3.h"

struct Triangle
{
	Vec3 m_v1;
	Vec3 m_v2;
	Vec3 m_v3;

	Triangle(Vec3 v1, Vec3 v2, Vec3 v3);
};

struct Color
{
	float m_r;
	float m_g;
	float m_b;
};

#endif // NEXT2024_SRC_ENGINE_RENDER_TRIANGLE_H_