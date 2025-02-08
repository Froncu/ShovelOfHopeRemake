#pragma once

#include <vector>

struct LocalHitBox final
{
public:
	//	Rule of 5
	~LocalHitBox() = default;

	LocalHitBox(const LocalHitBox& other) = default;
	LocalHitBox(LocalHitBox&& other) = default;
	LocalHitBox& operator=(const LocalHitBox& other) = default;
	LocalHitBox& operator=(LocalHitBox&& other) = default;

	//	Other special methods
	LocalHitBox(const Rectf& localHitBox);

	Rectf localHitBox;
	bool isActive;
	std::vector<int> vGroupNumbers;
	Vector2f hitDirection;
	int damage;
};

class HitBox
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~HitBox() = default;

	HitBox(const HitBox& other) = delete;
	HitBox(HitBox&& other) = delete;
	HitBox& operator=(const HitBox& other) = delete;
	HitBox& operator=(HitBox&& other) = delete;

	//	Other special methods


	//	Methods


	//	Setters


	//	Getters
	

protected:
	HitBox(const Point2f& rootCenter);

	int AddLocalHitBox(const Rectf& localHitBox);
	int AddLocalHitBox(float width = 0.0f, float height = 0.0f);
	int AddLocalHitBox(const Point2f& localBottomLeft, float width, float height);
	int AddLocalHitBox(float localLeft, float localBottom, float width, float height);

	void SetActive(bool isActive, int localHitBoxIndex = INT_MAX);

	void AddGroupNumber(const std::initializer_list<int>& groupNumbers, int localHitBoxIndex = INT_MAX);
	void AddGroupNumber(int groupNumber, int localHitBoxIndex = INT_MAX);

	void SetLocalHitBox(const Rectf& localHitBox, int localHitBoxIndex = INT_MAX);
	void SetLocalHitBox(const Point2f& localBottomLeft, float width, float height, int localHitBoxIndex = INT_MAX);
	void SetLocalHitBox(float localLeft, float localBottom, float width, float height, int localHitBoxIndex = INT_MAX);

	void SetHitDirection(const Vector2f& hitDirection, int localHitBoxIndex = INT_MAX);
	void SetHitDirection(float horizontalHitDirection, float verticalHitDirection, int localHitBoxIndex = INT_MAX);
	
	void SetDamage(int damage, int localHitBoxIndex = INT_MAX);

	const Rectf& GetLocalHitBox(int localHitBoxIndex) const;
	bool GetIsActive(int localHitBoxIndex) const;

private:
	virtual void OnHit(const Vector2f& hitNormals, const Vector2f& knockBackVelocity, int localHitBoxIndex);

	const Point2f* const m_pRootCenter;
	std::vector<LocalHitBox> m_vLocalHitBoxes;
};