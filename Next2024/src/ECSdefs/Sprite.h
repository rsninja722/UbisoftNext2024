#ifndef NEXT2024_SRC_ECSDEFS_SPRITE_H
#define NEXT2024_SRC_ECSDEFS_SPRITE_H

#include "engine/render/Mesh.h"
#include "engine/render/Render.h"

// component
struct Sprite {
	Mesh* mesh;
	Vec3 position;
	Vec3 scale;
	Vec3 rotation;
	Color color;
};

// system
struct SpriteSystem {
	void Update(Sprite* comp, float deltaTime);
	void Render(Sprite* comp);
};

#endif // NEXT2024_SRC_ECSDEFS_SPRITE_H
