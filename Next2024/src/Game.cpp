//-----------------------------------------------------------------------------
// Game.cpp
// !Important! update Game(), Update(), Render(), and RemoverEntity() when creating new components
// a class to handle updating and rendering of all entities,
// as well as removing entities, and initializing common classes
//-----------------------------------------------------------------------------

#include "stdafx.h"

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

	Entities::Init();
	Render::Init();

	Render::SetCameraPos({ (float)Render::SCREEN_WIDTH / 2.0f, -(float)Render::SCREEN_WIDTH / 2.0f, -6000.0f });
	Render::SetCameraTarget({ (float)Render::SCREEN_WIDTH / 2.0f, 0.0f, 0.0f });
}

void Game::Update(float deltaTime)
{
	switch (m_activeScene) {
	case Scene::MAIN_MENU:
		SwitchScene(Scene::GAME);
		break;
	case Scene::GAME:
		m_shieldManager.UpdateAll(deltaTime);
		m_cityManager.UpdateAll(deltaTime);
		m_spriteManager.UpdateAll(deltaTime);
		m_baseManager.UpdateAll(deltaTime);
		break;
	case Scene::SHOP:
		break;
	case Scene::PAUSE:
		break;
	case Scene::GAME_OVER:
		break;
	}
}

void Game::SwitchScene(Scene scene)
{
	if (m_activeScene == Scene::MAIN_MENU && scene == Scene::GAME) {
		// create terrain
		m_terrain = Entities::Create();
		m_spriteManager.AddComponent(m_terrain, Sprite{
			Render::m_terrain,
			{ 0.0f, -9.0f, 0.0f },
			{ 23.0f, 20.0f, 20.0f },
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
				{ offset * (i / 2 + 1.2f) * 8.0f, -11.0f, 0.0f },
				false,
				false,
				false
			};

			Sprite s{
				Render::m_city,
				{  offset * (i / 2 + 1.2f) * 8.0f, -11.0f, 0.0f},
				{ 13.0f, 13.0f, 13.0f },
				{ 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.02f, 1.0f }
			};
			m_cityManager.AddComponent(m_cities[i], c);
			m_spriteManager.AddComponent(m_cities[i], s);
		}

		// create bases

		for (int i = 0; i < 3; i++) {
			m_bases[i] = Entities::Create();

			m_baseManager.AddComponent(m_bases[i], Base{ {1 + (i - 1) * 15.0f, -11.0f, 0.0f}, false, false, false, false, 10 });
		}

		m_center = Entities::Create();
		m_spriteManager.AddComponent(m_center, Sprite{
			Render::m_shield,
			{ 0.0f, 0.0f, 0.0f },
			{ 10.0f, 10.0f, 10.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 1.0f }
			});
	}

	m_activeScene = scene;

}

void Game::Render()
{
	m_shieldManager.RenderAll();
	m_cityManager.RenderAll();
	m_spriteManager.RenderAll();
	m_baseManager.RenderAll();
}

void Game::RemoveEntity(entity e)
{
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
}

void Game::Shutdown()
{
	for (unsigned int i = 0; i < Entities::GetMaxEntities(); i++) {
		RemoveEntity(i);
	}

	Render::UnloadMeshes();
}

Scene Game::m_activeScene = Scene::MAIN_MENU;

std::array<entity, 6> Game::m_cities;
entity Game::m_center;
entity Game::m_terrain;
std::array<entity, 3> Game::m_bases;

Manager<Shield, ShieldSystem, 10000> Game::m_shieldManager;
Manager<Sprite, SpriteSystem, 10000> Game::m_spriteManager;
Manager<City, CitySystem, 6> Game::m_cityManager;
Manager<Base, BaseSystem, 3> Game::m_baseManager;

ShieldSystem Game::m_shieldSystemInstance;
SpriteSystem Game::m_spriteSystemInstance;
CitySystem Game::m_citySystemInstance;
BaseSystem Game::m_baseSystemInstance;