#include "pch.h"
#include "Interactable.h"

#pragma region Constructors/Destructor
Interactable::Interactable(const Point2f& rootCenter, float width, float height) :
	m_pRootCenter{ &rootCenter },
	m_LocalLockArea{ 0.0f, 0.0f, width, height },

	m_IsActive{ true },

	m_OnInteractEndOverlapCalled{ true }
{
}

Interactable::Interactable(const Point2f& rootCenter, const Rectf& localLockArea) :
	m_pRootCenter{ &rootCenter },
	m_LocalLockArea{ localLockArea },

	m_IsActive{ true },

	m_OnInteractEndOverlapCalled{ true }
{
}

Interactable::Interactable(const Point2f& rootCenter, const Point2f& localBottomLeft, float width, float height) :
	Interactable(rootCenter, Rectf(localBottomLeft.x, localBottomLeft.y, width, height))
{
}
Interactable::Interactable(const Point2f& rootCenter, float localLeft, float localBottom, float width, float height) :
	Interactable(rootCenter, Rectf(localLeft, localBottom, width, height))
{
}
#pragma endregion Constructors/Destructor



#pragma region PrivateMethods
void Interactable::OnInteractOverlap()
{

}

void Interactable::OnInteractEndOverlap()
{

}
#pragma endregion PrivateMethods