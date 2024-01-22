//-----------------------------------------------------------------------------
// Mesh.cpp
// Class to represent a mesh of triangles for rendering
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Render.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Triangle> triangles) : m_triangles(triangles)
{
}
