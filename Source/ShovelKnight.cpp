#include "pch.h"
#include "ShovelKnight.h"

#include "InputManager.h"
#include "SoundManager.h"

#include "FX.h"
#include "Pickupable.h"

#pragma region Constructors/Destructor
ShovelKnight::ShovelKnight(const Point2f& bottomLeft, int startingHealth, int startingScore) :
	GameObject(bottomLeft.x + 7.5f, bottomLeft.y + 13.0f),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter),
	HurtBox(m_RootCenter, 2.0f),
	HitBox(m_RootCenter),
	Interactor(m_RootCenter, 0.0f, -2.0f, 15.0f, 22.0f),
	Pickupper(m_RootCenter, 15.0f, 26.0f),
	SimpleSprite(m_RootCenter, 0.0f, 8.5f, "Resources/Entities/ShovelKnight.png", 9),
	SpriteAnimator(6, 15, 0.09f, 1, 1),

	m_MaxIdleTime{ 8.0f },
	m_AccumulatedIdleTime{},

	m_InteractState{ InteractState::None },

	m_SwingingState{ SwingingState::None },

	m_CombatState{ CombatState::None },
	m_MinAirSeconds{ 0.1f },
	m_MaxHurtSeconds{ 0.5f },
	m_AccumulatedHurtSeconds{},

	m_JumpChargeState{ JumpChargeState::ChargeCooldown },
	m_JumpVelocity{ 240.0f }, m_MaxJumpChargeSeconds{ 0.2f },
	m_AccumulatedJumpChargeSeconds{},

	m_VerticalState{ VerticalState::Standing },
	m_AccumulatedAirSeconds{},

	m_HorizontalState{ HorizontalState::Standing },
	m_Acceleration{ 360.0f },

	m_MaxHealth{ 8 },
	m_Health{ 8 },
	m_Score{ startingScore }
{
	m_LocalCollisionBox.width = 15.0f;
	m_LocalCollisionBox.height = 26.0f;

	HurtBox::AddLocalHurtBox(15.0f, 26.0f);
	HurtBox::AddGroupNumber({ 1, 5 });

	HitBox::AddLocalHitBox();
	HitBox::AddGroupNumber(0);
	HitBox::SetActive(false);
}

ShovelKnight::ShovelKnight(float bottomLeftX, float bottomLeftY, int startingHealth, int startingScore) :
	ShovelKnight(Point2f(bottomLeftX, bottomLeftY), startingHealth, startingScore)
{
}
#pragma endregion Constructors/Destructor



#pragma region PublicMethods
void ShovelKnight::Reset(const Point2f& bottomLeft, int startingScore)
{
	m_RootCenter = Point2f(bottomLeft.x + 7.5f, bottomLeft.y + 13.0f);
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;

	m_IsFlipped = false;

	m_AccumulatedIdleTime = 0.0f;

	m_InteractState = InteractState::None;

	m_SwingingState = SwingingState::None;

	m_CombatState = CombatState::None;
	m_AccumulatedHurtSeconds = 0.0f;

	m_JumpChargeState = JumpChargeState::ChargeCooldown;
	m_AccumulatedJumpChargeSeconds = 0.0f;

	m_VerticalState = VerticalState::Standing;
	m_AccumulatedAirSeconds = 0.0f;

	m_HorizontalState = HorizontalState::Standing;

	m_Health = m_MaxHealth;

	m_Score = startingScore;

	m_LocalCollisionBox.width = 15.0f;
	m_LocalCollisionBox.height = 26.0f;

	HitBox::SetActive(false);

	SpriteAnimator::SetFrameSeconds(0.09f);

	SpriteAnimator::SetCurrentRowIndex(1, 1);
}

void ShovelKnight::Reset(float bottomLeftX, float bottomLeftY, int startingScore)
{
	Reset(Point2f(bottomLeftX, bottomLeftY), startingScore);
}
#pragma endregion PublicMethods



#pragma region Components
void ShovelKnight::Update(float elapsedSeconds)
{
	if (m_Health)
	{
		HandleInteractState(elapsedSeconds);
		HandleSwingState(elapsedSeconds);
		HandleCombatState(elapsedSeconds);
		HandleJumpChargeState(elapsedSeconds);

		if (m_CombatState != CombatState::Hurt && m_InteractState == InteractState::None)
		{
			HandleVerticalState(elapsedSeconds);
			HandleHorizontalState(elapsedSeconds);
		}
	}

	HandleSprite(elapsedSeconds);
}

void ShovelKnight::OnCollision(const utils::HitInfo& hitInfo)
{
	if (hitInfo.normal == VERTICALNORMAL)
	{
		if (!InputManager::GetState(SDLK_SPACE) && m_JumpChargeState == JumpChargeState::ChargeCooldown)
		{
			SoundManager::PlayEffect("Resources/Audio/PlayerLand.wav", false);
			m_JumpChargeState = JumpChargeState::None;
		}

		if (m_CombatState == CombatState::Hurt)
		{
			m_Velocity.x = 0;
		}

		if (m_InteractState == InteractState::Climbing)
		{
			m_InteractState = InteractState::None;
			Rigidbody::SetGravityMultiplier(1.0f);
		}

		if (m_CombatState == CombatState::Hurt && !m_Health)
		{
			m_CombatState = CombatState::Dead;
			SpriteAnimator::SetFrameSeconds(0.4f);
		}

		m_VerticalState = VerticalState::Standing;
	}
	else if (hitInfo.normal == -VERTICALNORMAL)
	{
		if (m_JumpChargeState == JumpChargeState::Charging)
		{
			m_JumpChargeState = JumpChargeState::ChargeCooldown;
		}
	}
}

void ShovelKnight::OnHit(const Vector2f& hitNormals, const Vector2f& knockBackVelocity, int localHitBoxIndex)
{
	if (m_Health)
	{
		if (hitNormals.y && knockBackVelocity.y)
		{
			m_Velocity.y = knockBackVelocity.y;

			const Point2f fxPosition{ m_RootCenter.x, m_RootCenter.y - 16.0f };
			GameObject::AddGameObject(new FX(fxPosition, "Resources/FX/DownThrustSpark.png", 4, 12));
		}
	}
}

void ShovelKnight::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (m_Health)
	{
		m_Health = m_Health - damage >= 0 ? m_Health - damage : 0;

		m_Velocity.x = hurtNormals.x * m_MaxVelocity.x;
		m_Velocity.y = m_JumpVelocity;

		m_AccumulatedHurtSeconds = 0;
		HitBox::SetActive(false);
		m_CombatState = CombatState::Hurt;

		if (m_Health)
		{
			SoundManager::PlayEffect("Resources/Audio/PlayerDamage.wav", false);
			SimpleSprite::Blink(25, 2);
		}
		else
		{
			SoundManager::PlayEffect("Resources/Audio/PlayerDie.wav", false);

			const int totalToDrop{ m_Score / 4 };
			if (totalToDrop > 0)
			{
				if (totalToDrop <= 50)
				{
					GameObject::AddGameObject(new Pickupable{ m_RootCenter, totalToDrop });
				}
				else if (totalToDrop <= 100)
				{
					GameObject::AddGameObject(new Pickupable{ m_RootCenter, totalToDrop / 2 });
					GameObject::AddGameObject(new Pickupable{ m_RootCenter, totalToDrop / 2 });
				}
				else
				{
					GameObject::AddGameObject(new Pickupable{ m_RootCenter, totalToDrop / 3 });
					GameObject::AddGameObject(new Pickupable{ m_RootCenter, totalToDrop / 3 });
					GameObject::AddGameObject(new Pickupable{ m_RootCenter, totalToDrop / 3 });
				}
			}

			m_Score = int(m_Score * 0.75f);
		}
	}
}

void ShovelKnight::OnPickup(int value, bool heals)
{
	if (m_Health)
	{
		switch (heals)
		{
		case true:
			m_Health = m_Health + value <= m_MaxHealth ? m_Health + value : m_MaxHealth;
			break;

		case false:
			m_Score += value;
			break;
		}
	}
}

void ShovelKnight::OnInteractOverlap(const Rectf& interactingArea)
{
	if (m_Health)
	{
		if (m_InteractState == InteractState::None)
		{
			if  (
				((InputManager::GetState(SDLK_w) && (m_VerticalState != VerticalState::Standing && m_VerticalState != VerticalState::Crouching))
				||
				(InputManager::GetState(SDLK_w) && m_VerticalState == VerticalState::Standing))
				&&
				m_RootCenter.y < interactingArea.bottom + interactingArea.height
				)
			{
				m_InteractState = InteractState::Climbing;
				m_RootCenter.x = interactingArea.left + interactingArea.width / 2;

				Rigidbody::SetGravityMultiplier(0.0f);
				m_Velocity.y = 0.0f;
				m_Velocity.x = 0.0f;

				m_JumpChargeState = JumpChargeState::ChargeCooldown;
			}
		}
	}
}

void ShovelKnight::OnInteractEndOverlap()
{
	if (m_Health)
	{
		m_InteractState = InteractState::None;
		Rigidbody::SetGravityMultiplier(1.0f);
		SpriteAnimator::SetFrameSeconds(0.09f);
	}
}

void ShovelKnight::OnColumnChange(int currentColumnIndex)
{
	if (m_CombatState != CombatState::Hurt && m_CombatState != CombatState::Dead)
	{
		switch (m_HorizontalState)
		{		
		case ShovelKnight::HorizontalState::LeftStepping:
			m_HorizontalState = HorizontalState::LeftRunning;
			break;

		case ShovelKnight::HorizontalState::RightStepping:
			m_HorizontalState = HorizontalState::RightRunning;
			break;

		case HorizontalState::LeftBreaking:
			if (InputManager::GetState(SDLK_a))
			{
				m_Velocity.x = -m_MaxVelocity.x;
				m_HorizontalState = HorizontalState::LeftRunning;
			}
			break;

		case HorizontalState::RightBreaking:
			if (InputManager::GetState(SDLK_d))
			{
				m_Velocity.x = m_MaxVelocity.x;
				m_HorizontalState = HorizontalState::RightRunning;
			}
			break;
		}

		if (m_CombatState == CombatState::Swinging)
		{
			switch (currentColumnIndex)
			{
			case 0:
				HitBox::SetActive(false);
				m_CombatState = CombatState::None;
				break;
				
			case 1:
				HitBox::SetActive(true);
				break;
				
			case 2:
				HitBox::SetActive(false);
				break;

			}
		}
	}
	else if (m_CombatState == CombatState::Dead && currentColumnIndex == 2)
	{
		SpriteAnimator::SetFrameSeconds(INFINITY);
	}
}
#pragma endregion Components



#pragma region PrivateMethods
void ShovelKnight::HandleInteractState(float elapsedSeconds)
{
	switch (m_InteractState)
	{
	case ShovelKnight::InteractState::None:

		break;

	case ShovelKnight::InteractState::Climbing:
		if (m_CombatState == CombatState::Thrusting)
		{
			m_CombatState = CombatState::None;
			HitBox::SetActive(false);
		}

		if (m_CombatState != CombatState::Swinging)
		{
			if (InputManager::GetState(SDLK_w))
			{
				SpriteAnimator::SetFrameSeconds(0.2f);
				m_Velocity.y = 75.0f;
			}
			else if (InputManager::GetState(SDLK_s))
			{
				SpriteAnimator::SetFrameSeconds(0.2f);
				m_Velocity.y = -75.0f;
			}
			else
			{
				SpriteAnimator::SetFrameSeconds(INFINITY);
				m_Velocity.y = 0.0f;
			}
		}
		else
		{
			m_Velocity.y = 0.0f;
		}

		if (m_CombatState != CombatState::Swinging)
		{
			if (InputManager::GetState(SDLK_a))
			{
				SimpleSprite::m_IsFlipped = true;
			}
			else if (InputManager::GetState(SDLK_d))
			{
				SimpleSprite::m_IsFlipped = false;
			}
		}

		if (InputManager::GetState(SDLK_SPACE))
		{
			m_CombatState = CombatState::None;
			m_InteractState = InteractState::None;
			Rigidbody::SetGravityMultiplier(1.0f);
			m_Velocity.y = 0.0f;

			SpriteAnimator::SetFrameSeconds(0.09f);
		}
		break;

	case ShovelKnight::InteractState::Looting:

		break;
	}
}

void ShovelKnight::HandleSwingState(float elapsedSeconds)
{
	switch (m_SwingingState)
	{
	case ShovelKnight::SwingingState::None:
		if (m_CombatState == CombatState::Swinging)
		{
			SoundManager::PlayEffect("Resources/Audio/PlayerShovel.wav", false);
			m_SwingingState = SwingingState::SwingingCooldown;
		}
		break;

	case ShovelKnight::SwingingState::SwingingCooldown:
		if (m_CombatState != CombatState::Swinging && !InputManager::GetState(SDLK_l))
		{
			m_SwingingState = SwingingState::None;
		}
		break;
	}
}

void ShovelKnight::HandleCombatState(float elapsedSeconds)
{
	switch (m_CombatState)
	{
	case ShovelKnight::CombatState::None:
		if (InputManager::GetState(SDLK_l) && m_SwingingState == SwingingState::None && m_InteractState != InteractState::Looting)
		{
			SpriteAnimator::SetFrameSeconds(0.09f);
			m_CombatState = CombatState::Swinging;
		}
		else if (InputManager::GetState(SDLK_s) && m_VerticalState == VerticalState::Jumping && m_AccumulatedAirSeconds >= m_MinAirSeconds && m_InteractState == InteractState::None)
		{
			HitBox::SetHitDirection(0, -1);
			HitBox::SetLocalHitBox(0.0f, -14.0f, 13.0f, 3.0f);
			HitBox::SetActive(true);
			m_CombatState = CombatState::Thrusting;
		}
		break;

	case ShovelKnight::CombatState::Swinging:
		if (SimpleSprite::m_IsFlipped)
		{
			HitBox::SetHitDirection(-1, 0);
			HitBox::SetLocalHitBox(-17.0f, 0.0f, 34.0f, 7.0f);
		}
		else
		{
			HitBox::SetHitDirection(1, 0);
			HitBox::SetLocalHitBox(17.0f, 0.0f, 34.0f, 7.0f);
		}
		break;

	case ShovelKnight::CombatState::Thrusting:
		if (m_VerticalState == VerticalState::Standing)
		{
			HitBox::SetActive(false);
			m_CombatState = CombatState::None;
		}

		if (InputManager::GetState(SDLK_l) && m_SwingingState == SwingingState::None)
		{
			HitBox::SetActive(false);
			m_CombatState = CombatState::Swinging;
		}
		break;

	case ShovelKnight::CombatState::Hurt:
		m_AccumulatedHurtSeconds += elapsedSeconds;

		if (m_AccumulatedHurtSeconds >= m_MaxHurtSeconds)
		{
			m_AccumulatedHurtSeconds = 0;
			m_CombatState = CombatState::None;
		}
		break;
	}
}

void ShovelKnight::HandleJumpChargeState(float elapsedSeconds)
{
	switch (m_JumpChargeState)
	{
	case ShovelKnight::JumpChargeState::None:
		if (InputManager::GetState(SDLK_SPACE))
		{
			SoundManager::PlayEffect("Resources/Audio/PlayerJump.wav", false);
			m_AccumulatedJumpChargeSeconds = 0;
			m_Velocity.y = m_JumpVelocity;
			m_AccumulatedJumpChargeSeconds += elapsedSeconds;
			m_JumpChargeState = JumpChargeState::Charging;

			if (m_CombatState == CombatState::Swinging && m_InteractState != InteractState::Climbing)
			{
				HitBox::SetActive(false);
				m_CombatState = CombatState::None;
			}
		}
		else if (m_Velocity.y < 0)
		{
			m_JumpChargeState = JumpChargeState::ChargeCooldown;
		}
		break;

	case ShovelKnight::JumpChargeState::Charging:
		m_Velocity.y = m_JumpVelocity;
		m_AccumulatedJumpChargeSeconds += elapsedSeconds;

		if (!InputManager::GetState(SDLK_SPACE) || m_AccumulatedJumpChargeSeconds >= m_MaxJumpChargeSeconds || m_CombatState == CombatState::Hurt)
		{
			m_AccumulatedJumpChargeSeconds = 0;
			m_JumpChargeState = JumpChargeState::ChargeCooldown;
		}
		break;
	}
}

void ShovelKnight::HandleVerticalState(float elapsedSeconds)
{
	switch (m_VerticalState)
	{
	case ShovelKnight::VerticalState::Standing:
		m_AccumulatedAirSeconds = 0;

		if (InputManager::GetState(SDLK_s))
		{
			m_VerticalState = VerticalState::Crouching;
		}

		if (m_Velocity.y)
		{
			m_VerticalState = VerticalState::Jumping;
		}
		break;

	case ShovelKnight::VerticalState::Jumping:
		m_AccumulatedAirSeconds += elapsedSeconds;

		if (InputManager::GetState(SDLK_a))
		{
			m_Velocity.x = -m_MaxVelocity.x;
		}
		else if (InputManager::GetState(SDLK_d))
		{
			m_Velocity.x = m_MaxVelocity.x;
		}
		else if (!InputManager::GetState(SDLK_a) && !InputManager::GetState(SDLK_d))
		{
			m_Velocity.x = 0;
		}
		break;

	case ShovelKnight::VerticalState::Crouching:
		if (!InputManager::GetState(SDLK_s) && !m_Velocity.y)
		{
			m_VerticalState = VerticalState::Standing;
		}

		if (m_Velocity.y)
		{
			m_VerticalState = VerticalState::Jumping;
		}
		break;
	}
}

void ShovelKnight::HandleHorizontalState(float elapsedSeconds)
{
	switch (m_HorizontalState)
	{
	case ShovelKnight::HorizontalState::Standing:
		if (InputManager::GetState(SDLK_a) && m_CombatState != CombatState::Swinging)
		{
			m_Velocity.x -= m_Acceleration * elapsedSeconds;
			m_HorizontalState = HorizontalState::LeftStepping;
		}
		else if (InputManager::GetState(SDLK_d) && m_CombatState != CombatState::Swinging)
		{
			m_Velocity.x += m_Acceleration * elapsedSeconds;
			m_HorizontalState = HorizontalState::RightStepping;
		}
		break;

	case ShovelKnight::HorizontalState::LeftStepping:
	case ShovelKnight::HorizontalState::LeftRunning:
		if (InputManager::GetState(SDLK_a) && m_CombatState != CombatState::Swinging)
		{
			m_Velocity.x -= m_Acceleration * elapsedSeconds;
		}
		else
		{
			m_Velocity.x += 2 * m_Acceleration * elapsedSeconds;

			if (InputManager::GetState(SDLK_d) && m_CombatState != CombatState::Swinging)
			{
				m_HorizontalState = HorizontalState::RightBreaking;
			}

			if (m_Velocity.x >= 0)
			{
				m_Velocity.x = 0;
				m_HorizontalState = HorizontalState::Standing;
			}
		}
		break;

	case ShovelKnight::HorizontalState::LeftBreaking:
		m_Velocity.x -= 2 * m_Acceleration * elapsedSeconds;

		if (m_Velocity.x <= 0)
		{
			m_Velocity.x = 0;

			if (!InputManager::GetState(SDLK_a))
			{
				m_HorizontalState = HorizontalState::Standing;
			}
		}
		break;

	case ShovelKnight::HorizontalState::RightStepping:
	case ShovelKnight::HorizontalState::RightRunning:
		if (InputManager::GetState(SDLK_d) && m_CombatState != CombatState::Swinging)
		{
			m_Velocity.x += m_Acceleration * elapsedSeconds;
		}
		else
		{
			m_Velocity.x -= 2 * m_Acceleration * elapsedSeconds;

			if (InputManager::GetState(SDLK_a) && m_CombatState != CombatState::Swinging)
			{
				m_HorizontalState = HorizontalState::LeftBreaking;
			}

			if (m_Velocity.x <= 0)
			{
				m_Velocity.x = 0;
				m_HorizontalState = HorizontalState::Standing;
			}
		}
		break;

	case ShovelKnight::HorizontalState::RightBreaking:
		m_Velocity.x += 2 * m_Acceleration * elapsedSeconds;

		if (m_Velocity.x >= 0)
		{
			m_Velocity.x = 0;

			if (!InputManager::GetState(SDLK_d))
			{
				m_HorizontalState = HorizontalState::Standing;
			}
		}
		break;
	}
}

void ShovelKnight::HandleSprite(float elapsedSeconds)
{
	if (m_CombatState != CombatState::Swinging)
	{
		if (m_Velocity.x < 0)
		{
			SimpleSprite::m_IsFlipped = true;
		}
		else if (m_Velocity.x > 0)
		{
			SimpleSprite::m_IsFlipped = false;
		}
	}

	switch (m_CombatState)
	{
	case ShovelKnight::CombatState::Dead:
		SpriteAnimator::SetCurrentRowIndex(14, 3);
		break;

	case ShovelKnight::CombatState::Hurt:
		SpriteAnimator::SetCurrentRowIndex(13, 1);
		break;

	case ShovelKnight::CombatState::Thrusting:
		SpriteAnimator::SetCurrentRowIndex(10, 1);
		break;

	case ShovelKnight::CombatState::Swinging:
		if (m_InteractState == InteractState::Climbing)
		{
			SpriteAnimator::SetCurrentRowIndex(12, 4, true);
		}
		else
		{
			SpriteAnimator::SetCurrentRowIndex(9, 4, true);
		}
		break;

	case ShovelKnight::CombatState::None:
		if (m_InteractState == InteractState::Climbing)
		{
			SpriteAnimator::SetCurrentRowIndex(11, 2);
		}
		else
		{
			switch (m_VerticalState)
			{

			case ShovelKnight::VerticalState::Jumping:
				if (m_Velocity.y > 0)
				{
					SpriteAnimator::SetCurrentRowIndex(7, 1);
				}
				else
				{
					SpriteAnimator::SetCurrentRowIndex(8, 1);
				}
				break;

			case ShovelKnight::VerticalState::Standing:
			case ShovelKnight::VerticalState::Crouching:
				switch (m_HorizontalState)
				{
				case ShovelKnight::HorizontalState::LeftStepping:
				case ShovelKnight::HorizontalState::RightStepping:
					SpriteAnimator::SetCurrentRowIndex(4, 1);
					break;

				case ShovelKnight::HorizontalState::LeftRunning:
				case ShovelKnight::HorizontalState::RightRunning:
					SpriteAnimator::SetCurrentRowIndex(5, 6);
					break;

				case ShovelKnight::HorizontalState::LeftBreaking:
				case ShovelKnight::HorizontalState::RightBreaking:
					SpriteAnimator::SetCurrentRowIndex(6, 1);
					break;

				case ShovelKnight::HorizontalState::Standing:
					if (m_VerticalState == VerticalState::Standing)
					{
						m_AccumulatedIdleTime += elapsedSeconds;

						if (m_AccumulatedIdleTime >= m_MaxIdleTime)
						{
							m_AccumulatedIdleTime -= m_MaxIdleTime;

							SpriteAnimator::SetCurrentRowIndex(2, 3, true);
						}

						SpriteAnimator::SetCurrentRowIndex(1, 1);
					}
					else
					{
						SpriteAnimator::SetCurrentRowIndex(3, 1);
					}
					break;
				}
				break;

			}
			break;
		}
	}
}
#pragma endregion PrivateMethods