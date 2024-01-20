//-----------------------------------------------------------------------------
// Render.cpp
// Class to handle rendering of meshes
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Render.h"


Render::Render()
{
}

void Render::Init()
{
	m_camEye = Vec3(0.0f, 0.0f, 10.0f);
	m_camTarget = Vec3(0.0f, 0.0f, 0.0f);
	m_camUp = Vec3(0.0f, 1.0f, 0.0f);

	m_worldMatrix = Mat4::Identity();
	m_viewMatrix = Mat4::LookAt(m_camEye, m_camTarget, m_camUp);
	m_projectionMatrix = Mat4::Perspective(m_fov, m_aspectRatio, m_near, m_far);
}

void Render::SetCameraPos(const Vec3& pos)
{
	m_camEye = pos;
}

void Render::SetCameraTarget(const Vec3& target)
{
	m_camTarget = target;
}

void Render::RenderAll() {
	UpdateModel();


}

void Render::UpdateModel()
{
	m_modelMatrix = Mat4::Identity();
	m_modelMatrix *= m_worldMatrix;
	m_modelMatrix *= m_viewMatrix;
	m_modelMatrix *= m_projectionMatrix;
}
