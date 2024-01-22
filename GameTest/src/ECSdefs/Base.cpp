//-----------------------------------------------------------------------------
// Base.cpp
// base to shoot missles from to defend cities
// can be upgraded with
//   - smaller cheaper missiles
//   - fragment missiles
//	 - shield
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include <vector>
#include <unordered_map>

#include "../App/app.h"
#include "engine/ECS/Entities.h"
#include "Game.h"
#include "Base.h"

#include "ECSdefs/Missle.h"

void BaseSystem::Update(Base* comp, entity e, float deltaTime)
{
	if (comp->isDestroyed)
	{
		return;
	}

	bool shouldFire = false;

	// left base
	if (comp->position.GetX() < -10.f)
	{
		if (App::IsKeyPressed('A') && comp->readyToFire)
		{
			shouldFire = true;
		}
		if (!App::IsKeyPressed('A'))
		{
			comp->readyToFire = true;
		}
	}
	// right base
	else if (comp->position.GetX() > 10.0f)
	{
		if (App::IsKeyPressed('D') && comp->readyToFire)
		{
			shouldFire = true;
		}
		if (!App::IsKeyPressed('D'))
		{
			comp->readyToFire = true;
		}
	}
	// center base
	else
	{
		if (App::IsKeyPressed('S') && comp->readyToFire)
		{
			shouldFire = true;
		}
		if (!App::IsKeyPressed('S'))
		{
			comp->readyToFire = true;
		}
	}

	if (shouldFire && comp->missileCount > 0) {
		entity missle = Entities::Create();

		std::unordered_map<entity, Target*>* targets = Game::m_targetManager.GetAllComponents();
		Vec3 targetPos = targets->at(Game::m_target)->position;

		MissleType type = NORMAL;

		if (comp->hasSmallMissileUpgrade)
		{
			type = SMALL;
		}
		if (comp->hasSplitMissileUpgrade)
		{
			type = SPLIT;
		}

		Game::m_missleManager.AddComponent(missle, Missle{ comp->position + Vec3{0.0f, 40.0f, 0.0f}, targetPos, Vec3{0.0f, 1.0f, 0.0f}, 0.0f, 0.001f, true, 0.6f, type });

		comp->missileCount -= 1;

		comp->readyToFire = false;
	}

	if (!comp->isDestroyed)
	{
		std::unordered_map<entity, Explosion*>* explosions = Game::m_explosionManager.GetAllComponents();
		for (auto& i : *explosions)
		{
			if ((i.second->position - comp->position).Magnitude() < i.second->curRadius)
			{
				comp->isDestroyed = true;
				comp->missileCount = 0;
				break;
			}
		}
	}
}

void BaseSystem::Render(Base* comp)
{
	if (comp->isDestroyed)
	{
		return;
	}

	Render::RenderMesh(Render::m_base, { 0.0f, 0.2f, 1.0f }, comp->position, { 10.0f, 10.0f, 10.0f }, { 0.0f, M_PI / 2, 0.0f });

	for (int i = 0; i < comp->missileCount - 1; ++i)
	{
		Render::RenderMesh(Render::m_rocket, { 1.0f, 0.5f, 0.0f }, missilePoses[i] + comp->position, { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f });
	}

	if (comp->missileCount > 0) {
		Render::RenderMesh(Render::m_rocket, { 1.0f, 0.5f, 0.0f }, comp->position + Vec3{0.0f, 40.0f, -10.0f}, { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f });
	}
}