#include "pch.h"
#include "Beeto.h"

#include "FX.h"
#include "Pickupable.h"

#include "SoundManager.h"

#include "myutils.h"

#pragma region Constructors/Destructor
Beeto::Beeto(const Point2f& bottomLeft, bool isFacingLeft, float localLeftBorder, float localRightBorder) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 8.0f, true),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter, 0.25f, Vector2f(36.0f, 100.0f)),
	HurtBox(m_RootCenter),
	HitBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0, -1, "Resources/Entities/Beeto.png", 8),
	SpriteAnimator(4, 2, 0.25f, 0, 4),

	m_LeftBorder{ localLeftBorder ? bottomLeft.x + localLeftBorder : 0.0f }, m_RightBorder{ localRightBorder ? bottomLeft.x + localRightBorder : 0.0f },
	m_HasBeenHurt{}, m_IsFacingLeft{ isFacingLeft }
{
	m_LocalCollisionBox.width = 26.0f;
	m_LocalCollisionBox.height = 16.0f;

	m_Velocity.x = m_IsFacingLeft ? -m_MaxVelocity.x / 2 : m_MaxVelocity.x / 2;

	HurtBox::AddLocalHurtBox(26.0f, 16.0f);
	HurtBox::AddGroupNumber({ 0, 5 });
	HurtBox::SetKnockBackVelocity(0.0f, 360.0f);

	HitBox::AddLocalHitBox(22.0f, 12.0f);
	HitBox::AddGroupNumber(1);
}

Beeto::Beeto(float bottomLeftX, float bottomLeftY, bool isFacingLeft, float localLeftBorder, float localRightBorder) :
	Beeto(Point2f(bottomLeftX, bottomLeftY), isFacingLeft, localLeftBorder, localRightBorder)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Beeto::Update(float elapsedSeconds)
{
	if (!m_HasBeenHurt)
	{
		if (m_LeftBorder && m_RootCenter.x - 13.0f <= m_LeftBorder)
		{
			m_RootCenter.x = m_LeftBorder + 13.0f;
			m_Velocity.x = m_MaxVelocity.x / 2.0f;
		}
		else if (m_RightBorder && m_RootCenter.x + 13.0f >= m_RightBorder)
		{
			m_RootCenter.x = m_RightBorder - 13.0f;
			m_Velocity.x = -m_MaxVelocity.x / 2.0f;
		}
	}

	if (m_Velocity.x < 0)
	{
		SimpleSprite::m_IsFlipped = true;
	}
	else if (m_Velocity.x > 0)
	{
		SimpleSprite::m_IsFlipped = false;
	}
}

void Beeto::OnCollision(const utils::HitInfo& hitInfo)
{
	if (hitInfo.normal == HORIZONTALNORMAL)
	{
		m_Velocity.x = m_MaxVelocity.x / 2.0f;
	}
	else if (hitInfo.normal == -HORIZONTALNORMAL)
	{
		m_Velocity.x = -m_MaxVelocity.x / 2.0f;
	}

	if (hitInfo.normal == VERTICALNORMAL)
	{
		if (m_HasBeenHurt)
		{
			SoundManager::PlayEffect("Resources/Audio/Kill.wav", false);
			GameObject::Delete();
			GameObject::AddGameObject(new FX{ m_RootCenter, "Resources/FX/Poof.png", 5, 8, 0.1f });

			const float horizontalDirection{ m_Velocity.x / abs(m_Velocity.x) };
			const Vector2f minimalRandomInitialVelocity{ 60.0f, 200.0f }, maximalRandomInitialVelocity{ 80.0f, 300.0f };
			const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };
			GameObject::AddGameObject(new Pickupable(m_RootCenter, Pickupable::Type::BlueGem, horizontalDirection * randomInitialVelocity.x, randomInitialVelocity.y));
		}
	}
}

void Beeto::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (!hurtNormals.y)
	{
		SoundManager::PlayEffect("Resources/Audio/BeetleFlip.wav", false);

		m_Velocity.x = hurtNormals.x * abs(m_MaxVelocity.x);
		m_Velocity.y = m_MaxVelocity.y;

		m_HasBeenHurt = true;

		SpriteAnimator::SetCurrentRowIndex(1, 2);
		HitBox::SetActive(false);
	}
	else
	{
		SoundManager::PlayEffect("Resources/Audio/Kill.wav", false);

		GameObject::Delete();
		GameObject::AddGameObject(new FX{ m_RootCenter, "Resources/FX/Poof.png", 5, 8, 0.1f });

		const Vector2f minimalRandomInitialVelocity{ 60.0f, 200.0f }, maximalRandomInitialVelocity{ 80.0f, 300.0f };
		const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };
		GameObject::AddGameObject(new Pickupable(m_RootCenter, Pickupable::Type::BlueGem, hurtNormals.x * randomInitialVelocity.x, randomInitialVelocity.y));
	}
}
#pragma endregion Components