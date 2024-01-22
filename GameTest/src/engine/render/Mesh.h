#ifndef NEXT2024_SRC_ENGINE_RENDER_MESH_H_
#define NEXT2024_SRC_ENGINE_RENDER_MESH_H_

#include <vector>

#include "engine/math/Mat4.h"
#include "Triangle.h"

struct Mesh {
	std::vector<Triangle> m_triangles;

	Mesh(std::vector<Triangle> triangles);
};


#endif // NEXT2024_SRC_ENGINE_RENDER_MESH_H_
