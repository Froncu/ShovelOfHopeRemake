#include "pch.h"
#include "Interactor.h"

#pragma region Constructors/Destructor
Interactor::Interactor(const Point2f& rootCenter, float width, float height) :
	m_pRootCenter{ &rootCenter },
	m_LocalInteractArea{ 0.0f, 0.0f, width, height },

	m_OnInteractEndOverlapCalled{ true }
{
}

Interactor::Interactor(const Point2f& rootCenter, const Rectf& localInteracArea) :
	m_pRootCenter{ &rootCenter },
	m_LocalInteractArea{ localInteracArea },

	m_OnInteractEndOverlapCalled{ true }
{
}

Interactor::Interactor(const Point2f& rootCenter, const Point2f& localBottomLeft, float width, float height) :
	Interactor(rootCenter, Rectf(localBottomLeft.x, localBottomLeft.y, width, height))
{
}
Interactor::Interactor(const Point2f& rootCenter, float localLeft, float localBottom, float width, float height) :
	Interactor(rootCenter, Rectf(localLeft, localBottom, width, height))
{
}
#pragma endregion Constructors/Destructor



#pragma region PrivateMethods
void Interactor::OnInteractOverlap(const Rectf& interactingLockArea)
{

}

void Interactor::OnInteractEndOverlap()
{

}
#pragma endregion PrivateMethods