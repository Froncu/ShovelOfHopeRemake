#include "pch.h"
#include "Game.h"

#include "InputManager.h"
#include "LevelManager.h"
#include "SoundManager.h"

Game::Game(const Window& window) :
	BaseGame{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	LevelManager::Load(GetViewPort());
}

void Game::Cleanup()
{
	LevelManager::Close();
	SoundManager::DeleteAll();
}

void Game::Update(float elapsedSec)
{
	LevelManager::Update(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();

	LevelManager::Draw();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	InputManager::SetKeyboardInput(e.keysym.sym, true);
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	InputManager::SetKeyboardInput(e.keysym.sym, false);
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	InputManager::SetMousePosition(Point2f(float(e.x), float(e.y)));
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	InputManager::SetMouseInput(e.button, true);
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	InputManager::SetMouseInput(e.button, false);
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}