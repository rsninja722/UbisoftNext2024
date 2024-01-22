#ifndef NEXT2024_SRC_ECSDEFS_PLANE_H
#define NEXT2024_SRC_ECSDEFS_PLANE_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

// component
struct Plane {
	Vec3 position;
	float timeSinceFire;
	float direction;
};

// system
struct PlaneSystem {
	void Update(Plane* comp, entity e, float deltaTime);
	void Render(Plane* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_PLANE_H
