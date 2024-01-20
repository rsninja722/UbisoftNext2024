#ifndef NEXT2024_SRC_ENGINE_RENDER_TRIANGLE_H_
#define NEXT2024_SRC_ENGINE_RENDER_TRIANGLE_H_

#include "engine/math/Vec3.h"

struct Triangle
{
	std::array<Vec3, 3> vertices;
	int r, g, b;

	Triangle(Vec3 v1, Vec3 v2, Vec3 v3, int r, int g, int b);
};

#endif // NEXT2024_SRC_ENGINE_RENDER_TRIANGLE_H_