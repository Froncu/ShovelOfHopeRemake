#include "pch.h"
#include "DirtBlock.h"

#include "FX.h"
#include "SoundManager.h"

#pragma region Constructors/Destructor
DirtBlock::DirtBlock(const Point2f& bottomLeft, Pickupable::Type pickupableToDrop) :
	GameObject(bottomLeft.x + 16.0f, bottomLeft.y + 16.0f),
	KinematicCollider(m_RootCenter, 32.0f, 32.0f),
	HurtBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/DirtBlock.png", 8),

	m_PickupableToDrop{ pickupableToDrop }
{
	HurtBox::AddLocalHurtBox(32.0f, 32.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 240.0f);
}

DirtBlock::DirtBlock(float positionLeft, float positionBottom, Pickupable::Type pickupableToDrop) :
	DirtBlock(Point2f(positionLeft, positionBottom), pickupableToDrop)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void DirtBlock::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	GameObject::Delete();

	GameObject::AddGameObject(new FX(m_RootCenter, "Resources/FX/DirtBlockPop.png", 3, 8, 0.1f));

	if (m_PickupableToDrop != Pickupable::Type::Empty)
	{
		Point2f dropPosition{ Point2f(m_RootCenter.x - 8.0f, m_RootCenter.y) };

		if (hurtNormals.x == 1)
		{
			dropPosition.x += 8.0f;
		}

		GameObject::AddGameObject(new Pickupable(dropPosition, m_PickupableToDrop, 0, 360.0f));

		GameObject::AddGameObject(new FX(m_RootCenter, "Resources/FX/MoneyPoof.png", 7, 8));
	}

	if (hurtNormals.y)
	{
		SoundManager::PlayEffect("Resources/Audio/DirtBlockThrust.wav", false);
	}
	else
	{
		SoundManager::PlayEffect("Resources/Audio/DirtBlockShovel.wav", false);
	}
}
#pragma endregion Components