//-----------------------------------------------------------------------------
// Shield.cpp
// a one hit shield that is destroyed when hit
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "engine/Log.h"
#include "Shield.h"

void ShieldSystem::Update(Shield* comp, float deltaTime)
{
	comp->position += Vec3(1.0f, 0.0f, 0.0f);
}

void ShieldSystem::Render(Shield* comp)
{
	Log::Info("Shield at: " + std::to_string(comp->position.GetX()) + std::to_string(comp->position.GetY()) + std::to_string(comp->position.GetZ()));
}