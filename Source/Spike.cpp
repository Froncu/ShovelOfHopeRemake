#include "pch.h"
#include "Spike.h"

#pragma region Constructors/Destructor
Spike::Spike(const Point2f& bottomLeft, int width) :
	GameObject(bottomLeft.x + 16.0f * width / 2, bottomLeft.y + 8.0f),
	KinematicCollider(m_RootCenter, 16.0f * width, 14.0f),
	HitBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/Spike.png", 7, width, 1)
{
	HitBox::AddLocalHitBox(16.0f * width, 14.0f);
	HitBox::AddGroupNumber({ 0, 1, 2, 3 });
	HitBox::SetDamage(INT_MAX);
}

Spike::Spike(float positionLeft, float positionBottom, int width) :
	Spike(Point2f(positionLeft, positionBottom), width)
{
}
#pragma endregion Constructors/Destructor