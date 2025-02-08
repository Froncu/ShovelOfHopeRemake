#pragma once

class Interactor
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~Interactor() = default;

	Interactor(const Interactor& other) = delete;
	Interactor(Interactor&& other) = delete;
	Interactor& operator=(const Interactor& other) = delete;
	Interactor& operator=(Interactor&& other) = delete;

	//	Other special methods


	//	Methods


	//	Setters
	

	//	Getters


protected:
	Interactor(const Point2f& rootCenter, float width, float height);
	Interactor(const Point2f& rootCenter, const Rectf& localInteractArea);
	Interactor(const Point2f& rootCenter, const Point2f& localBottomLeft, float width, float height);
	Interactor(const Point2f& rootCenter, float localLeft, float localBottom, float width, float height);

private:
	virtual void OnInteractOverlap(const Rectf& interactingLockArea);
	virtual void OnInteractEndOverlap();

	const Point2f* const m_pRootCenter;
	const Rectf m_LocalInteractArea;

	bool m_OnInteractEndOverlapCalled;
};