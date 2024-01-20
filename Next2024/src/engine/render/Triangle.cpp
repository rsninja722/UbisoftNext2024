//-----------------------------------------------------------------------------
// Triangle.cpp
// Struct to represent individual triangles for rendering
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Triangle.h"

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, int r, int g, int b) : vertices{ v1, v2, v3 }, r(r), g(g), b(b)
{
}