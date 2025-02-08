#include "pch.h"
#include "Rigidbody.h"

#pragma region StaticDataMembers
const float Rigidbody::m_GRAVITY{ -1200 };
#pragma endregion StaticDataMembers



#pragma region Constructors/Destructor
Rigidbody::Rigidbody(Point2f& rootCenter, float gravityMultiplier, const Vector2f& maxVelocity) :
	m_pRootCenter{ &rootCenter },

	m_GravityMultiplier{ abs(gravityMultiplier) },

	m_MaxVelocity{ abs(maxVelocity.x), abs(maxVelocity.y)},
	m_Velocity{}
{
}
#pragma endregion Constructors/Destructor



#pragma region ProtectedMethods
void Rigidbody::SetGravityMultiplier(float gravityMultiplier)
{
	m_GravityMultiplier = gravityMultiplier;
}
#pragma endregion ProtectedMethods