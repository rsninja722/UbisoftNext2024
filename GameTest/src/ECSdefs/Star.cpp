//-----------------------------------------------------------------------------
// Star.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Star.h"

void StarSystem::Update(Star* comp, entity e, float deltaTime)
{

}

void StarSystem::Render(Star* comp)
{
	Render::RenderMesh(Render::m_target, { 0.0f, 0.2f, 1.0f }, comp->position, { 13.0f, 13.0f, 13.0f }, { 0.0f, M_PI / 2, 0.0f });
}