#pragma once

#include "utils.h"

class DynamicCollider
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~DynamicCollider() = default;

	DynamicCollider(const DynamicCollider& other) = delete;
	DynamicCollider(DynamicCollider&& other) = delete;
	DynamicCollider& operator=(const DynamicCollider& other) = delete;
	DynamicCollider& operator=(DynamicCollider&& other) = delete;

	//	Other special methods


	//	Methods


	//	Setters
	

	//	Getters


protected:
	DynamicCollider(Point2f& rootCenter);

	Rectf m_LocalCollisionBox;
	
	bool m_IsActive;

private:
	virtual void OnCollision(const utils::HitInfo& hitInfo);

	Point2f* const m_pRootCenter;

	float m_LastHitRigidbodyIntersectionY;
};