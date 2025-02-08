#include "pch.h"
#include "Dozedrake.h"

#include "Bubble.h"
#include "FX.h"

#include "SoundManager.h"

#include "myutils.h"

#pragma region Constructors/Destructor
Dozedrake::Dozedrake(const Point2f& bottomLeft) :
	GameObject(bottomLeft.x + 64.0f, bottomLeft.y + 44.5f, true),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter, 0.0f, Vector2f(48.0f, 0.0f)),
	HurtBox(m_RootCenter),
	HitBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 12.0f, -2.0f, "Resources/Entities/Dozedrake.png", 8),
	SpriteAnimator(12, 6, 0.1f, 0, 12),

	m_State{ State::Sleeping },

	m_Health{ 7 },

	m_MaxDyingSeconds{ 2.0f }, m_MaxKnockingSeconds{ 1.5f },
	m_AccumulatedDyingSeconds{},

	m_BlowingCooldownSeconds{ 1.0f },
	m_AccumulatedBlowingCooldownSeconds{},

	m_DeltaBlowSeconds{ 0.2f },
	m_AccumulatedBlowSeconds{},
	m_AmountOfBubblesToBlow{ 3 },
	m_AmountOfBlownBubbles{},

	m_DropRandomlyCounter{}, FXCounter{},
	m_FirstDropRandomlySeconds{ 0.6f }, m_SecondDropRandomlySeconds{ 1.0f }, m_DeltaFXSeconds{ 0.3f }
{
	m_LocalCollisionBox = Rectf(0.0f, -12.0f, 128.0f, 64.0f);

	HurtBox::AddLocalHurtBox(24.0f, -12.5f, 80.0f, 64.0f);
	HurtBox::AddLocalHurtBox(-40.0f, -28.5f, 48.0f, 32.0f);
	HurtBox::AddGroupNumber({ 0, 5 });
	HurtBox::SetKnockBackVelocity(0.0f, 420.0f);

	HitBox::AddLocalHitBox(24.0f, -14.5f, 80.0f, 56.0f);
	HitBox::AddLocalHitBox(-40.0f, -32.5f, 48.0f, 24.0f);
	HitBox::AddGroupNumber(1);

	SimpleSprite::m_IsFlipped = true;
}

Dozedrake::Dozedrake(float positionLeft, float positionBottom) :
	Dozedrake(Point2f(positionLeft, positionBottom))
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Dozedrake::Update(float elapsedSeconds)
{
	switch (m_State)
	{
	case Dozedrake::State::BlowingCooldown:
		m_AccumulatedBlowingCooldownSeconds += elapsedSeconds;
		if (m_AccumulatedBlowingCooldownSeconds >= m_BlowingCooldownSeconds)
		{
			m_AccumulatedBlowingCooldownSeconds = 0.0f;
			SpriteAnimator::SetFrameSeconds(0.1f);
			m_State = State::Sleeping;
		}
		break;

	case Dozedrake::State::Blowing:
		m_AccumulatedBlowSeconds += elapsedSeconds;
		if (m_AccumulatedBlowSeconds >= m_DeltaBlowSeconds)
		{
			m_AccumulatedBlowSeconds -= m_DeltaBlowSeconds;
			++m_AmountOfBlownBubbles;

			if (m_AmountOfBlownBubbles <= m_AmountOfBubblesToBlow)
			{
				const Point2f mouthCenter{ m_RootCenter.x - 48.0f, m_RootCenter.y - 32.0f };
				const float offset{ 8.0f };
				const Point2f randomPosition{ myutils::GetRandom(mouthCenter.x - offset, mouthCenter.x + offset), myutils::GetRandom(mouthCenter.y - offset, mouthCenter.y + offset) };
				GameObject::AddGameObject(new Bubble{ randomPosition, myutils::GetRandom(-80.0f, -112.0f), INFINITY, false });
			}
			else
			{
				m_State = State::ClosingMouth;
				m_AmountOfBlownBubbles = 0;
				SpriteAnimator::SetCurrentRowIndex(3, 1);
			}
		}
		break;

	case Dozedrake::State::Hurt:
		if (myutils::GetRandom(1, 0))
		{
			m_State = State::WalkingForward;
			m_Velocity.x = m_MaxVelocity.x;
			SpriteAnimator::SetCurrentRowIndex(2, 6);
		}
		else
		{
			m_State = State::WalkingBackward;
			m_Velocity.x = -m_MaxVelocity.x;
			SpriteAnimator::SetCurrentRowIndex(1, 6);
		}
		break;

	case Dozedrake::State::Dying:
		m_AccumulatedDyingSeconds += elapsedSeconds;

		if (m_AccumulatedDyingSeconds <= m_MaxKnockingSeconds) SoundManager::PlayEffect("Resources/Audio/BubbleThrust.wav", false);

		if (m_AccumulatedDyingSeconds >= m_MaxDyingSeconds)
		{
			GameObject::Delete();

			GameObject::AddGameObject(new FX{ m_RootCenter.x + 24.0f, m_RootCenter.y, "Resources/FX/ExplosionSmall.png", 5, 11 });

			DropRandomly(Pickupable::Type::GreyGem, 3);
			DropRandomly(Pickupable::Type::GoldGem, 1);
			DropRandomly(Pickupable::Type::RedGem, 2);
			DropRandomly(Pickupable::Type::BlueGem, 1);
			DropRandomly(Pickupable::Type::Apple, 1);
		}
		else if (m_AccumulatedDyingSeconds >= m_SecondDropRandomlySeconds && m_DropRandomlyCounter == 1)
		{
			++m_DropRandomlyCounter;

			DropRandomly(Pickupable::Type::GreyGem, 2);
			DropRandomly(Pickupable::Type::GoldGem, 1);
			DropRandomly(Pickupable::Type::GreenGem, 1);
		}
		else if (m_AccumulatedDyingSeconds >= m_FirstDropRandomlySeconds && !m_DropRandomlyCounter)
		{
			++m_DropRandomlyCounter;
			DropRandomly(Pickupable::Type::GoldGem, 2);
		}

		if (FXCounter < 5 && m_AccumulatedDyingSeconds >= m_DeltaFXSeconds * FXCounter)
		{
			++FXCounter;

			const Vector2f randomOffset{ myutils::GetRandom(Vector2f(64.0f, 32.0f), Vector2f(-64.0f, -32.0f)) };
			GameObject::AddGameObject(new FX{ m_RootCenter + randomOffset, "Resources/FX/ExplosionSmall.png", 5, 11 });
		}

		break;
	}
}

void Dozedrake::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (localHurtBoxIndex == 1 && m_Health)
	{
		SoundManager::PlayEffect("Resources/Audio/DozendrakeDamage.wav", false);

		switch (m_State)
		{
		case Dozedrake::State::WalkingForward:
		case Dozedrake::State::WalkingBackward:
		case Dozedrake::State::OpeningMouth:
		case Dozedrake::State::Blowing:
			if (m_AmountOfBlownBubbles)
			{
				m_State = State::Hurt;
				SpriteAnimator::SetFrameSeconds(0.1f);
				m_AmountOfBlownBubbles = 0;
				m_AccumulatedBlowSeconds = 0;
			}
			break;

		default:
			m_State = State::Hurt;
			SpriteAnimator::SetFrameSeconds(0.1f);
			m_AmountOfBlownBubbles = 0;
			m_AccumulatedBlowSeconds = 0;
			break;
		}

		if (!--m_Health)
		{
			SoundManager::PlayEffect("Resources/Audio/DozendrakeDie.wav", false);
			m_State = State::Dying;
			SpriteAnimator::SetCurrentRowIndex(5, 1);
			SimpleSprite::Blink(50, m_MaxDyingSeconds);

			HurtBox::m_IsActive = false;
			HitBox::SetActive(false);
		}
		else
		{
			SimpleSprite::Blink(5, 0.2f);
		}
	}
	else if (localHurtBoxIndex == 0)
	{
		SoundManager::PlayEffect("Resources/Audio/BubbleThrust.wav", false);
	}
}

void Dozedrake::OnColumnChange(int currentColumnIndex)
{
	switch (m_State)
	{
	case Dozedrake::State::Sleeping:
		if (currentColumnIndex == 0)
		{
			m_State = State::OpeningMouth;
			SpriteAnimator::SetCurrentRowIndex(3, 1);
		}
		break;

	case Dozedrake::State::OpeningMouth:
		SoundManager::PlayEffect("Resources/Audio/DozendrakeShoot.wav", false);
		m_State = State::Blowing;
		SpriteAnimator::SetCurrentRowIndex(4, 1);
		break;

	case Dozedrake::State::Blowing:

		break;

	case Dozedrake::State::ClosingMouth:
		SpriteAnimator::SetFrameSeconds(INFINITY);
		SpriteAnimator::SetCurrentRowIndex(0, 12);
		m_State = State::BlowingCooldown;
		break;

	case Dozedrake::State::WalkingForward:
	case Dozedrake::State::WalkingBackward:
		if (currentColumnIndex == 0)
		{
			m_State = State::OpeningMouth;
			m_Velocity.x = 0.0f;
		}
		break;
	}
}
#pragma endregion Components



#pragma region PrivateMethods
void Dozedrake::DropRandomly(Pickupable::Type type, int amount)
{
	for (int index{}; index < amount; ++index)
	{
		const Vector2f minimalRandomInitialVelocity{ -100.0f, 240.0f }, maximalRandomInitialVelocity{ 100.0f, 360.0f };
		const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };
		GameObject::AddGameObject(new Pickupable(m_RootCenter.x + 24.0f, m_RootCenter.y, type, 0.75f * randomInitialVelocity.x, randomInitialVelocity.y));
	}
}
#pragma endregion PrivateMethods