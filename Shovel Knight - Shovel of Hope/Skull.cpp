#include "pch.h"
#include "Skull.h"

#include "FX.h"
#include "Particle.h"
#include "SoundManager.h"

#include "myutils.h"

#pragma region Constructors/destructor
Skull::Skull(const Point2f& bottomLeft, const Vector2f& initialVelocity) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 5.5f, true),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter, 1.0f, Vector2f(100.0f, 200.0f)),
	HurtBox(m_RootCenter),
	HitBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Environment/Skull.png", 10),

	m_HasBeenHit{}
{
	m_LocalCollisionBox.width = 12.0f;
	m_LocalCollisionBox.height = 11.0f;

	HurtBox::AddLocalHurtBox(0.0f, 0.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 240.0f);

	HitBox::AddLocalHitBox(12.0f, 11.0f);
	HitBox::AddGroupNumber(2);

	HitBox::SetActive(false);

	m_Velocity = initialVelocity;
}

Skull::Skull(float positionLeft, float positionBottom, const Vector2f& initialVelocity) :
	Skull(Point2f(positionLeft, positionBottom), initialVelocity)
{
}
#pragma endregion Constructors/destructor



#pragma region Components
void Skull::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (hurtNormals.y || damage >= 10)
	{
		SoundManager::PlayEffect("Audio/SkullScatter.wav", false);
		GameObject::Delete();
		GameObject::AddGameObject(new Particle{ m_RootCenter, "Particles/SkullParticle0.png", GetRandomInitialDropVelocity() });
		GameObject::AddGameObject(new Particle{ m_RootCenter, "Particles/SkullParticle1.png", GetRandomInitialDropVelocity(true) });
		GameObject::AddGameObject(new Particle{ m_RootCenter, "Particles/SkullParticle2.png", GetRandomInitialDropVelocity() });
	}
	else
	{
		SoundManager::PlayEffect("Audio/SkullShovel.wav", false);
		m_HasBeenHit = true;
		HitBox::SetActive(m_HasBeenHit);

		m_Velocity.x = hurtNormals.x * m_MaxVelocity.x;
		m_Velocity.y = m_MaxVelocity.y;

		GameObject::AddGameObject(new FX{ m_RootCenter.x + (hurtNormals.x == 1 ? 11.5f : -11.5f), m_RootCenter.y + 10.5f, "FX/FlipSpak.png", 4, 12, 0.05f, hurtNormals.x == 1 ? false : true });
	}

	Rigidbody::SetGravityMultiplier(0.5f);
}

void Skull::OnCollision(const utils::HitInfo& hitInfo)
{
	if (hitInfo.normal == VERTICALNORMAL)
	{
		if (m_HasBeenHit)
		{
			SoundManager::PlayEffect("Audio/SkullScatter.wav", false);
			GameObject::Delete();
			GameObject::AddGameObject(new Particle{ m_RootCenter, "Particles/SkullParticle0.png", GetRandomInitialDropVelocity() });
			GameObject::AddGameObject(new Particle{ m_RootCenter, "Particles/SkullParticle1.png", GetRandomInitialDropVelocity(true) });
			GameObject::AddGameObject(new Particle{ m_RootCenter, "Particles/SkullParticle2.png", GetRandomInitialDropVelocity() });
		}

		m_Velocity.y = 0.0f;
		m_Velocity.x = 0.0f;
		HurtBox::SetLocalHurtBox(0.0f, 0.0f, 11.0f, 12.0f);
	}
	else if (hitInfo.normal == HORIZONTALNORMAL)
	{
		SoundManager::PlayEffect("Audio/SkullBounce.wav", false);

		m_Velocity.x = hitInfo.normal.x * m_MaxVelocity.x;

		if (m_HasBeenHit && m_Velocity.y < 0) m_Velocity.y = m_MaxVelocity.y;
	}
	else if (hitInfo.normal == -HORIZONTALNORMAL)
	{
		SoundManager::PlayEffect("Audio/SkullBounce.wav", false);

		m_Velocity.x = hitInfo.normal.x * m_MaxVelocity.x;

		if (m_HasBeenHit && m_Velocity.y < 0) m_Velocity.y = m_MaxVelocity.y;
	}

	if (m_HasBeenHit) Rigidbody::SetGravityMultiplier(0.5f);
}

void Skull::OnHit(const Vector2f& hitNormals, const Vector2f& knockbackVelocity, int localHitBoxIndex)
{
	SoundManager::PlayEffect("Audio/SkullBounce.wav", false);

	m_Velocity.x = hitNormals.x * m_MaxVelocity.x;
	m_Velocity.y = m_MaxVelocity.y;
}
#pragma endregion Components



#pragma region PrivateMethods
Vector2f Skull::GetRandomInitialDropVelocity(bool dropLeft) const
{
	const Vector2f minimalRandomInitialVelocity{ -100.0f, 120.0f }, maximalRandomInitialVelocity{ 100.0f, 240.0f };
	Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };

	if (dropLeft)
	{
		randomInitialVelocity.x = -abs(randomInitialVelocity.x);
	}
	else
	{
		randomInitialVelocity.x = abs(randomInitialVelocity.x);
	}

	return randomInitialVelocity;
}
#pragma endregion PrivateMethods