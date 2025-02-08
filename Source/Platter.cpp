#include "pch.h"
#include "Platter.h"

#include "Particle.h"
#include "Pickupable.h"
#include "SoundManager.h"

#pragma region Constructors/Destructor
Platter::Platter(const Point2f& bottomLeft) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 9.0f, true),
	HurtBox(m_RootCenter, 0.2f),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/Platter.png", 7),

	m_MaxAccumulatedTime{ 0.2f },
	m_AccumulatedTime{}
{
	HurtBox::AddLocalHurtBox(29.0f, 18.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 240.0f);

	HurtBox::m_IsActive = false;
}

Platter::Platter(float positionLeft, float positionBottom) :
	Platter(Point2f(positionLeft, positionBottom))
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Platter::Update(float elapsedSeconds)
{
	if (!HurtBox::m_IsActive)
	{
		m_AccumulatedTime += elapsedSeconds;

		if (m_AccumulatedTime >= m_MaxAccumulatedTime)
		{
			m_AccumulatedTime -= m_MaxAccumulatedTime;

			HurtBox::m_IsActive = true;
		}
	}
}

void Platter::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (!hurtNormals.y)
	{
		SoundManager::PlayEffect("Resources/Audio/OpenPlatter.wav", false);
		GameObject::Delete();

		GameObject::AddGameObject(new Particle{m_RootCenter, "Resources/Particles/Platter0.png", Vector2f(-100.0f, 240.0f) });
		GameObject::AddGameObject(new Particle{m_RootCenter, "Resources/Particles/Platter1.png", Vector2f(100.0f, 240.0f) });

		GameObject::AddGameObject(new Pickupable{ m_RootCenter, Pickupable::Type::Chicken, Vector2f(0.0f, 240.0f) });
	}
}
#pragma endregion Components