//-----------------------------------------------------------------------------
// Missle.cpp
// Missle that flys towards the target
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Game.h"

#include "Missle.h"
#include "Explosion.h"


void MissleSystem::Update(Missle* comp, entity e, float deltaTime)
{
	comp->speed += comp->acceleration * deltaTime;

	if (comp->speed > comp->maxSpeed)
	{
		comp->speed = comp->maxSpeed;
	}


	// move towards target
	Vec3 direction = (comp->target - comp->position).Normalize();

	comp->angle = comp->angle.Slerp(direction, 0.05f);

	if (comp->angle.DotProduct(direction) > 0.99f)
	{
		comp->angle = direction;
	}

	comp->angle.NormalizeEquals();

	comp->position += comp->angle.ScalarMultiply(comp->speed * deltaTime);

	// gravity
	if (comp->useGravity && comp->position.GetY() > -20.0f)
	{
		comp->position += Vec3{ 0.0f, -0.05f, 0.0f }.ScalarMultiply(deltaTime);
	}

	if (comp->type == MissleType::SPLIT)
	{
		if (comp->position.GetY() < 900.0f || (comp->position - comp->target).Magnitude() < 100.0f)
		{
			for (int i = 0; i < 3; ++i) {
				entity missle = Entities::Create();


				Vec3 target;

				if (comp->useGravity)
				{
					target = comp->target + Vec3{ (float)(rand() % 200 - 100), (float)(rand() % 200 - 100), 0.0f };
				}
				else
				{
					std::unordered_map<entity, City*>* cities = Game::m_cityManager.GetAllComponents();

					int city = Game::GetRandomInt(0, 5);
					target = cities->at(Game::m_cities[city])->position;
				}

				Game::m_missleManager.AddComponent(missle, Missle{ comp->position,
					target,
					comp->angle,
					comp->speed,
					comp->acceleration,
					comp->useGravity,
					comp->maxSpeed,
					MissleType::NORMAL });
			}

			Game::RemoveEntity(e);

			return;
		}
	}

	// check if hit target
	if ((comp->position - comp->target).Magnitude() < 10.0f)
	{
		float radius = 70.0f;

		if (comp->type == MissleType::SMALL)
		{
			radius = 50.0f;
		}

		//Log::Info("Missle hit target " + std::to_string(e));


		entity explosion = Entities::Create();
		Game::m_explosionManager.AddComponent(explosion, Explosion{ comp->position, 0.0f, 0.0f, radius });

		Game::RemoveEntity(e);
		return;
	}


	std::unordered_map<entity, Explosion*>* explosions = Game::m_explosionManager.GetAllComponents();
	for (auto& i : *explosions)
	{
		if ((i.second->position - comp->position).Magnitude() < i.second->curRadius)
		{
			float radius = 70.0f;

			if (comp->type == MissleType::SMALL)
			{
				radius = 50.0f;
			}

			entity explosion = Entities::Create();
			Game::m_explosionManager.AddComponent(explosion, Explosion{ comp->position, 0.0f, 0.0f, radius });

			Game::m_points += 10;

			Game::RemoveEntity(e);
			return;
		}
	}
}

void MissleSystem::Render(Missle* comp)
{
	Vec3 rot;

	if (comp->useGravity)
	{
		rot = { 0.0f, sinf(comp->position.GetY() / 100.0f), -comp->angle.GetX() };
	}
	else
	{
		rot = { 0.0f, sinf(comp->position.GetY() / 100.0f), comp->angle.GetX() - (float)M_PI };
	}


	Render::RenderMesh(Render::m_rocket, { 1.0f, 0.5f, 0.0f }, comp->position, { 5.0f, 5.0f, 5.0f }, rot);
}