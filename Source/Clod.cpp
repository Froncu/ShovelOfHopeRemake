#include "pch.h"
#include "Clod.h"

#include "Particle.h"
#include "Camera.h"

#include "myutils.h"

#include "SoundManager.h"

#pragma region Constructors/Destructor
Clod::Clod(const Point2f& center, const Vector2f& initialVelocity) :
	GameObject(center.x + 8.0f, center.y + 8.0f, true),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter),
	HurtBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/Clod.png", 7)
{
	DynamicCollider::m_LocalCollisionBox.width = 16.0f;
	DynamicCollider::m_LocalCollisionBox.height = 16.0f;

	Rigidbody::m_Velocity = initialVelocity;

	HurtBox::AddLocalHurtBox(16.0f, 16.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 240.0f);
	HurtBox::m_IsActive = false;
}

Clod::Clod(float centerX, float centerY, const Vector2f& initialVelocity) :
	Clod(Point2f(centerX, centerY), initialVelocity)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Clod::Update(float elapsedSeconds)
{
	if (m_Velocity.y < 0) HurtBox::m_IsActive = true;
}

void Clod::OnCollision(const utils::HitInfo& hitInfo)
{
	if (hitInfo.normal == VERTICALNORMAL)
	{
		if (m_Velocity.x != 0.0f) SoundManager::PlayEffect("Resources/Audio/DigClodLand.wav", false);

		m_Velocity.x = 0.0f;
	}
}

void Clod::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	SoundManager::PlayEffect("Resources/Audio/DigClodBreak.wav", false);
	GameObject::Delete();

	DropRandomly(Pickupable::Type::GoldGem, 2);
	DropRandomly(Pickupable::Type::BlueGem, 1);

	const int amountOfParticles{ 4 };
	for (int droppedAmount{}; droppedAmount < amountOfParticles; ++droppedAmount)
	{
		const Vector2f minimalRandomInitialVelocity{ -100.0f + droppedAmount * 50.0f, 320.0f }, maximalRandomInitialVelocity{ -50.0f + droppedAmount * 50.0f, 360.0f };
		const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };

		const std::string particlePath{ "Resources/Particles/DirtParticle" + std::to_string(myutils::GetRandom(1)) + ".png" };
		GameObject::AddGameObject(new Particle{ m_RootCenter, particlePath, hurtNormals.x * randomInitialVelocity.x, randomInitialVelocity.y });
	}
}
#pragma endregion Components



#pragma region PrivateMethods
void Clod::DropRandomly(Pickupable::Type type, int amount)
{
	for (int droppedAmount{}; droppedAmount < amount; ++droppedAmount)
	{
		const Vector2f minimalRandomInitialVelocity{ -100.0f, 240.0f }, maximalRandomInitialVelocity{ 100.0f, 300.0f };
		const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };
		GameObject::AddGameObject(new Pickupable{ m_RootCenter, type, randomInitialVelocity });
	}
}
#pragma endregion PrivateMethods