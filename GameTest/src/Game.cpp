//-----------------------------------------------------------------------------
// Game.cpp
// !Important! update Game(), Update(), Render(), and RemoverEntity() when creating new components
// a class to handle updating and rendering of all entities,
// as well as removing entities, and initializing common classes
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "../App/app.h"
#include "Game.h"

Game::Game()
{
}

void Game::Init()
{
	Log::Init();

	Log::Info("Initializing Game");

	Manager<Shield, ShieldSystem, 10000> m_shieldManager(&m_shieldSystemInstance);
	Manager<Sprite, SpriteSystem, 10000> m_spriteManager(&m_spriteSystemInstance);
	Manager<City, CitySystem, 6> m_cityManager(&m_citySystemInstance);
	Manager<Base, BaseSystem, 3> m_baseManager(&m_baseSystemInstance);
	Manager<Target, TargetSystem, 1> m_targetManager(&m_targetSystemInstance);
	Manager<Missle, MissleSystem, 1> m_missleManager(&m_missleSystemInstance);
	Manager<Explosion, ExplosionSystem, 1000> m_explosionManager(&m_explosionSystemInstance);
	Manager<Particle, ParticleSystem, 10000> m_particleManager(&m_particleSystemInstance);
	Manager<Plane, PlaneSystem, 100> m_planeManager(&m_planeSystemInstance);
	Manager<Star, StarSystem, 1000> m_starManager(&m_starSystemInstance);

	Entities::Init();
	Render::Init();

	Render::SetCameraPos({ (float)Render::SCREEN_WIDTH / 2.0f, -(float)Render::SCREEN_WIDTH / 2.0f, -6000.0f });
	Render::SetCameraTarget({ (float)Render::SCREEN_WIDTH / 2.0f, 0.0f, 0.0f });
}

void Game::Update(float deltaTime)
{
	m_timeElapsed += deltaTime;

	std::unordered_map<entity, Base*>* bases;
	std::unordered_map<entity, City*>* cities;
	bool gameOver = true;

	switch (m_activeScene) {
	case Scene::MAIN_MENU:
		SwitchScene(Scene::GAME);
		break;
	case Scene::GAME:
		m_targetManager.UpdateAll(deltaTime);
		m_shieldManager.UpdateAll(deltaTime);
		m_cityManager.UpdateAll(deltaTime);
		m_spriteManager.UpdateAll(deltaTime);
		m_baseManager.UpdateAll(deltaTime);
		m_missleManager.UpdateAll(deltaTime);
		m_explosionManager.UpdateAll(deltaTime);
		m_particleManager.UpdateAll(deltaTime);
		m_planeManager.UpdateAll(deltaTime);
		m_starManager.UpdateAll(deltaTime);

		ExecuteRemoves();

		if (m_timeElapsed - m_timeofLastSpawn > 1500.0f && m_enemiesToSpawn > 0) {
			m_timeofLastSpawn = m_timeElapsed;
			--m_enemiesToSpawn;
			entity e = Entities::Create();
			m_enemies.push_back(e);
			if (m_enemiesToSpawn % 10 == 0)
			{
				float dir = GetRandomInt(0, 1) == 0 ? -1.0f : 1.0f;
				m_planeManager.AddComponent(e, Plane{ { -dir * (float)Render::SCREEN_WIDTH / 2.0f, 1000.0f, 0.0f }, 0.0f, dir });
			}
			else
			{
				Vec3 targetPos;
				MissleType type = NORMAL;

				if (GetRandomInt(0, 3) == 3)
				{
					std::unordered_map<entity, Base*>* bases = Game::m_baseManager.GetAllComponents();

					int base = GetRandomInt(0, 2);
					targetPos = bases->at(Game::m_bases[base])->position;
				}
				else
				{
					std::unordered_map<entity, City*>* cities = Game::m_cityManager.GetAllComponents();

					int city = GetRandomInt(0, 5);
					targetPos = cities->at(Game::m_cities[city])->position;
				}

				if (GetRandomInt(0, 6) == 6)
				{
					type = SPLIT;
				}

				Game::m_missleManager.AddComponent(e, Missle{ Vec3{ (float)GetRandomInt(0, Render::SCREEN_WIDTH) - ((float)Render::SCREEN_WIDTH / 2.0f), 1200.0f, 0.0f},
					targetPos,
					Vec3{0.0f,
					-1.0f, 0.0f},
					0.0f,
					0.0001f,
					false,
					0.125f,
					type });
			}
		}

		cities = Game::m_cityManager.GetAllComponents();
		for (auto& i : *cities)
		{
			if (!i.second->isDestroyed) {
				gameOver = false;
				break;
			}
		}

		if (gameOver) {
			// remove all entities
			for (unsigned int i = 0; i < Entities::GetMaxEntities() + 1; i++) {
				RemoveEntity(i);
			}

			SwitchScene(Scene::GAME_OVER);
		}

		if (m_enemiesToSpawn == 0 && m_enemies.size() == 0)
		{
			// remove all missles
			std::unordered_map<entity, Missle*>* missles = Game::m_missleManager.GetAllComponents();
			for (auto& i : *missles)
			{
				Game::RemoveEntity(i.first);
			}

			// remove explosions
			std::unordered_map<entity, Explosion*>* explosions = Game::m_explosionManager.GetAllComponents();
			for (auto& i : *explosions)
			{
				Game::RemoveEntity(i.first);
			}

			// undestroy bases
		/*	std::unordered_map<entity, Base*>* bases = Game::m_baseManager.GetAllComponents();
			for (auto& i : *bases)
			{
				i.second->isDestroyed = false;
			}*/

			// undestroy cities
			/*std::unordered_map<entity, City*>* cities = Game::m_cityManager.GetAllComponents();
			for (auto& i : *cities)
			{
				i.second->isDestroyed = false;
			}*/

			SwitchScene(Scene::SHOP);
		}
		break;
	case Scene::SHOP:
		ExecuteRemoves();

		if (m_timeElapsed > 4000.0f)
		{
			SwitchScene(Scene::GAME);
		}

		bases = Game::m_baseManager.GetAllComponents();
		if (m_timeElapsed > 2000.0f && m_timeElapsed < 3000.0f)
		{

			for (auto& i : *bases)
			{
				if (i.second->missileCount > 0)
				{
					i.second->missileCount -= 1;
					m_points += 100;
				}
			}
		}
		if (m_timeElapsed > 3000.0f) {

			for (auto& i : *bases)
			{
				if (i.second->missileCount < 10)
				{
					i.second->missileCount += 1;
				}
			}
		}

		break;
	case Scene::PAUSE:
		break;
	case Scene::GAME_OVER:
		ExecuteRemoves();

		if (m_timeElapsed > 5000.0f)
		{
			SwitchScene(Scene::MAIN_MENU);
		}
		break;
	}
}

void Game::SwitchScene(Scene scene)
{
	m_timeElapsed = 0.0f;

	if (m_activeScene == Scene::MAIN_MENU && scene == Scene::GAME) {
		m_enemiesToSpawn = 10;
		m_points = 0;
		m_basesLeft = 3;
		m_citiesLeft = 6;
		m_level = 1;
		m_timeElapsed = 0.0f;
		m_timeofLastSpawn = 0.0f;

		// create terrain
		m_terrain = Entities::Create();
		m_spriteManager.AddComponent(m_terrain, Sprite{
			Render::m_terrain,
			{ 0.0f, -150.0f, 0.0f },
			{ 24.0f, 23.0f, 23.0f },
			{ 0.0f, M_PI / 2.0f, 0.0f },
			{ 0.73f, 0.69f, 0.0f }
			});


		// create cities
		for (int i = 0; i < 6; i++) {
			m_cities[i] = Entities::Create();

			float offset = 1.0f;
			if (i % 2 == 0) {
				offset = -1.0f;
			}

			City c{
				{ offset * (i / 2 + 1.5f) * 100.0f, -110.0f, 0.0f },
				false,
				false,
				false
			};

			m_cityManager.AddComponent(m_cities[i], c);
		}

		// create bases
		for (int i = 0; i < 3; i++) {
			m_bases[i] = Entities::Create();

			m_baseManager.AddComponent(m_bases[i], Base{ {1 + (i - 1) * 475.0f, -70.0f, 0.0f}, false, false, false, false, 10, true });
		}

		// create targeting reticle
		m_target = Entities::Create();
		m_targetManager.AddComponent(m_target, Target{ { 0.0f, 0.0f, 0.0f } });

	}

	if (m_activeScene == Scene::SHOP && scene == Scene::GAME)
	{
		m_timeofLastSpawn = 0.0f;
		m_level += 1;
		m_enemiesToSpawn = 10 + m_level * 5;
	}

	m_activeScene = scene;

}

void Game::Render()
{
	std::string level = "Level " + std::to_string(m_level);
	std::string points = "Points " + std::to_string(m_points);
	std::string gameOver = "Game Over";

	switch (m_activeScene) {
	case Scene::MAIN_MENU:
		break;
	case Scene::GAME:
		m_spriteManager.RenderAll();
		m_shieldManager.RenderAll();
		m_cityManager.RenderAll();
		m_baseManager.RenderAll();
		m_targetManager.RenderAll();
		m_missleManager.RenderAll();
		m_explosionManager.RenderAll();
		m_particleManager.RenderAll();
		m_planeManager.RenderAll();
		m_starManager.RenderAll();

		App::Print(10, Render::SCREEN_HEIGHT - 30, level.c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
		App::Print(10, Render::SCREEN_HEIGHT - 70, points.c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);

		break;
	case Scene::SHOP:
		m_spriteManager.RenderAll();
		m_cityManager.RenderAll();
		m_baseManager.RenderAll();

		App::Print((int)Render::SCREEN_WIDTH / 2 - 100, (int)Render::SCREEN_HEIGHT / 2 - 100, points.c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
		break;
	case Scene::PAUSE:
		break;
	case Scene::GAME_OVER:
		App::Print((int)Render::SCREEN_WIDTH / 2 - 100, (int)Render::SCREEN_HEIGHT / 2 - 100, gameOver.c_str(), 1.0f, 0.3f, 0.3f, GLUT_BITMAP_TIMES_ROMAN_24);
		break;
	}
}

void Game::RemoveEntity(entity e)
{
	m_entitiesToRemove.push_back(e);
}

void Game::ExecuteRemoves()
{
	for (entity e : m_entitiesToRemove) {

		// Shield.h
		for (std::pair<entity, Shield*> i : *m_shieldManager.GetAllComponents()) {
			if (i.first == e) {
				m_shieldManager.RemoveComponent(e);
				break;
			}
		}
		// City.h
		for (std::pair<entity, City*> i : *m_cityManager.GetAllComponents()) {
			if (i.first == e) {
				m_cityManager.RemoveComponent(e);
				break;
			}
		}
		// Sprite.h
		for (std::pair<entity, Sprite*> i : *m_spriteManager.GetAllComponents()) {
			if (i.first == e) {
				m_spriteManager.RemoveComponent(e);
				break;
			}
		}
		// Base.h
		for (std::pair<entity, Base*> i : *m_baseManager.GetAllComponents()) {
			if (i.first == e) {
				m_baseManager.RemoveComponent(e);
				break;
			}
		}
		// Target.h
		for (std::pair<entity, Target*> i : *m_targetManager.GetAllComponents()) {
			if (i.first == e) {
				m_targetManager.RemoveComponent(e);
				break;
			}
		}
		// Missle.h
		for (std::pair<entity, Missle*> i : *m_missleManager.GetAllComponents()) {
			if (i.first == e) {
				m_missleManager.RemoveComponent(e);
				break;
			}
		}
		// Explosion.h
		for (std::pair<entity, Explosion*> i : *m_explosionManager.GetAllComponents()) {
			if (i.first == e) {
				m_explosionManager.RemoveComponent(e);
				break;
			}
		}
		// Particle.h
		for (std::pair<entity, Particle*> i : *m_particleManager.GetAllComponents()) {
			if (i.first == e) {
				m_particleManager.RemoveComponent(e);
				break;
			}
		}
		// Plane.h
		for (std::pair<entity, Plane*> i : *m_planeManager.GetAllComponents()) {
			if (i.first == e) {
				m_planeManager.RemoveComponent(e);
				break;
			}
		}
		// Star.h
		for (std::pair<entity, Star*> i : *m_starManager.GetAllComponents()) {
			if (i.first == e) {
				m_starManager.RemoveComponent(e);
				break;
			}
		}

		if (std::find(m_enemies.begin(), m_enemies.end(), e) != m_enemies.end())
		{
			m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), e), m_enemies.end());
		}
	}
}

void Game::Shutdown()
{
	for (unsigned int i = 0; i < Entities::GetMaxEntities(); i++) {
		RemoveEntity(i);
	}

	Render::UnloadMeshes();
}

int Game::GetRandomInt(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

	return dist(rng);
}

Scene Game::m_activeScene = Scene::MAIN_MENU;

std::array<entity, 6> Game::m_cities;
entity Game::m_center;
entity Game::m_terrain;
std::array<entity, 3> Game::m_bases;
entity Game::m_target;
std::vector<entity> Game::m_enemies;


int Game::m_enemiesToSpawn;
int Game::m_points;
int Game::m_basesLeft;
int Game::m_citiesLeft;
int Game::m_level;
float Game::m_timeElapsed;
float Game::m_timeofLastSpawn;

Manager<Shield, ShieldSystem, 1000> Game::m_shieldManager;
Manager<Sprite, SpriteSystem, 1000> Game::m_spriteManager;
Manager<City, CitySystem, 6> Game::m_cityManager;
Manager<Base, BaseSystem, 3> Game::m_baseManager;
Manager<Target, TargetSystem, 1> Game::m_targetManager;
Manager<Missle, MissleSystem, 500> Game::m_missleManager;
Manager<Explosion, ExplosionSystem, 1000> Game::m_explosionManager;
Manager<Particle, ParticleSystem, 10000> Game::m_particleManager;
Manager<Plane, PlaneSystem, 100> Game::m_planeManager;
Manager<Star, StarSystem, 1000> Game::m_starManager;

ShieldSystem Game::m_shieldSystemInstance;
SpriteSystem Game::m_spriteSystemInstance;
CitySystem Game::m_citySystemInstance;
BaseSystem Game::m_baseSystemInstance;
TargetSystem Game::m_targetSystemInstance;
MissleSystem Game::m_missleSystemInstance;
ExplosionSystem Game::m_explosionSystemInstance;
ParticleSystem Game::m_particleSystemInstance;
PlaneSystem Game::m_planeSystemInstance;
StarSystem Game::m_starSystemInstance;

std::vector<entity> Game::m_entitiesToRemove;