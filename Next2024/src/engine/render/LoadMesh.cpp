//-----------------------------------------------------------------------------
// LoadMesh.cpp
// class for loading meshes from .obj files in the assets folder
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "LoadMesh.h"

LoadMesh::LoadMesh()
{
}

std::vector<Triangle> LoadMesh::LoadObj(const std::string& fileName)
{
	Log::Info("Loading mesh from file: assets/" + fileName);

	std::vector<Vec3> vertices;

	std::vector<Triangle> triangles;

	std::ifstream f("assets/" + fileName);
	if (!f.is_open())
	{
		Log::Error("Could not open file: assets/" + fileName);
		return triangles;
	}

	while (!f.eof())
	{
		char line[255];
		f.getline(line, 255);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			float x, y, z;
			s >> junk >> x >> y >> z;
			vertices.emplace_back(x, y, z);
		}

		if (line[0] == 'f')
		{
			int v1, v2, v3;
			s >> junk >> v1 >> v2 >> v3;
			triangles.emplace_back(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1]);
		}
	}

	Log::Info("Successfully Loaded mesh from file: assets/" + fileName);

	return triangles;
}