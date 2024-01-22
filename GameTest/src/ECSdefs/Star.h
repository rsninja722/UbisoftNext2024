#ifndef NEXT2024_SRC_ECSDEFS_Star_H
#define NEXT2024_SRC_ECSDEFS_Star_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

// component
struct Star {
	Vec3 position;
};

// system
struct StarSystem {
	void Update(Star* comp, entity e, float deltaTime);
	void Render(Star* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_Star_H
