#ifndef NEXT2024_SRC_ECSDEFS_BASE_H
#define NEXT2024_SRC_ECSDEFS_BASE_H

#include <array>

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

// component
struct Base {
	Vec3 position;
	bool isDestroyed;
	bool hasShieldUpgrade;
	bool hasSmallMissileUpgrade;
	bool hasSplitMissileUpgrade;
	int missileCount;
	bool readyToFire;
};

// system
struct BaseSystem {
	void Update(Base* comp, entity e, float deltaTime);
	void Render(Base* comp);
};

const std::array<Vec3, 20> missilePoses = {
	Vec3{ -30.0f, 20.0f, 0.0f },
	Vec3{ -15.0f, 20.0f, 0.0f },
	Vec3{ 0.0f, 20.0f, 0.0f },
	Vec3{ 15.0f, 20.0f, 0.0f },
	Vec3{ 30.0f, 20.0f, 0.0f },
	Vec3{ -30.0f, 20.0f, 50.0f },
	Vec3{ -15.0f, 20.0f, 50.0f },
	Vec3{ 0.0f, 20.0f, 50.0f },
	Vec3{ 15.0f, 20.0f, 50.0f },
	Vec3{ 30.0f, 20.0f, 50.0f },
	Vec3{ -30.0f, 20.0f, 150.0f },
	Vec3{ -15.0f, 20.0f, 150.0f },
	Vec3{ 0.0f, 20.0f, 150.0f },
	Vec3{ 15.0f, 20.0f, 150.0f },
	Vec3{ 30.0f, 20.0f, 150.0f },
	Vec3{ -30.0f, 20.0f, 200.0f },
	Vec3{ -15.0f, 20.0f, 200.0f },
	Vec3{ 0.0f, 20.0f, 200.0f },
	Vec3{ 15.0f, 20.0f, 200.0f },
	Vec3{ 30.0f, 20.0f, 200.0f }
};

#endif // NEXT2024_SRC_ECSDEFS_BASE_H

