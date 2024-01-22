#ifndef NEXT2024_SRC_ECSDEFS_EXPLOSION_H
#define NEXT2024_SRC_ECSDEFS_EXPLOSION_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

// component
struct Explosion {
	Vec3 position;
	float timeSinceSpawn;
	float curRadius;
	float maxRadius;
};

// system
struct ExplosionSystem {
	void Update(Explosion* comp, entity e, float deltaTime);
	void Render(Explosion* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_EXPLOSION_H
