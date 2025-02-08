#include "pch.h"
#include "Bubble.h"

#include "FX.h"
#include "Camera.h"
#include "SoundManager.h"

#pragma region Constructors/Destructor
Bubble::Bubble(const Point2f& center, const Point2f& localTargetCenter, bool respawn) :
	GameObject(center, true),
	HurtBox(m_RootCenter),
	HitBox(m_RootCenter),
	Rigidbody(m_RootCenter, 1.0f, Vector2f(200.0f, 32.0f)),
	SimpleSprite(m_RootCenter, 0, 0, "Resources/Environment/Bubble.png", 11),
	SpriteAnimator(4, 1, 0.2f),

	m_SpawnCenter{ m_RootCenter }, m_TargetCenter{ m_SpawnCenter.x + localTargetCenter.x, m_SpawnCenter.y + localTargetCenter.y },

	m_Respawn{ respawn },

	m_Direction{ Vector2f(	m_SpawnCenter.x < m_TargetCenter.x ? 1.0f :				// Nested control expressions, did not know it is possible lol very cool :)
							m_SpawnCenter.x == m_TargetCenter.x ? 0.0f : -1.0f,

							m_SpawnCenter.y < m_TargetCenter.y ? 1.0f :
							m_SpawnCenter.y == m_TargetCenter.y ? 0.0f : -1.0f) },

	m_HorizontalAmplitude{ 2.0f },

	m_AccumulatedSeconds{}, m_Period{ 4.0f }
{
	HurtBox::AddLocalHurtBox(27.0f, 27.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 420.0f);

	HitBox::AddLocalHitBox(27.0f, 27.0f);
	HitBox::AddGroupNumber(1);

	Rigidbody::SetGravityMultiplier(0.0f);

	m_Velocity.x = m_Direction.x * m_MaxVelocity.x;
	if (m_Velocity.x == 0) m_Velocity.y = m_Direction.y * m_MaxVelocity.y;
}

Bubble::Bubble(float positionX, float positionY, const Point2f& localTargetCenter, bool respawn) :
	Bubble(Point2f(positionX, positionY), localTargetCenter, respawn)
{
}

Bubble::Bubble(const Point2f& center, float localTargetPositionX, float localTargetPositionY, bool respawn) :
	Bubble(center, Point2f(localTargetPositionX, localTargetPositionY), respawn)
{
}

Bubble::Bubble(float positionX, float positionY, float localTargetPositionX, float localTargetPositionY, bool respawn) :
	Bubble(Point2f(positionX, positionY), Point2f(localTargetPositionX, localTargetPositionY), respawn)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Bubble::Update(float elapsedSeconds)
{
	m_AccumulatedSeconds += elapsedSeconds;
	SimpleSprite::m_OffsetX = m_HorizontalAmplitude * cosf(m_AccumulatedSeconds * 2 * float(M_PI) / m_Period);

	if (m_AccumulatedSeconds >= m_Period) m_AccumulatedSeconds -= m_Period;

	if (m_Velocity.x > 0 && m_RootCenter.x > m_TargetCenter.x)
	{
		m_RootCenter.x = m_TargetCenter.x;

		m_Velocity.x = 0;
		m_Velocity.y = m_Direction.y * m_MaxVelocity.y;
	}
	else if (m_Velocity.x < 0 && m_RootCenter.x < m_TargetCenter.x)
	{
		m_RootCenter.x = m_TargetCenter.x;

		m_Velocity.x = 0;
		m_Velocity.y = m_Direction.y * m_MaxVelocity.y;
	}

	if (m_Velocity.y > 0 && m_RootCenter.y > m_TargetCenter.y)
	{
		m_RootCenter.y = m_TargetCenter.y;

		m_Velocity.y = 0;
	}
	else if (m_Velocity.y < 0 && m_RootCenter.y < m_TargetCenter.y)
	{
		m_RootCenter.y = m_TargetCenter.y;

		m_Velocity.y = 0;
	}

	if (abs(m_SpawnCenter.y - m_RootCenter.y) > Camera::GetTransformedViewPort().height)
	{
		Pop();
	}
}

void Bubble::OnHit(const Vector2f& hitNormals, const Vector2f& knockBackVelocity, int localHurtBoxIndex)
{
	Pop();
}

void Bubble::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (hurtNormals.y) SoundManager::PlayEffect("Resources/Audio/BubbleThrust.wav", false);
	Pop();
}
#pragma endregion Components



#pragma region PrivateMethods
void Bubble::Pop()
{
	GameObject::Delete();
	GameObject::AddGameObject(new FX{ m_RootCenter, "Resources/FX/BubblePop.png", 2, 11 });

	if (m_Respawn)
	{
		GameObject::AddGameObject(new Bubble{ m_SpawnCenter, m_TargetCenter.x - m_SpawnCenter.x, m_TargetCenter.y - m_SpawnCenter.y, true });
	}
}
#pragma endregion PrivateMethods