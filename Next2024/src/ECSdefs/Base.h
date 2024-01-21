#ifndef NEXT2024_SRC_ECSDEFS_BASE_H
#define NEXT2024_SRC_ECSDEFS_BASE_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"

// component
struct Base {
	Vec3 position;
	bool isDestroyed;
	bool hasShieldUpgrade;
	bool hasSmallMissileUpgrade;
	bool hasSplitMissileUpgrade;
	int missileCount;
};

// system
struct BaseSystem {
	void Update(Base* comp, float deltaTime);
	void Render(Base* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_BASE_H
