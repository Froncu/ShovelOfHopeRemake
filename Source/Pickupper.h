#pragma once

class Pickupper
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~Pickupper() = default;

	Pickupper(const Pickupper& other) = delete;
	Pickupper(Pickupper&& other) = delete;
	Pickupper& operator=(const Pickupper& other) = delete;
	Pickupper& operator=(Pickupper&& other) = delete;

	//	Other special methods


	//	Methods
	

	//	Setters
	

	//	Getters


protected:
	Pickupper(const Point2f& rootCenter, float width, float height);
	Pickupper(const Point2f& rootCenter, const Rectf& localPickupArea = Rectf(0.0f, 0.0f, 0.0f, 0.0f));
	Pickupper(const Point2f& rootCenter, const Point2f& localBottomLeft, float width, float height);
	Pickupper(const Point2f& rootCenter, float localLeft, float localBottom, float width, float height);

private:
	virtual void OnPickup(int value, bool heals);

	const Point2f* const m_pRootCenter;
	Rectf m_LocalPickupArea;
};