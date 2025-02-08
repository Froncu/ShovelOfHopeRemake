#include "pch.h"
#include "DirtBlockSmall.h"

#include "FX.h"
#include "SoundManager.h"

#pragma region Constructors/Destructor
DirtBlockSmall::DirtBlockSmall(const Point2f& bottomLeft, Pickupable::Type pickupableToDrop) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 8.0f),
	KinematicCollider(m_RootCenter, 16.0f, 16.0f),
	HurtBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Environment/DirtBlockSmall.png", 8),

	m_PickupableToDrop{ pickupableToDrop }
{
	HurtBox::AddLocalHurtBox(16.0f, 16.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 240.0f);
}

DirtBlockSmall::DirtBlockSmall(float positionLeft, float positionBottom, Pickupable::Type pickupableToDrop) :
	DirtBlockSmall(Point2f(positionLeft, positionBottom), pickupableToDrop)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void DirtBlockSmall::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	GameObject::Delete();

	GameObject::AddGameObject(new FX(m_RootCenter, "FX/DirtBlockSmallPop.png", 3, 8, 0.1f));

	if (m_PickupableToDrop != Pickupable::Type::Empty)
	{
		GameObject::AddGameObject(new Pickupable(m_RootCenter, m_PickupableToDrop, 0, 360.0f));

		GameObject::AddGameObject(new FX(m_RootCenter, "FX/MoneyPoofSmall.png", 7, 8));
	}		

	if (hurtNormals.y)
	{
		SoundManager::PlayEffect("Audio/DirtBlockThrust.wav", false);
	}
	else
	{
		SoundManager::PlayEffect("Audio/DirtBlockShovel.wav", false);
	}
}
#pragma endregion Components