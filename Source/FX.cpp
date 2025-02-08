#include "pch.h"
#include "FX.h"

#pragma region Constructors/Destructor
FX::FX(const Point2f& center, const std::string& spritePath, int amountOfColumns, int layer, float frameTime, bool isFlipped) :
	GameObject(center),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, spritePath, layer),
	SpriteAnimator(amountOfColumns, 1, frameTime, 0, 0)
{
	SimpleSprite::m_IsFlipped = isFlipped;
}

FX::FX(float centerX, float centerY, const std::string& spritePath, int amountOfColumns, int layer, float frameTime, bool isFlipped) :
	FX(Point2f(centerX, centerY), spritePath, amountOfColumns, layer, frameTime, isFlipped)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void FX::OnColumnChange(int currentColumnIndex)
{
	if (!currentColumnIndex)
	{
		GameObject::Delete();
	}
}
#pragma endregion Components