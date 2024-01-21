//-----------------------------------------------------------------------------
// Shield.cpp
// a one hit shield that is destroyed when hit
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "engine/Log.h"
#include "Shield.h"

void ShieldSystem::Update(Shield* comp, float deltaTime)
{
	comp->radius += sinf(deltaTime) * 0.1f;
}

void ShieldSystem::Render(Shield* comp)
{
	float scale = comp->radius;
	Render::RenderMesh(Render::m_shield, comp->color, comp->position, { scale, scale, scale }, { 0.0f, 0.0f, 0.0f });
}