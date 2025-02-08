#include "pch.h"
#include "InputManager.h"

#pragma region StaticVariables
std::map<const SDL_Keycode, bool> InputManager::m_mKEYBOARDINPUTS;
std::map<const Uint8, bool> InputManager::m_mMOUSEINPUTS;
Point2f InputManager::m_MOUSEPOSITION;
#pragma endregion StaticVariables



#pragma region PublicMethods
bool InputManager::GetState(const SDL_Keycode& keycode)
{
	if (m_mKEYBOARDINPUTS.end() != m_mKEYBOARDINPUTS.find(keycode))
	{
		return m_mKEYBOARDINPUTS.at(keycode);
	}
	
	return false;
}

bool InputManager::GetState(const Uint8& buttonIndex)
{
	if (m_mMOUSEINPUTS.end() != m_mMOUSEINPUTS.find(buttonIndex))
	{
		return m_mMOUSEINPUTS.at(buttonIndex);
	}

	return false;
}

const Point2f& InputManager::GetMousePosition()
{
	return m_MOUSEPOSITION;
}
#pragma endregion PublicMethods



#pragma region PrivateMethods
void InputManager::SetKeyboardInput(const SDL_Keycode& keycode, bool isPressed)
{
	if (!m_mKEYBOARDINPUTS.insert(std::pair<const SDL_Keycode, bool>(keycode, isPressed)).second)
	{
		m_mKEYBOARDINPUTS.at(keycode) = isPressed;
	}
}

void InputManager::SetMouseInput(const Uint8& buttonIndex, bool isPressed)
{
	if (!m_mMOUSEINPUTS.insert(std::pair<const Uint8, bool>(buttonIndex, isPressed)).second)
	{
		m_mMOUSEINPUTS.at(buttonIndex) = isPressed;
	}
}

void InputManager::SetMousePosition(const Point2f& position)
{
	m_MOUSEPOSITION = position;
}
#pragma endregion PrivateMethods