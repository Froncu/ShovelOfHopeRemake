#pragma once

#include <map>

class InputManager final
{
public:
	//	Other
	friend class Game;

	//	Rule of 5
	~InputManager() = delete;

	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other) = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) = delete;

	//	Other special methods
	InputManager() = delete;

	//	Methods


	//	Setters


	//	Getters
	static bool GetState(const SDL_Keycode& keycode);
	static bool GetState(const Uint8& buttonIndex);
	static const Point2f& GetMousePosition();

protected:


private:
	static void SetKeyboardInput(const SDL_Keycode& keycode, bool isPressed);
	static void SetMouseInput(const Uint8& buttonIndex, bool isPressed);
	static void SetMousePosition(const Point2f& position);

	static std::map<const SDL_Keycode, bool> m_mKEYBOARDINPUTS;
	static std::map<const Uint8, bool> m_mMOUSEINPUTS;
	static Point2f m_MOUSEPOSITION;
};