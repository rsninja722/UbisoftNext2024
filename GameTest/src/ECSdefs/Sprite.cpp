//-----------------------------------------------------------------------------
// Sprite.cpp
// a mesh and a color for rendering
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Sprite.h"

void SpriteSystem::Update(Sprite* comp, entity e, float deltaTime)
{
}

void SpriteSystem::Render(Sprite* comp)
{
	Render::RenderMesh(comp->mesh, comp->color, comp->position, comp->scale, comp->rotation);
}