#pragma once

#include <vector>

class KinematicCollider
{
public:
	// Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~KinematicCollider() = default;

	KinematicCollider(const KinematicCollider& other) = delete;
	KinematicCollider(KinematicCollider&& other) = delete;
	KinematicCollider& operator=(const KinematicCollider& other) = delete;
	KinematicCollider& operator=(KinematicCollider&& other) = delete;

	//	Other special methods


	//	Methods


	//	Setters
	

	//	Getters

	
protected:
	KinematicCollider(const Point2f& rootCenter, float width, float height);
	KinematicCollider(const std::vector<Point2f>& vVertices);

private:
	static float m_SMALLESTSIZE;

	const Point2f* const m_pRootCenter;
	const float m_Width, m_Height;

	bool m_IsActive;

	const std::vector<Point2f>* const m_pvVertices;
};