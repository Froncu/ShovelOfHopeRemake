#include "pch.h"
#include "Divedrake.h"

#include "FX.h"
#include "Pickupable.h"

#include "myutils.h"
#include "SoundManager.h"

#pragma region Constructors/Destructor
Divedrake::Divedrake(const Point2f& pivotPoint, float horizontalAmplitude, float verticalAmplitude) :
	GameObject(pivotPoint, true),
	Rigidbody(m_RootCenter),
	HurtBox(m_RootCenter),
	HitBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 2.0f, "Resources/Entities/Divedrake.png", 11),
	SpriteAnimator(3, 2, 0.2f, 0, 3),

	m_PivotPoint{ m_RootCenter },
	m_HorizontalAmplitude{ horizontalAmplitude }, m_VerticalAmplitude{ verticalAmplitude },

	m_Period{ 6.0f },
	m_AccumulatedSeconds{},

	m_Health{ 2 }
{
	Rigidbody::SetGravityMultiplier(0.0f);

	HurtBox::AddLocalHurtBox(24.0f, 16.0f);
	HurtBox::AddGroupNumber({ 0, 5 });
	HurtBox::SetKnockBackVelocity(0.0f, 360.0f);

	HitBox::AddLocalHitBox(20.0f, 12.0f);
	HitBox::AddGroupNumber(1);
}

Divedrake::Divedrake(float pivotPointX, float pivotPointY, float horizontalAmplitude, float verticalAmplitude) :
	Divedrake(Point2f(pivotPointX, pivotPointY), horizontalAmplitude, verticalAmplitude)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Divedrake::Update(float elapsedSeconds)
{
	const float pi{ 3.14159265359f };

	m_AccumulatedSeconds += elapsedSeconds;

	m_RootCenter.x = m_PivotPoint.x + m_HorizontalAmplitude * cosf(m_AccumulatedSeconds * 2 * pi / m_Period);
	m_RootCenter.y = m_PivotPoint.y + m_VerticalAmplitude * sinf(m_AccumulatedSeconds * 2 * pi / m_Period);

	if (m_AccumulatedSeconds >= m_Period) m_AccumulatedSeconds -= m_Period;

	SimpleSprite::m_IsFlipped = m_AccumulatedSeconds <= pi;
}

void Divedrake::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	SimpleSprite::Blink(5, 0.5f);

	if (!--m_Health)
	{
		SoundManager::PlayEffect("Resources/Audio/Kill.wav", false);
		GameObject::Delete();
		GameObject::AddGameObject(new FX{ m_RootCenter, "Resources/FX/Poof.png", 5, 11, 0.1f });

		const Vector2f minimalRandomInitialVelocity{ -100.0f, 240.0f }, maximalRandomInitialVelocity{ 100.0f, 360.0f };
		const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };
		GameObject::AddGameObject(new Pickupable{ m_RootCenter, Pickupable::Type::GreenGem, randomInitialVelocity });
	}
	else
	{
		SoundManager::PlayEffect("Resources/Audio/DigPile.wav", false);
	}
}
#pragma endregion Components