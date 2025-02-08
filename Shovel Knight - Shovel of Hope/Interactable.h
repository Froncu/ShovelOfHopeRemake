#pragma once

class Interactable
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~Interactable() = default;

	Interactable(const Interactable& other) = delete;
	Interactable(Interactable&& other) = delete;
	Interactable& operator=(const Interactable& other) = delete;;
	Interactable& operator=(Interactable&& other) = delete;;

	//	Other special methods


	//	Methods


	//	Setters
	

	//	Getters


protected:
	Interactable(const Point2f& rootCenter, float width, float height);
	Interactable(const Point2f& rootCenter, const Rectf& localLockArea);
	Interactable(const Point2f& rootCenter, const Point2f& localBottomLeft, float width, float height);
	Interactable(const Point2f& rootCenter, float localLeft, float localBottom, float width, float height);

private:
	virtual void OnInteractOverlap();
	virtual void OnInteractEndOverlap();

	const Point2f* const m_pRootCenter;
	const Rectf m_LocalLockArea;

	bool m_IsActive;

	bool m_OnInteractEndOverlapCalled;
};