#include "pch.h"
#include "CheckPoint.h"

#include "SoundManager.h"

#pragma region Constructors/Destructor
CheckPoint::CheckPoint(const Point2f& bottomLeft) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 26.5f),
	HurtBox(m_RootCenter, 0.2f),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Environment/CheckPoint.png", 7),
	SpriteAnimator(5, 3, 0.18f),

	m_IsActivated{},

	m_Shake{}, m_IsOnLeft{},
	m_SpriteVelocity{},
	m_SpriteAcceleration{ 750.0f }
{
	HurtBox::AddLocalHurtBox(0.0f, 12.0f, 35.0f, 30.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 240.0f);
}

CheckPoint::CheckPoint(float positionLeft, float positionBottom) :
	CheckPoint(Point2f(positionLeft, positionBottom))
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void CheckPoint::Update(float elapsedSeconds)
{
	if (m_Shake)
	{
		if (SimpleSprite::m_OffsetX < 2.0f)
		{
			m_SpriteVelocity += m_SpriteAcceleration * elapsedSeconds;
			SimpleSprite::m_OffsetX += m_SpriteVelocity * elapsedSeconds;

			if (m_IsOnLeft && SimpleSprite::m_OffsetX > 0)
			{
				m_Shake = false;
				m_IsOnLeft = false;
			}
		}
		else
		{
			m_SpriteVelocity = 0.0f;
			SimpleSprite::m_OffsetX = -1.0f;

			m_IsOnLeft = true;
		}
	}
}

void CheckPoint::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	if (hurtNormals.y)
	{
		SoundManager::PlayEffect("Audio/CheckPointDamage.wav", false);
		if (!m_IsActivated)
		{
			SoundManager::PlayEffect("Audio/CheckPointActivate.wav", false);
			m_IsActivated = true;

			SpriteAnimator::SetFrameSeconds(0.09f);
			SpriteAnimator::SetCurrentRowIndex(1, 5);
		}
	}

	m_Shake = true;
}

void CheckPoint::OnColumnChange(int currentColumnIndex)
{
	if (m_IsActivated && !currentColumnIndex)
	{
		SpriteAnimator::SetFrameSeconds(0.18f);
		SpriteAnimator::SetCurrentRowIndex(2, 3);
	}
}
#pragma endregion Components