#pragma once

#include "BaseGame.h"
#include <vector>

#include "HUD.h"

class Game final : public BaseGame
{
public:
	explicit Game(const Window& window);
	Game(const Game &other) = delete;
	Game& operator=(const Game &other) = delete;
	Game(Game &&other) = delete;
	Game& operator=(Game &&other) = delete;
	~Game();

	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void Update(float elapsedSec) override;
	void Draw() const override;

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

private:

};