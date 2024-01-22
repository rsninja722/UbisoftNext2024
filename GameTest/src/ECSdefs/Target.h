#ifndef NEXT2024_SRC_ECSDEFS_TARGET_H
#define NEXT2024_SRC_ECSDEFS_TARGET_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

// component
struct Target {
	Vec3 position;
};

// system
struct TargetSystem {
	void Update(Target* comp, entity e, float deltaTime);
	void Render(Target* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_TARGET_H
