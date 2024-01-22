#ifndef NEXT2024_SRC_GAME_H_
#define NEXT2024_SRC_GAME_H_

#include "engine/ECS/Manager.h"

#include <unordered_map>
#include <math.h>
#include <random>

#include "engine/Log.h"

#include "engine/ECS/Entities.h"
#include "engine/render/Render.h"
#include "Scenes.h"

#include "ECSdefs/Shield.h"
#include "ECSdefs/City.h"
#include "ECSdefs/Sprite.h"
#include "ECSdefs/Base.h"
#include "ECSdefs/Target.h"
#include "ECSdefs/Missle.h"
#include "ECSdefs/Explosion.h"
#include "ECSdefs/Particle.h"
#include "ECSdefs/Plane.h"
#include "ECSdefs/Star.h"



class Game {
public:

	static Scene m_activeScene;

	static std::array<entity, 6> m_cities;
	static entity m_center;
	static entity m_terrain;
	static std::array<entity, 3> m_bases;
	static entity m_target;
	static std::vector<entity> m_enemies;

	static int m_enemiesToSpawn;
	static int m_points;
	static int m_basesLeft;
	static int m_citiesLeft;
	static int m_level;
	static float m_timeElapsed;
	static float m_timeofLastSpawn;

	static Manager<Shield, ShieldSystem, 1000> m_shieldManager;
	static Manager<Sprite, SpriteSystem, 1000> m_spriteManager;
	static Manager<City, CitySystem, 6> m_cityManager;
	static Manager<Base, BaseSystem, 3> m_baseManager;
	static Manager<Target, TargetSystem, 1> m_targetManager;
	static Manager<Missle, MissleSystem, 500> m_missleManager;
	static Manager<Explosion, ExplosionSystem, 1000> m_explosionManager;
	static Manager<Particle, ParticleSystem, 10000> m_particleManager;
	static Manager<Plane, PlaneSystem, 100> m_planeManager;
	static Manager<Star, StarSystem, 1000> m_starManager;

	static std::vector<entity> m_entitiesToRemove;

	Game();

	static void Init();

	static void Update(float deltaTime);

	static void SwitchScene(Scene scene);

	static void Render();

	static void RemoveEntity(entity e);

	static void ExecuteRemoves();

	static void Shutdown();

	static int GetRandomInt(int min, int max);
private:
	static ShieldSystem m_shieldSystemInstance;
	static SpriteSystem m_spriteSystemInstance;
	static CitySystem m_citySystemInstance;
	static BaseSystem m_baseSystemInstance;
	static TargetSystem m_targetSystemInstance;
	static MissleSystem m_missleSystemInstance;
	static ExplosionSystem m_explosionSystemInstance;
	static ParticleSystem m_particleSystemInstance;
	static PlaneSystem m_planeSystemInstance;
	static StarSystem m_starSystemInstance;
};

#endif // NEXT2024_SRC_GAME_H_