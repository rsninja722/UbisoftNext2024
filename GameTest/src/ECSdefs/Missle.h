#ifndef NEXT2024_SRC_ECSDEFS_MISSLE_H
#define NEXT2024_SRC_ECSDEFS_MISSLE_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

typedef enum {
	NORMAL,
	SMALL,
	SPLIT
} MissleType;

// component
struct Missle {
	Vec3 position;
	Vec3 target;
	Vec3 angle;
	float speed;
	float acceleration;
	bool useGravity;
	float maxSpeed;
	MissleType type;
};

// system
struct MissleSystem {
	void Update(Missle* comp, entity e, float deltaTime);
	void Render(Missle* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_MISSLE_H
