#include "pch.h"
#include "KinematicCollider.h"

#pragma region StaticVariables
float KinematicCollider::m_SMALLESTSIZE{ 16.0f };
#pragma endregion StaticVariables



#pragma region Constructors/Destructor
KinematicCollider::KinematicCollider(const Point2f& rootCenter, float width, float height) :
	m_pRootCenter{ &rootCenter },
	m_Width{ width }, m_Height{ height },

	m_IsActive{ true },

	m_pvVertices{ nullptr }
{
}

KinematicCollider::KinematicCollider(const std::vector<Point2f>& vVertices) :
	m_pRootCenter{ nullptr },
	m_Width{}, m_Height{},

	m_IsActive{ true },

	m_pvVertices { &vVertices }
{
}
#pragma endregion Constructors/Destructors