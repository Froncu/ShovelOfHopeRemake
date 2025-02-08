#include "pch.h"
#include "MovingPlatform.h"

#pragma region Constructors/Destructor
MovingPlatform::MovingPlatform(const Point2f& startCenter, const Point2f& localEndCenter, float startingFragment, float period) :
	GameObject(startCenter.x + startingFragment * localEndCenter.x, startCenter.y + startingFragment * localEndCenter.y, true),
	KinematicCollider(m_RootCenter, 48.0f, 16.0f),
	Rigidbody(m_RootCenter, 0.0f, Vector2f((localEndCenter.x) / (period / 2), (localEndCenter.y) / (period / 2))),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Resources/Environment/MovingPlatform.png", 7),

	m_StartCenter{ startCenter },
	m_EndCenter{ m_StartCenter.x + localEndCenter.x, m_StartCenter.y + localEndCenter.y },

	m_SwapX{ m_StartCenter.x > m_EndCenter.x ? true : false }, m_SwapY{ m_StartCenter.y > m_EndCenter.y ? true : false }
{
	m_Velocity.x = m_MaxVelocity.x;
	m_Velocity.y = m_MaxVelocity.y;
}

MovingPlatform::MovingPlatform(float startCenterX, float startCenterY, const Point2f& localEndCenter, float startingFragment, float period) :
	MovingPlatform(Point2f(startCenterX, startCenterY), localEndCenter, startingFragment, period)
{
}

MovingPlatform::MovingPlatform(const Point2f& startCenter, float localEndCenterX, float localEndCenterY, float startingFragment, float period) :
	MovingPlatform(startCenter, Point2f(localEndCenterX, localEndCenterY), startingFragment, period)
{
}

MovingPlatform::MovingPlatform(float startCenterX, float startCenterY, float localEndCenterX, float localEndCenterY, float startingFragment, float period) :
	MovingPlatform(Point2f(startCenterX, startCenterY), Point2f(localEndCenterX, localEndCenterY), startingFragment, period)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void MovingPlatform::Update(float elapsedSeconds)
{
	if (!m_SwapX)
	{
		if (m_RootCenter.x > m_EndCenter.x)
		{
			m_Velocity.x = -m_MaxVelocity.x;
		}
		else if (m_RootCenter.x < m_StartCenter.x)
		{
			m_Velocity.x = m_MaxVelocity.x;
		}
	}
	else
	{
		if (m_RootCenter.x > m_StartCenter.x)
		{
			m_Velocity.x = -m_MaxVelocity.x;
		}
		else if (m_RootCenter.x < m_EndCenter.x)
		{
			m_Velocity.x = m_MaxVelocity.x;
		}
	}

	if (!m_SwapY)
	{
		if (m_RootCenter.y > m_EndCenter.y)
		{
			m_Velocity.y = -m_MaxVelocity.y;
		}
		else if (m_RootCenter.y < m_StartCenter.y)
		{
			m_Velocity.y = m_MaxVelocity.y;
		}
	}
	else
	{
		if (m_RootCenter.y > m_StartCenter.y)
		{
			m_Velocity.y = -m_MaxVelocity.y;
		}
		else if (m_RootCenter.y < m_EndCenter.y)
		{
			m_Velocity.y = m_MaxVelocity.y;
		}
	}
}
#pragma endregion Components