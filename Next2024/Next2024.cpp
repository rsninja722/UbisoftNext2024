//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

#include "src/Game.h"
#include "engine/Log.h"
#include "engine/ECS/Entities.h"
#include "ECSdefs/Shield.h"


// comment out to enable debug mode
#define DEBUG


float lastMouseX = 0.0f;
float lastMouseY = 0.0f;


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	Game::Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{

	Game::Update(deltaTime);

	// debug camera movement
#ifdef DEBUG

	Vec3 move{ 0.0f, 0.0f, 0.0f };

	if (App::IsKeyPressed('I')) {
		move += Vec3(0.0f, 0.0f, 1.0f);
	}
	if (App::IsKeyPressed('K')) {
		move += Vec3(0.0f, 0.0f, -1.0f);
	}
	if (App::IsKeyPressed('U')) {
		move += Vec3(0.0f, 1.0f, 0.0f);
	}
	if (App::IsKeyPressed('O')) {
		move += Vec3(0.0f, -1.0f, 0.0f);
	}
	if (App::IsKeyPressed('J')) {
		move += Vec3(-1.0f, 0.0f, 0.0f);
	}
	if (App::IsKeyPressed('L')) {
		move += Vec3(1.0f, 0.0f, 0.0f);
	}

	Render::UpdateCameraPos(move.ScalarMultiplyEquals(10.0f));

#endif // DEBUG

	App::GetMousePos(lastMouseX, lastMouseY);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	Render::RenderFirstStep();

	Game::Render();

	Render::RenderFinalStep();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	Game::Shutdown();
}