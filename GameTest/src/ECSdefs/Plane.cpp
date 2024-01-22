//-----------------------------------------------------------------------------
// Plane.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include <math.h>

#include "engine/ECS/Entities.h"
#include "ECSdefs/Missle.h"
#include "ECSdefs/Explosion.h"
#include "Game.h"
#include "engine/Log.h"

#include "Plane.h"



void PlaneSystem::Update(Plane* comp, entity e, float deltaTime)
{
	Log::Info(comp->position.ToString());
	comp->timeSinceFire += deltaTime;

	comp->position += { 0.02f * comp->direction * deltaTime, 0.0f, 0.0f};

	if (comp->timeSinceFire > 4000.0f) {
		comp->timeSinceFire = 0.0f;

		entity missile = Entities::Create();

		Game::m_missleManager.AddComponent(missile, Missle{ comp->position, Vec3{comp->position.GetX(), -65.0f, 0.0f }, Vec3{0.0f, -1.0f, 0.0f}, 0.0f, 0.0001f, false, 0.1f, MissleType::NORMAL });
	}

	if (comp->position.GetX() > Render::SCREEN_WIDTH / 2.0f + 10.0f || comp->position.GetX() < -Render::SCREEN_WIDTH / 2.0f - 10.0f)
	{
		Game::RemoveEntity(e);
	}

	std::unordered_map<entity, Explosion*>* explosions = Game::m_explosionManager.GetAllComponents();
	for (auto& i : *explosions)
	{
		if ((i.second->position - comp->position).Magnitude() < i.second->curRadius)
		{
			Game::m_points += 50;

			Game::RemoveEntity(e);
			return;
		}
	}
}

void PlaneSystem::Render(Plane* comp)
{
	Vec3 rotation = { 0.0f, (float)M_PI / 2.0f , 0.0f, };

	if (comp->direction == 1.0f)
	{
		rotation = { 0.0f, -(float)M_PI / 2.0f , 0.0f };
	}

	Render::RenderMesh(Render::m_plane, { 0.0f, 0.2f, 1.0f }, comp->position, { 5.0f, 5.0f, 5.0f }, rotation);
}