#ifndef NEXT2024_SRC_ECSDEFS_CITY_H
#define NEXT2024_SRC_ECSDEFS_CITY_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"
#include "engine/ECS/Entities.h"

// component
struct City {
	Vec3 position;
	bool isDestroyed;
	bool hasShieldUpgrade;
	bool hasMissileUpgrade;
};

// system
struct CitySystem {
	void Update(City* comp, entity e, float deltaTime);
	void Render(City* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_CITY_H
