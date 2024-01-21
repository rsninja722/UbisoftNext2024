//-----------------------------------------------------------------------------
// Base.cpp
// base to shoot missles from to defend cities
// can be upgraded with
//   - smaller cheaper missiles
//   - fragment missiles
//	 - shield
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Base.h"

void BaseSystem::Update(Base* comp, float deltaTime)
{

}

void BaseSystem::Render(Base* comp)
{
	Render::RenderMesh(Render::m_base, { 0.0f, 0.2f, 1.0f }, comp->position, { 10.0f, 10.0f, 10.0f }, { 0.0f, M_PI / 2, 0.0f });
}