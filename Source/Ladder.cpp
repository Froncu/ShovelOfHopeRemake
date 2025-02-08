#include "pch.h"
#include "Ladder.h"

#pragma region Constructors/Destructor
Ladder::Ladder(const Point2f& bottomLeft, int height) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + (height * 16.0f) / 2),
	Interactable(m_RootCenter, 12.0f, height * 16.0f),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/Ladder.png", 7, 1, height)
{
}

Ladder::Ladder(float positionLeft, float positionBottom, int height) :
	Ladder(Point2f(positionLeft, positionBottom), height)
{
}
#pragma endregion Constructors/Destructor