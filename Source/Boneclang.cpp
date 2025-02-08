#include "pch.h"
#include "Boneclang.h"

#include "Skull.h"
#include "FX.h"
#include "Pickupable.h"

#include "SoundManager.h"

#include "utils.h"
#include "myutils.h"

#pragma region Constructors/destructor
Boneclang::Boneclang(const GameObject* const pTarget, const Point2f& bottomLeft) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 14.0f, true),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter, 1.0f, Vector2f(140.0f, 360.0f)),
	HurtBox(m_RootCenter),
	HitBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 4.0f, "Entities/Boneclang.png", 8),
	SpriteAnimator(4, 3, 0.5f, 0, 2),

	m_pTarget{ pTarget },

	m_State{ State::Idle },

	m_Health{ 2 },

	m_AccumulatedHitBoxCooldownSeconds{},
	m_MaxHitBoxCooldownSeconds{ 0.2f },

	m_AccumulatedMoveSeconds{}, m_MaxMoveSeconds{},

	m_TriggerDistance{ 160.0f }
{
	m_LocalCollisionBox.width = 16.0f;
	m_LocalCollisionBox.height = 28.0f;

	HurtBox::AddLocalHurtBox(16.0f, 28.0f);
	HurtBox::AddGroupNumber({ 0, 2, 5 });
	HurtBox::SetKnockBackVelocity(0.0f, 360.0f);

	HitBox::AddLocalHitBox(12.0f, 24.0f);
	HitBox::AddLocalHitBox(0.0f, 0.0f, 24.0f, 8.0f);
	HitBox::AddGroupNumber(1);

	HitBox::SetActive(false, 1);
}

Boneclang::Boneclang(const GameObject* const pTarget, float positionLeft, float positionBottom) :
	Boneclang(pTarget, Point2f(positionLeft, positionBottom))
{
}
#pragma endregion Constructors/destructor



#pragma region Components
void Boneclang::Update(float elapsedSeconds)
{
	if (m_State != State::Attack)
	{
		if (m_pTarget->GetRootCenter().x > m_RootCenter.x)
		{
			SimpleSprite::m_IsFlipped = false;
			HitBox::SetLocalHitBox(20.0f, 0.0f, 24.0f, 8.0f, 1);
		}
		else if (m_pTarget->GetRootCenter().x < m_RootCenter.x)
		{
			SimpleSprite::m_IsFlipped = true;
			HitBox::SetLocalHitBox(-20.0f, 0.0f, 24.0f, 8.0f, 1);
		}
	}

	const int sign{ int((m_pTarget->GetRootCenter().x - m_RootCenter.x) / abs(m_pTarget->GetRootCenter().x - m_RootCenter.x)) };
	switch (m_State)
	{
	case Boneclang::State::Idle:
		if (utils::GetDistance(m_pTarget->GetRootCenter(), m_RootCenter) <= m_TriggerDistance)
		{
			m_State = State::MovingTowards;
			SpriteAnimator::SetCurrentRowIndex(1, 4);
			SpriteAnimator::SetFrameSeconds(0.1f);
		}
		break;

	case Boneclang::State::MovingAway:
		m_Velocity.x = -m_MaxVelocity.x / 2 * sign;

		m_AccumulatedMoveSeconds += elapsedSeconds;
		if (m_AccumulatedMoveSeconds >= m_MaxMoveSeconds)
		{
			m_AccumulatedMoveSeconds = 0;

			m_State = State::MovingForAttack;
		}
		break;

	case Boneclang::State::MovingTowards:
		m_Velocity.x = m_MaxVelocity.x / 2 * sign;

		if (utils::GetDistance(m_pTarget->GetRootCenter(), m_RootCenter) <= m_TriggerDistance / 2)
		{
			m_State = State::MovingAway;
			m_MaxMoveSeconds = myutils::GetRandom(1.0f, 0.2f);
		}
		break;

	case Boneclang::State::MovingForAttack:
		m_Velocity.x = m_MaxVelocity.x / 2 * sign;

		if (abs(m_pTarget->GetRootCenter().x - m_RootCenter.x) <= 32.0f)
		{
			m_State = State::Attack;
			m_Velocity.x = 0;

			SpriteAnimator::SetCurrentRowIndex(2, 2);
			SpriteAnimator::SetFrameSeconds(0.5f);
		}
		break;

	case Boneclang::State::Attack:

		break;

	case Boneclang::State::Hurt:
		m_AccumulatedHitBoxCooldownSeconds += elapsedSeconds;
		if (m_AccumulatedHitBoxCooldownSeconds >= m_MaxHitBoxCooldownSeconds)
		{
			m_AccumulatedHitBoxCooldownSeconds = 0;

			m_State = State::MovingTowards;
			SpriteAnimator::SetCurrentRowIndex(1, 4);
			SpriteAnimator::SetFrameSeconds(0.1f);

			m_MaxMoveSeconds = myutils::GetRandom(1.0f, 0.2f);

			m_Velocity.x = 0.0f;

			HitBox::SetActive(true, 0);
		}
		break;
	}
}

void Boneclang::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	SoundManager::PlayEffect("Audio/DigPile.wav", false);
	HitBox::SetActive(false);
	SimpleSprite::Blink(5, m_MaxHitBoxCooldownSeconds);
	SpriteAnimator::SetCurrentRowIndex(0, 2);
	SpriteAnimator::SetFrameSeconds(0.5f);

	m_Velocity.x = hurtNormals.x * m_MaxVelocity.x;
	m_State = State::Hurt;

	if (!--m_Health)
	{
		SoundManager::PlayEffect("Audio/Kill.wav", false);

		GameObject::Delete();
		GameObject::AddGameObject(new FX{ m_RootCenter.x, m_RootCenter.y - 8.0f, "FX/Poof.png", 5, 8, 0.1f });
		GameObject::AddGameObject(new FX{ m_RootCenter.x, m_RootCenter.y + 8.0f, "FX/Poof.png", 5, 8, 0.1f });

		GameObject::AddGameObject(new Skull{ m_RootCenter.x - 8.0f, m_RootCenter.y, GetRandomInitialDropVelocity() });
		GameObject::AddGameObject(new Pickupable{ m_RootCenter, Pickupable::Type::GreenGem, GetRandomInitialDropVelocity() });
		GameObject::AddGameObject(new Pickupable{ m_RootCenter, Pickupable::Type::GoldGem, GetRandomInitialDropVelocity() });
	}
}

void Boneclang::OnColumnChange(int currentColumnIndex)
{
	if (m_State == State::Attack)
	{
		switch (currentColumnIndex)
		{
		case 0:
			m_State = State::MovingTowards;
			SpriteAnimator::SetCurrentRowIndex(1, 4);
			SpriteAnimator::SetFrameSeconds(0.1f);

			HitBox::SetActive(false, 1);
			break;

		case 1:
			SoundManager::PlayEffect("Audio/BoneclangAttack.wav", false);
			HitBox::SetActive(true, 1);
			break;
		}
	}
}
#pragma endregion Components



#pragma region PrivateMethods
Vector2f Boneclang::GetRandomInitialDropVelocity() const
{
	const Vector2f minimalRandomInitialVelocity{ -100.0f, 240.0f }, maximalRandomInitialVelocity{ 100.0f, 360.0f };
	return myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity);
}
#pragma endregion PrivateMethods