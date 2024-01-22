//-----------------------------------------------------------------------------
// Explosion.cpp
// Explosion that flys towards the target
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Explosion.h"
#include "engine/Log.h"
#include "Game.h"
#include "Missle.h"
#include "../App/app.h"

void ExplosionSystem::Update(Explosion* comp, entity e, float deltaTime)
{
	if (comp->curRadius < comp->maxRadius) {
		comp->curRadius += deltaTime * 0.2f;
	}

	comp->timeSinceSpawn += deltaTime;
	if (comp->timeSinceSpawn > 2000.0f)
	{
		Game::RemoveEntity(e);
	}
}

void ExplosionSystem::Render(Explosion* comp)
{
	Vec3 scale = { comp->curRadius, comp->curRadius, comp->curRadius };

	scale.ScalarMultiplyEquals(0.8f);

	Render::RenderMesh(Render::m_shield, { 1.0f, 0.0f, 0.1f }, comp->position, scale, { comp->timeSinceSpawn / 1000.0f, comp->timeSinceSpawn / 1000.0f, comp->timeSinceSpawn / 1000.0f });
}