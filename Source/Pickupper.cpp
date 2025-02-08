#include "pch.h"
#include "Pickupper.h"

#pragma region Constructors/Destructor
Pickupper::Pickupper(const Point2f& rootCenter, float width, float height) :
	m_pRootCenter{ &rootCenter },
	m_LocalPickupArea{ 0.0f, 0.0f, width, height }
{
}

Pickupper::Pickupper(const Point2f& rootCenter, const Rectf& localPickupArea) :
	m_pRootCenter{ &rootCenter },
	m_LocalPickupArea{ localPickupArea }
{
}

Pickupper::Pickupper(const Point2f& rootCenter, const Point2f& localBottomLeft, float width, float height) :
	Pickupper(rootCenter, Rectf(localBottomLeft.x, localBottomLeft.y, width, height))
{
}
Pickupper::Pickupper(const Point2f& rootCenter, float localLeft, float localBottom, float width, float height) :
	Pickupper(rootCenter, Rectf(localLeft, localBottom, width, height))
{
}
#pragma endregion Constructors/Destructor



#pragma region PrivateMethods
void Pickupper::OnPickup(int value, bool heals)
{

}
#pragma endregion PrivateMethods