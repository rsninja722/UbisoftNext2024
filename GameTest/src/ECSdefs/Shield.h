#ifndef NEXT2024_SRC_ECSDEFS_SHIELD_H
#define NEXT2024_SRC_ECSDEFS_SHIELD_H

#include "engine/math/Vec3.h"
#include "engine/render/Render.h"
#include "engine/ECS/Manager.h"
#include "engine/ECS/Entities.h"

// component
struct Shield {
	Vec3 position;
	float radius;
	Color color;
};

// system
struct ShieldSystem {
	void Update(Shield* comp, entity e, float deltaTime);
	void Render(Shield* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_SHIELD_H
