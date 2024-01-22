//-----------------------------------------------------------------------------
// Render.cpp
// Class to handle rendering of meshes
// 
// Adding new mesh checklist:
//  - update Render::Init()
//  - update Render::UnloadMeshes()
//  - set nullptr at bottom of file
//  - declare in Render.h
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "../App/app.h"

#include "LoadMesh.h"
#include "Render.h"


Render::Render()
{
}

void Render::Init()
{
	m_camEye = Vec3(0.0f, 0.0f, 100.0f);
	m_camTarget = Vec3(0.0f, 0.0f, 0.0f);
	m_camUp = Vec3(0.0f, 1.0f, 0.0f);

	m_worldMatrix = Mat4::Identity();
	m_viewMatrix = Mat4::LookAt(m_camEye, m_camTarget, m_camUp);
	m_projectionMatrix = Mat4::Perspective(m_fov, m_aspectRatio, m_near, m_far);

	if (m_city == nullptr)
	{
		m_city = new Mesh(LoadMesh::LoadObj("city.obj"));
	}
	if (m_rocket == nullptr)
	{
		m_rocket = new Mesh(LoadMesh::LoadObj("rocket.obj"));
	}
	if (m_shield == nullptr)
	{
		m_shield = new Mesh(LoadMesh::LoadObj("shield.obj"));
	}
	if (m_base == nullptr)
	{
		m_base = new Mesh(LoadMesh::LoadObj("base.obj"));
	}
	if (m_terrain == nullptr)
	{
		m_terrain = new Mesh(LoadMesh::LoadObj("terrain.obj"));
	}
	if (m_plane == nullptr)
	{
		m_plane = new Mesh(LoadMesh::LoadObj("plane.obj"));
	}
	if (m_target == nullptr)
	{
		m_target = new Mesh(LoadMesh::LoadObj("target.obj"));
	}
}

void Render::SetCameraPos(const Vec3& pos)
{
	m_camEye = pos;
}

void Render::SetCameraTarget(const Vec3& target)
{
	m_camTarget = target;
}

void Render::UpdateCameraPos(const Vec3& pos)
{
	m_camEye += pos;
}

void Render::RenderFirstStep()
{
	m_drawBuffer.clear();

	m_viewMatrix = Mat4::LookAt(m_camEye, m_camTarget, m_camUp);
	m_projectionMatrix = Mat4::Perspective(m_fov, m_aspectRatio, m_near, m_far);

	m_worldMatrix = Mat4::Identity();
	m_worldMatrix *= Mat4::Scale({ 1.0f, 1.0f, 1.0f });
	m_worldMatrix *= Mat4::Identity();
	m_worldMatrix *= Mat4::Translation({ 0.0f, 0.0f, 0.0f });
}


void Render::RenderMesh(Mesh* mesh, Color color, Vec3 translate, Vec3 scale, Vec3 rotation)
{
	Mat4 localMatrix = Mat4::Identity();
	localMatrix *= Mat4::Translation(translate);
	localMatrix *= Mat4::Rotation(rotation);
	localMatrix *= Mat4::Scale(scale);

	for (int i = 0; i < mesh->m_triangles.size(); i++)
	{
		Vec3 p1 = localMatrix * mesh->m_triangles[i].m_v1;
		Vec3 p2 = localMatrix * mesh->m_triangles[i].m_v2;
		Vec3 p3 = localMatrix * mesh->m_triangles[i].m_v3;

		// unnecessary, and laggy
		//Mat4 worldMatrix = Mat4::Identity();
		//worldMatrix *= Mat4::Scale({ 1.0f, 1.0f, 1.0f });
		//worldMatrix *= Mat4::Identity();
		//worldMatrix *= Mat4::Translation({ 0.0f, 0.0f, 0.0f });

		//p1 = worldMatrix * p1;
		//p2 = worldMatrix * p2;
		//p3 = worldMatrix * p3;

		// backface culling
		Vec3 normal = ((p2 - p1).CrossProduct(p3 - p1)).Normalize();
		float camToTri = normal.DotProduct((p1 - m_camEye).Normalize());

		if (camToTri > 0.0f)
		{
			continue;
		}

		p1 = m_projectionMatrix * (m_viewMatrix * p1);
		p2 = m_projectionMatrix * (m_viewMatrix * p2);
		p3 = m_projectionMatrix * (m_viewMatrix * p3);

		if (p1.GetW() != 0.0f) {
			p1 = p1 / p1.GetW();
		}
		if (p2.GetW() != 0.0f) {
			p2 = p2 / p2.GetW();
		}
		if (p3.GetW() != 0.0f) {
			p3 = p3 / p3.GetW();
		}

		float offW = SCREEN_WIDTH / 2.0f;
		float offH = SCREEN_HEIGHT / 2.0f;

		p1 = { p1.GetX() * offW + offW, p1.GetY() * -offH + offH, p1.GetZ() * 0.5f + 0.5f };
		p2 = { p2.GetX() * offW + offW, p2.GetY() * -offH + offH, p2.GetZ() * 0.5f + 0.5f };
		p3 = { p3.GetX() * offW + offW, p3.GetY() * -offH + offH, p3.GetZ() * 0.5f + 0.5f };

		Triangle tri = { p1, p2, p3 };
		m_drawBuffer.emplace_back(tri, color);
	}
}


void Render::RenderFinalStep()
{
	for (std::pair<Triangle, Color>& i : m_drawBuffer) {
		Triangle t = i.first;
		Color c = i.second;

		App::DrawLine(t.m_v1.GetX(), t.m_v1.GetY(), t.m_v2.GetX(), t.m_v2.GetY(), c.m_r, c.m_g, c.m_b);
		App::DrawLine(t.m_v2.GetX(), t.m_v2.GetY(), t.m_v3.GetX(), t.m_v3.GetY(), c.m_r, c.m_g, c.m_b);
		App::DrawLine(t.m_v3.GetX(), t.m_v3.GetY(), t.m_v1.GetX(), t.m_v1.GetY(), c.m_r, c.m_g, c.m_b);
	}
}

void Render::UnloadMeshes()
{
	m_city->m_triangles.clear();
	m_rocket->m_triangles.clear();
	m_shield->m_triangles.clear();
	m_base->m_triangles.clear();
	m_terrain->m_triangles.clear();
	m_plane->m_triangles.clear();
	m_target->m_triangles.clear();

	delete m_city;
	delete m_rocket;
	delete m_shield;
	delete m_base;
	delete m_terrain;
	delete m_plane;
	delete m_target;

	m_city = nullptr;
	m_rocket = nullptr;
	m_shield = nullptr;
	m_base = nullptr;
	m_terrain = nullptr;
	m_plane = nullptr;
	m_target = nullptr;
}

float Render::m_fov = 100.0f;
float Render::m_near = 0.1f;
float Render::m_far = 1000.0f;
float Render::m_aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

Vec3 Render::m_camEye;
Vec3 Render::m_camTarget;
Vec3 Render::m_camUp;
Mat4 Render::m_worldMatrix;
Mat4 Render::m_viewMatrix;
Mat4 Render::m_projectionMatrix;

std::vector<std::pair<Triangle, Color>> Render::m_drawBuffer;

Mesh* Render::m_city = nullptr;
Mesh* Render::m_rocket = nullptr;
Mesh* Render::m_shield = nullptr;
Mesh* Render::m_base = nullptr;
Mesh* Render::m_terrain = nullptr;
Mesh* Render::m_plane = nullptr;
Mesh* Render::m_target = nullptr;