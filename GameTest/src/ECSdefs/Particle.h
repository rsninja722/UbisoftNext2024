#ifndef NEXT2024_SRC_ECSDEFS_PARTICLE_H
#define NEXT2024_SRC_ECSDEFS_PARTICLE_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

// component
struct Particle {
	Vec3 position;
};

// system
struct ParticleSystem {
	void Update(Particle* comp, entity e, float deltaTime);
	void Render(Particle* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_PARTICLE_H
