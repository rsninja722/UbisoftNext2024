#ifndef NEXT2024_SRC_GAME_H_
#define NEXT2024_SRC_GAME_H_

#include "engine/ECS/Manager.h"

#include <unordered_map>
#include <math.h>

#include "engine/Log.h"

#include "engine/ECS/Entities.h"
#include "engine/render/Render.h"
#include "Scenes.h"

#include "ECSdefs/Shield.h"
#include "ECSdefs/City.h"
#include "ECSdefs/Sprite.h"
#include "ECSdefs/Base.h"


class Game {
public:

	static Scene m_activeScene;

	static std::array<entity, 6> m_cities;
	static entity m_center;
	static entity m_terrain;
	static std::array<entity, 3> m_bases;

	static Manager<Shield, ShieldSystem, 10000> m_shieldManager;
	static Manager<Sprite, SpriteSystem, 10000> m_spriteManager;
	static Manager<City, CitySystem, 6> m_cityManager;
	static Manager<Base, BaseSystem, 3> m_baseManager;

	Game();

	static void Init();

	static void Update(float deltaTime);

	static void SwitchScene(Scene scene);

	static void Render();

	static void RemoveEntity(entity e);

	static void Shutdown();
private:
	static ShieldSystem m_shieldSystemInstance;
	static SpriteSystem m_spriteSystemInstance;
	static CitySystem m_citySystemInstance;
	static BaseSystem m_baseSystemInstance;
};

#endif // NEXT2024_SRC_GAME_H_