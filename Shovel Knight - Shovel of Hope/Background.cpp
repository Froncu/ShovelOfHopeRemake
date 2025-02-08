#include "pch.h"
#include "Background.h"

#pragma region Constructors/Destructor
Background::Background(const Point2f& bottomLeft, const std::string& spritePath, int layer, int amountOfColumns, int tileX, int tileY) :
	GameObject(),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, spritePath, layer, tileX, tileY),
	SpriteAnimator(amountOfColumns, 1, 0.2f, 0, 3)
{
	m_RootCenter.x = bottomLeft.x + SimpleSprite::GetSourceRectangle().width / amountOfColumns * tileX / 2;
	m_RootCenter.y = bottomLeft.y + SimpleSprite::GetSourceRectangle().height * tileY / 2;
}

Background::Background(float positionBottom, float positionLeft, const std::string& spritePath, int layer, int amountOfColumns, int tileX, int tileY) :
	Background(Point2f(positionBottom, positionLeft), spritePath, layer, amountOfColumns, tileX, tileY)
{
}
#pragma endregion Constructors/Destructor