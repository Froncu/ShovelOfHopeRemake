#include "pch.h"
#include "Pickupable.h"

#include "FX.h"
#include "SoundManager.h"

#include "myutils.h"

#pragma region StaticDataMembers
std::map<Pickupable::Type, std::string> Pickupable::m_mTYPESPRITEPATH
{
	std::pair<Pickupable::Type, std::string>(Type::Empty, ""),
	std::pair<Pickupable::Type, std::string>(Type::GreyGem, "Pickupables/GreyGem.png"),
	std::pair<Pickupable::Type, std::string>(Type::BlueGem, "Pickupables/BlueGem.png"),
	std::pair<Pickupable::Type, std::string>(Type::GreenGem, "Pickupables/GreenGem.png"),
	std::pair<Pickupable::Type, std::string>(Type::GoldGem, "Pickupables/GoldGem.png"),
	std::pair<Pickupable::Type, std::string>(Type::RedGem, "Pickupables/RedGem.png"),
	std::pair<Pickupable::Type, std::string>(Type::MagentaGem, "Pickupables/MagentaGem.png"),
	std::pair<Pickupable::Type, std::string>(Type::Carrot, "Pickupables/Carrot.png"),
	std::pair<Pickupable::Type, std::string>(Type::Apple, "Pickupables/Apple.png"),
	std::pair<Pickupable::Type, std::string>(Type::Chicken, "Pickupables/Chicken.png")
};
#pragma endregion StaticDataMembers



#pragma region Constructors/Destructor
Pickupable::Pickupable(const Point2f& center, Type type, const Vector2f& initialVelocity) :
	GameObject(center, !(initialVelocity.x || initialVelocity.y)),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, m_mTYPESPRITEPATH.at(type), 9),
	SpriteAnimator(1, 1),

	m_LocalPickupArea{},

	m_Despawns{ initialVelocity != Vector2f(0, 0) }, m_CanBePickedUp{},

	m_Value{},
	m_Heals{},

	m_AmountOfFX{},

	m_MaxPickupableSeconds{ 8.0f },
	m_AccumulatedSeconds{},

	m_WasAudioPlayed{},

	m_DBagTarget{}
{
	SpriteAnimator::SetFrameSeconds(INFINITY);

	if (m_Despawns)
	{
		m_Velocity = initialVelocity;
	}
	else
	{
		Rigidbody::SetGravityMultiplier(0.0f);
		m_CanBePickedUp = true;
	}

	switch (type)
	{
	case Pickupable::Type::GreyGem:
		m_LocalPickupArea = Rectf(0.0f, 0.0f, 6.0f, 6.0f);
		m_Value = 1;

		m_AmountOfFX = 1;
		break;

	case Pickupable::Type::BlueGem:
		m_LocalPickupArea = Rectf(0.0f, 0.0f, 8.0f, 8.0f);
		m_Value = 5;

		m_AmountOfFX = 1;
		break;

	case Pickupable::Type::GreenGem:
		m_LocalPickupArea = Rectf(0.0f, 0.0f, 9.0f, 12.0f);
		m_Value = 10;

		m_AmountOfFX = 1;
		break;

	case Pickupable::Type::GoldGem:
		m_LocalPickupArea = Rectf(0.0f, 0.0f, 13.0f, 9.0f);
		m_Value = 20;

		m_AmountOfFX = 1;
		break;

	case Pickupable::Type::RedGem:
		m_LocalPickupArea = Rectf(0.0f, 0.0f, 16.0f, 13.0f);
		m_Value = 50;

		m_AmountOfFX = 2;
		break;

	case Pickupable::Type::MagentaGem:
		m_LocalPickupArea = Rectf(0.0f, 0.0f, 21.0f, 16.0f);
		m_Value = 200;

		m_AmountOfFX = 3;
		break;

	case Pickupable::Type::Carrot:
		m_Heals = true;

		m_LocalPickupArea = Rectf(0.0f, 0.0f, 19.0f, 6.0f);
		m_Value = 6;

		m_AmountOfFX = 1;
		break;

	case Pickupable::Type::Apple:
		m_Heals = true;

		m_LocalPickupArea = Rectf(0.0f, 0.0f, 12.0f, 11.0f);
		m_Value = 4;

		m_AmountOfFX = 1;
		break;

	case Pickupable::Type::Chicken:
		m_Heals = true;

		m_LocalPickupArea = Rectf(0.0f, 0.0f, 27.0f, 18.0f);
		m_Value = 20;

		m_AmountOfFX = 5;
		break;
	}

	m_LocalCollisionBox = m_LocalPickupArea;
}

Pickupable::Pickupable(float centerX, float centerY, Type type, const Vector2f& initialVelocity) :
	Pickupable(Point2f(centerX, centerY), type, initialVelocity)
{
}

Pickupable::Pickupable(const Point2f& center, Type type, float initialVelocityX, float initialVelocityY) :
	Pickupable(center, type, Vector2f(initialVelocityX, initialVelocityY))
{
}

Pickupable::Pickupable(float centerX, float centerY, Type type, float initialVelocityX, float initialVelocityY) :
	Pickupable(Point2f(centerX, centerY), type, Vector2f(initialVelocityX, initialVelocityY))
{
}

Pickupable::Pickupable(const Point2f& center, int value) :
	GameObject(center),
	DynamicCollider(m_RootCenter),
	Rigidbody(m_RootCenter, 0.0f),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Pickupables/DBag.png", 9),
	SpriteAnimator(3, 3, 0.1f, value <= 50 ? 1 : value <= 250 ? 2 : 0, 3),

	m_LocalPickupArea{},

	m_Despawns{}, m_CanBePickedUp{ false },

	m_Value{ value },
	m_Heals{},

	m_AmountOfFX{ 5 },

	m_MaxPickupableSeconds{},
	m_AccumulatedSeconds{},

	m_WasAudioPlayed{},

	m_DBagTarget{ m_RootCenter.x + myutils::GetRandom(48.0f, -48.0f), m_RootCenter.y + myutils::GetRandom(96.0f, 64.0f) }
{
	m_LocalPickupArea.width = 40.0f;
	m_LocalPickupArea.height = 29.0f;
}

Pickupable::Pickupable(float centerX, float centerY, int value) :
	Pickupable(Point2f(centerX, centerY), value)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Pickupable::Update(float elapsedSeconds)
{
	//	If not a dBag
	if (!m_DBagTarget.x && !m_DBagTarget.y)
	{
		if (m_Velocity.y <= 0 && m_Despawns)
		{
			m_CanBePickedUp = true;

			m_AccumulatedSeconds += elapsedSeconds;

			if (m_AccumulatedSeconds >= m_MaxPickupableSeconds)
			{
				GameObject::Delete();
			}
			else if (m_AccumulatedSeconds >= m_MaxPickupableSeconds - 2.0f)
			{
				SimpleSprite::Blink(3, 2.0f);
			}
		}
	}
	else
	{
		m_AccumulatedSeconds += elapsedSeconds;

		const float amplitude{ 16.0f }, period{ 4.0f };
		m_DBagTarget.y += (amplitude * sinf(m_AccumulatedSeconds * 2 * float(M_PI) / period)) * elapsedSeconds;

		if (m_AccumulatedSeconds >= period / 2)
		{
			m_CanBePickedUp = true;
		}

		if (m_AccumulatedSeconds >= period)
		{
			m_AccumulatedSeconds -= period;

			m_CanBePickedUp = true;
		}

		m_Velocity.y = m_DBagTarget.y - m_RootCenter.y;
		m_Velocity.x = m_DBagTarget.x - m_RootCenter.x;
	}
}

void Pickupable::OnCollision(const utils::HitInfo& hitInfo)
{
	//	If not a dBag
	if (!m_DBagTarget.x && !m_DBagTarget.y)
	{
		if (hitInfo.normal == VERTICALNORMAL)
		{
			if (!m_Heals && !m_WasAudioPlayed)
			{
				SoundManager::PlayEffect("Audio/GemDrop.wav", false);
				m_WasAudioPlayed = true;
			}

			m_Velocity.x = 0.0f;
		}
	}
}
#pragma endregion Components



#pragma region PrivateMethods
void Pickupable::OnPickup()
{	
	//	If not a dBag
	if (!m_DBagTarget.x && !m_DBagTarget.y)
	{
		if (!m_Heals)
		{
			switch (m_Value)
			{
			case 1:
				SoundManager::PlayEffect("Audio/GemGrey.wav", false);
				break;

			case 20:
				SoundManager::PlayEffect("Audio/GemGold.wav", false);
				break;

			case 50:
				SoundManager::PlayEffect("Audio/GemRed.wav", false);
				break;

			case 200:
				SoundManager::PlayEffect("Audio/GemMagenta.wav", false);
				break;

			default:
				SoundManager::PlayEffect("Audio/GemStandard.wav", false);
				break;
			}
		}
		else
		{
			SoundManager::PlayEffect("Audio/Food.wav", false);
		}

		GameObject::Delete();

		for (int index{}; index < m_AmountOfFX; ++index)
		{
			const float halfFxSize{ 4.5f };
			const Point2f randomFXPosition
			{
				myutils::GetRandom(m_RootCenter.x + m_LocalPickupArea.width / 2 + m_LocalPickupArea.left, m_RootCenter.x - m_LocalPickupArea.width / 2 - m_LocalPickupArea.left),
				myutils::GetRandom(m_RootCenter.y + m_LocalPickupArea.height / 2 + m_LocalPickupArea.bottom, m_RootCenter.y - m_LocalPickupArea.height / 2 + m_LocalPickupArea.bottom)
			};

			GameObject::AddGameObject(new FX(randomFXPosition, "FX/PickupSparkleParticle.png", 3, 12, 0.1f));
		}
	}
	else
	{
		SoundManager::PlayEffect("Audio/GemStandard.wav", false);
		GameObject::Delete();

		for (int index{}; index < m_AmountOfFX; ++index)
		{
			const float halfFxSize{ 4.5f };
			const Point2f randomFXPosition
			{
				myutils::GetRandom(m_RootCenter.x + m_LocalPickupArea.width / 2 + m_LocalPickupArea.left, m_RootCenter.x - m_LocalPickupArea.width / 2 - m_LocalPickupArea.left),
				myutils::GetRandom(m_RootCenter.y + m_LocalPickupArea.height / 2 + m_LocalPickupArea.bottom, m_RootCenter.y - m_LocalPickupArea.height / 2 + m_LocalPickupArea.bottom)
			};

			GameObject::AddGameObject(new FX(randomFXPosition, "FX/PickupSparkleParticle.png", 3, 12, 0.1f));
		}
	}
}
#pragma endregion PrivateMethods