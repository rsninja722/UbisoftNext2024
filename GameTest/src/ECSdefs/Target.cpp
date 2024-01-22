//-----------------------------------------------------------------------------
// Target.cpp
// reticle for aiming missles
//-----------------------------------------------------------------------------

#include "stdafx.h"


#include "../App/app.h"
#include "Target.h"

void TargetSystem::Update(Target* comp, entity e, float deltaTime)
{
	Vec3 moveDir = { 0.0f, 0.0f, 0.0f };
	if (App::IsKeyPressed(VK_UP))
	{
		moveDir += { 0.0f, 1.0f, 0.0f };
	}
	if (App::IsKeyPressed(VK_DOWN))
	{
		moveDir += { 0.0f, -1.0f, 0.0f};
	}
	if (App::IsKeyPressed(VK_LEFT))
	{
		moveDir += { -1.0f, 0.0f, 0.0f };
	}
	if (App::IsKeyPressed(VK_RIGHT))
	{
		moveDir += { 1.0f, 0.0f, 0.0f };
	}

	float multiplier = 0.5f;
	if (App::IsKeyPressed(VK_SPACE))
	{
		multiplier = 1.5f;
	}

	if (moveDir.Magnitude() > 0.0f)
	{
		moveDir.Normalize();
		comp->position += moveDir.ScalarMultiply(deltaTime).ScalarMultiply(multiplier);

		// clamp to visable area
		if (comp->position.GetX() > Render::SCREEN_WIDTH / 2)
		{
			comp->position -= { comp->position.GetX() - (Render::SCREEN_WIDTH / 2), 0.0f, 0.0f};
		}
		if (comp->position.GetX() < -Render::SCREEN_WIDTH / 2)
		{
			comp->position -= { comp->position.GetX() + (Render::SCREEN_WIDTH / 2), 0.0f, 0.0f };
		}
		if (comp->position.GetY() > (float)Render::SCREEN_HEIGHT * 1.5f)
		{
			comp->position -= { 0.0f, comp->position.GetY() - ((float)Render::SCREEN_HEIGHT * 1.5f), 0.0f };
		}
		if (comp->position.GetY() < -30)
		{
			comp->position -= { 0.0f, comp->position.GetY() + 30, 0.0f };
		}
	}
}

void TargetSystem::Render(Target* comp)
{
	Render::RenderMesh(Render::m_target, { 1.0f, 1.0f, 0.0f }, comp->position, { 2.0f, 2.0f, 2.0f }, { 0.0f, 0.0f, 0.0f });
}