#include "pch.h"
#include "DigClod.h"

#include "Particle.h"
#include "Camera.h"
#include "Clod.h"

#include "myutils.h"

#include "SoundManager.h"

#pragma region Constructors/Destructor
DigClod::DigClod(const Point2f& bottomLeft, bool isFlipped) :
	GameObject(bottomLeft.x + (isFlipped ? 11.0f : 5.0f), bottomLeft.y + 12.5f, true),
	HurtBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/DigClod.png", 7),
	SpriteAnimator(5, 3, 0.1f, 0, 1),

	m_MaxIdleSeconds{ 4.0f }, m_MaxDespawningSeconds{ 0.8f },
	m_AccumulatedSeconds{},

	m_IsFlipped{ isFlipped }
{
	HurtBox::AddLocalHurtBox(10.0f, 25.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 360.0f);

	SimpleSprite::m_IsFlipped = m_IsFlipped;
}

DigClod::DigClod(float positionLeft, float positionBottom, bool isFlipped) :
	DigClod(Point2f(positionLeft, positionBottom), isFlipped)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void DigClod::Update(float elapsedSeconds)
{
	m_AccumulatedSeconds += elapsedSeconds;

	if (HurtBox::m_IsActive && m_AccumulatedSeconds >= m_MaxIdleSeconds)
	{
		m_AccumulatedSeconds -= m_MaxIdleSeconds;

		SpriteAnimator::SetCurrentRowIndex(1, 5, true);
	}
	else if (!HurtBox::m_IsActive && m_AccumulatedSeconds >= m_MaxDespawningSeconds)
	{
		GameObject::Delete();
	}
}

void DigClod::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	SoundManager::PlayEffect("Resources/Audio/DigClodBreak.wav", false);

	SpriteAnimator::SetCurrentRowIndex(2, 1);
	SimpleSprite::Blink(int(10 * m_MaxDespawningSeconds), m_MaxDespawningSeconds);

	HurtBox::m_IsActive = false;

	const Vector2f initialVelocity{ 100.0f, 240.0f };
	GameObject::AddGameObject(new Clod{ m_RootCenter.x + (m_IsFlipped ? -12.0f : 12.0f), m_RootCenter.y, Vector2f(m_IsFlipped ? -initialVelocity.x : initialVelocity.x, initialVelocity.y) });

	m_AccumulatedSeconds = 0;
}
#pragma endregion Components