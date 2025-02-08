#include "pch.h"
#include "DigPile.h"

#include "Particle.h"
#include "Camera.h"

#include "SoundManager.h"

#include "myutils.h"

#pragma region Constructors/Destructor
DigPile::DigPile(const Point2f& bottomLeft) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 7.5f, true),
	HurtBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/DigPile.png", 7),
	SpriteAnimator(5, 10, 0.1f, 0, 1),

	m_MaxIdleSeconds{ 4.0f },
	m_AccumulatedIdleSeconds{},

	m_CurrentRowIndex{}, m_AmountOfGreyGems{ 10 }, m_ValueLeftToDropRandomly{ 150 }
{
	HurtBox::AddLocalHurtBox(33.0f, 15.0f);
	HurtBox::AddGroupNumber(0);
}

DigPile::DigPile(float positionLeft, float positionBottom) :
	DigPile(Point2f(positionLeft, positionBottom))
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void DigPile::Update(float elapsedSeconds)
{
	m_AccumulatedIdleSeconds += elapsedSeconds;

	if (m_AccumulatedIdleSeconds >= m_MaxIdleSeconds)
	{
		m_AccumulatedIdleSeconds -= m_MaxIdleSeconds;

		SpriteAnimator::SetCurrentRowIndex(m_CurrentRowIndex + 1, 5, true);
	}
}

void DigPile::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (!hurtNormals.y)
	{
		SoundManager::PlayEffect("Resources/Audio/DigPile.wav", false);

		m_CurrentRowIndex += 2;
		SpriteAnimator::SetCurrentRowIndex(m_CurrentRowIndex, 1);

		//	Amount to drop
		int grey{}, blue{}, green{}, gold{}, red{};

		if (m_CurrentRowIndex <= 8)
		{
			if (m_AmountOfGreyGems >= 4) grey = myutils::GetRandom(4);
			else grey = m_AmountOfGreyGems;
			m_AmountOfGreyGems -= grey;

			DropRandomly(Pickupable::Type::GreyGem, grey, hurtNormals);

			if (myutils::GetRandom(1))
			{
				DropRandomly(Pickupable::Type::BlueGem, 1, hurtNormals);
			}
			else
			{
				DropRandomly(Pickupable::Type::GreenGem, 1, hurtNormals);
			}
		}
		else
		{
			while (m_ValueLeftToDropRandomly)
			{
				DropRandomlyToFit(Pickupable::Type::RedGem, hurtNormals);
				DropRandomlyToFit(Pickupable::Type::GoldGem, hurtNormals);
				DropRandomlyToFit(Pickupable::Type::GreenGem, hurtNormals);
				DropRandomlyToFit(Pickupable::Type::BlueGem, hurtNormals);
				DropRandomlyToFit(Pickupable::Type::GreyGem, hurtNormals);
			}

			GameObject::Delete();
		}

		const int amountOfParticles{ 4 };
		for (int droppedAmount{}; droppedAmount < amountOfParticles; ++droppedAmount)
		{
			const Vector2f minimalRandomInitialVelocity{ 50.0f + droppedAmount * 25.0f, 320.0f }, maximalRandomInitialVelocity{ 75.0f + droppedAmount * 25.0f, 360.0f };
			const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };

			const std::string particlePath{ "Resources/Particles/DirtParticle" + std::to_string(myutils::GetRandom(1)) + ".png" };
			GameObject::AddGameObject(new Particle{ m_RootCenter, particlePath, hurtNormals.x * randomInitialVelocity.x, randomInitialVelocity.y });
		}
	}
}
#pragma endregion Components



#pragma region PrivateMethods
void DigPile::DropRandomly(Pickupable::Type type, int amount, const Vector2f& hurtNormals)
{
	for (int droppedAmount{}; droppedAmount < amount; ++droppedAmount)
	{
		const Vector2f minimalRandomInitialVelocity{ 20.0f, 240.0f }, maximalRandomInitialVelocity{ 100.0f, 360.0f };
		const Vector2f randomInitialVelocity{ myutils::GetRandom(maximalRandomInitialVelocity, minimalRandomInitialVelocity) };
		GameObject::AddGameObject(new Pickupable{ m_RootCenter, type, hurtNormals.x * randomInitialVelocity.x, randomInitialVelocity.y });

		m_ValueLeftToDropRandomly -= int(type);
	}
}

void DigPile::DropRandomlyToFit(Pickupable::Type type, const Vector2f& hurtNormals)
{
	DropRandomly(type, m_ValueLeftToDropRandomly / int(type), hurtNormals);
}
#pragma endregion PrivateMethods