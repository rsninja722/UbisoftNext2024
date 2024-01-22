//-----------------------------------------------------------------------------
// City.cpp
// city to defend from missiles
// can be upgraded with
//   - shield
//   - iron dome rocket
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include <unordered_map>
#include "ECSdefs/Explosion.h"
#include "Game.h"

#include "City.h"

void CitySystem::Update(City* comp, entity e, float deltaTime)
{
	if (!comp->isDestroyed)
	{
		std::unordered_map<entity, Explosion*>* explosions = Game::m_explosionManager.GetAllComponents();
		for (auto& i : *explosions)
		{
			if ((i.second->position - comp->position).Magnitude() < i.second->curRadius)
			{
				comp->isDestroyed = true;
				break;
			}
		}
	}
}

void CitySystem::Render(City* comp)
{
	if (comp->isDestroyed)
	{
		return;
	}
	Render::RenderMesh(Render::m_city, { 0.0f, 0.2f, 1.0f }, comp->position, { 13.0f, 13.0f, 13.0f }, { 0.0f, M_PI / 2, 0.0f });
}