#ifndef NEXT2024_SRC_ENGINE_RENDER_LOADMESH_H_
#define NEXT2024_SRC_ENGINE_RENDER_LOADMESH_H_

#include <fstream>
#include <strstream>

#include <vector>
#include "engine/Log.h"
#include "engine/render/Triangle.h"
#include "engine/math/Vec3.h"

class LoadMesh {
public:
	LoadMesh();

	static std::vector<Triangle> LoadObj(const std::string& fileName);
};

#endif // NEXT2024_SRC_ENGINE_RENDER_LOADMESH_H_