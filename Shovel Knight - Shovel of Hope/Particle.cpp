#include "pch.h"
#include "Particle.h"

#include "myutils.h"

#pragma region Constructors/Destructor
Particle::Particle(const Point2f& center, const std::string& spritePath, const Vector2f& initialVelocity) :
	GameObject(center),
	Rigidbody(m_RootCenter, 1.0f, Vector2f(200.0f, 360.0f)),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, spritePath, 12)
{
	m_Velocity = initialVelocity;

	SimpleSprite::m_IsFlipped = myutils::GetRandom(1);
}

Particle::Particle(float centerX, float centerY, const std::string& spritePath, const Vector2f& initialVelocity) :
	Particle(Point2f(centerX, centerY), spritePath, initialVelocity)
{
}

Particle::Particle(const Point2f& center, const std::string& spritePath, float initialVelocityX, float initialVelocityY) :
	Particle(center, spritePath, Vector2f(initialVelocityX, initialVelocityY))
{
}

Particle::Particle(float centerX, float centerY, const std::string& spritePath, float initialVelocityX, float initialVelocityY) :
	Particle(Point2f(centerX, centerY), spritePath, Vector2f(initialVelocityX, initialVelocityY))
{
}
#pragma endregion Constructors/Destructor