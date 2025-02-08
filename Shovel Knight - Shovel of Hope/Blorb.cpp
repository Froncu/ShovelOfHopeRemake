#include "pch.h"
#include "Blorb.h"

#include "FX.h"
#include "Pickupable.h"

#include "myutils.h"
#include "SoundManager.h"

#pragma region Constructors/destructor
Blorb::Blorb(const GameObject* const pTarget, const Point2f& bottomLeft) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 5.0f, true),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter, 1.0f, Vector2f(100.0f, 140.0f)),
	HurtBox(m_RootCenter),
	HitBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Entities/Blorb.png", 8),
	SpriteAnimator(4, 1, 0.2f),

	m_pTarget{ pTarget },

	m_State{ State::Idle },

	m_Health{ 2 },

	m_AccumulatedSeconds{}, m_MaxSeconds{},

	m_TriggerDistance{ 160.0f }, m_AttackDistance{ 96.0f }
{
	m_LocalCollisionBox.width = 20.0f;
	m_LocalCollisionBox.height = 11.0f;

	Rigidbody::SetGravityMultiplier(0.5f);

	HurtBox::AddLocalHurtBox(20.0f, 11.0f);
	HurtBox::AddGroupNumber({ 0, 5 });
	HurtBox::SetKnockBackVelocity(0.0f, 360.0f);

	HitBox::AddLocalHitBox(16.0f, 7.0f);
	HitBox::AddGroupNumber(1);
}

Blorb::Blorb(const GameObject* const pTarget, float positionLeft, float positionBottom) :
	Blorb(pTarget, Point2f(positionLeft, positionBottom))
{
}
#pragma endregion Constructors/destructor



#pragma region Components
void Blorb::Update(float elapsedSeconds)
{
	if (m_RootCenter.x < 0.0f)
	{
		std::cout << "why";
	}

	Vector2f direction{ (m_pTarget->GetRootCenter().x - m_RootCenter.x) / abs(m_pTarget->GetRootCenter().x - m_RootCenter.x), (m_pTarget->GetRootCenter().y - m_RootCenter.y) / abs(m_pTarget->GetRootCenter().y - m_RootCenter.y) };

	switch (m_State)
	{	
	case Blorb::State::Idle:
		m_Velocity.x = 0;
		SpriteAnimator::SetFrameSeconds(0.2f);

		m_AccumulatedSeconds += elapsedSeconds;
		if (m_AccumulatedSeconds >= m_MaxSeconds)
		{
			m_AccumulatedSeconds -= m_MaxSeconds;

			m_State = State::Slow;
			m_MaxSeconds = myutils::GetRandom(6.0f, 3.0f);
		}
		break;

	case Blorb::State::Hurt:
		m_AccumulatedSeconds += elapsedSeconds;
		if (m_AccumulatedSeconds >= m_MaxSeconds)
		{
			m_AccumulatedSeconds -= m_MaxSeconds;

			m_Velocity.x = 0.0f;

			m_State = State::Idle;
			m_MaxSeconds = myutils::GetRandom(1.0f, 0.5f);
		}
		break;

	case Blorb::State::Slow:
		m_Velocity.x = direction.x * m_MaxVelocity.x / 10;
		SpriteAnimator::SetFrameSeconds(0.2f);

		m_AccumulatedSeconds += elapsedSeconds;
		if (m_AccumulatedSeconds >= m_MaxSeconds)
		{
			m_AccumulatedSeconds -= m_MaxSeconds;

			if (myutils::GetRandom(1))
			{
				m_State = State::Idle;
				m_MaxSeconds = myutils::GetRandom(3.0f, 1.0f);
			}
			else
			{
				if (abs(m_pTarget->GetRootCenter().x - m_RootCenter.x) < m_AttackDistance)
				{
					m_State = State::Jump;
				}
				else
				{
					m_State = State::Fast;
					m_MaxSeconds = myutils::GetRandom(6.0f, 3.0f);
				}
			}
		}
		break;

	case Blorb::State::Fast:
		m_Velocity.x = direction.x * m_MaxVelocity.x / 4;
		SpriteAnimator::SetFrameSeconds(0.1f);

		m_AccumulatedSeconds += elapsedSeconds;
		if (m_AccumulatedSeconds >= m_MaxSeconds)
		{
			m_AccumulatedSeconds -= m_MaxSeconds;

			if (abs(m_pTarget->GetRootCenter().x - m_RootCenter.x) < m_AttackDistance)
			{
				m_State = State::Jump;
			}
			else
			{
				m_State = State::Slow;
				m_MaxSeconds = myutils::GetRandom(6.0f, 3.0f);
			}
		}
		break;

	case Blorb::State::Jump:
		SpriteAnimator::SetFrameSeconds(0.2f);
		m_Velocity.x = 0;
		m_Velocity.y = m_MaxVelocity.y;

		SoundManager::PlayEffect("Audio/BlorbJump.wav", false);
		m_State = State::Jumped;
		break;

	case Blorb::State::Attack:
		SpriteAnimator::SetFrameSeconds(0.2f);
		m_Velocity.x = direction.x * m_MaxVelocity.x;
		m_Velocity.y = m_MaxVelocity.y;

		SoundManager::PlayEffect("Audio/BlorbJump.wav", false);
		m_State = State::Attacked;
		break;
	}
}

void Blorb::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (m_State != State::Attack && m_State != State::Attacked)
	{
		if (!hurtNormals.y) m_Velocity.x = hurtNormals.x * m_MaxVelocity.x;

		m_State = State::Hurt;

		m_AccumulatedSeconds = 0.0f;
		m_MaxSeconds = 0.2f;
		SimpleSprite::Blink(5, m_MaxSeconds);
	}

	if (!--m_Health)
	{
		SoundManager::PlayEffect("Audio/Kill.wav", false);
		GameObject::Delete();

		GameObject::AddGameObject(new FX{ m_RootCenter, "FX/Poof.png", 5, 8, 0.1f });

		const Vector2f minimalRandomInitialVelocity1{ -100.0f, 240.0f }, maximalRandomInitialVelocity1{ 100.0f, 360.0f };
		const Vector2f randomInitialVelocity1{ myutils::GetRandom(maximalRandomInitialVelocity1, minimalRandomInitialVelocity1) };
		GameObject::AddGameObject(new Pickupable{ m_RootCenter, Pickupable::Type::BlueGem, randomInitialVelocity1 });

		const Vector2f minimalRandomInitialVelocity2{ -100.0f, 240.0f }, maximalRandomInitialVelocity2{ 100.0f, 360.0f };
		const Vector2f randomInitialVelocity2{ myutils::GetRandom(maximalRandomInitialVelocity2, minimalRandomInitialVelocity2) };
		GameObject::AddGameObject(new Pickupable{ m_RootCenter, Pickupable::Type::GreenGem, randomInitialVelocity2 });
	}
	else
	{
		SoundManager::PlayEffect("Audio/DigPile.wav", false);
	}
}

void Blorb::OnCollision(const utils::HitInfo& hitInfo)
{
	if (hitInfo.normal == VERTICALNORMAL)
	{
		if (m_State == State::Jumped)
		{
			m_State = State::Attack;
		}
		else if (m_State == State::Attacked)
		{
			m_State = State::Idle;
			m_MaxSeconds = myutils::GetRandom(1.0f);
		}
	}
}