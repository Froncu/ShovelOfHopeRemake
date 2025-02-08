#include "pch.h"
#include "DynamicCollider.h"

#pragma region Constructors/Destructor
DynamicCollider::DynamicCollider(Point2f& rootCenter) :
	m_pRootCenter{ &rootCenter },
	m_LocalCollisionBox{},

	m_IsActive{ true },

	m_LastHitRigidbodyIntersectionY{ INFINITY }
{
}
#pragma endregion Constructors/Destructor



#pragma region PrivateMethods
void DynamicCollider::OnCollision(const utils::HitInfo& hitInfo)
{

}
#pragma endregion PrivateMethods