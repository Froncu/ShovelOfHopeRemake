#pragma once

#include <vector>

struct LocalHurtBox final
{
public:
	//	Rule of 5
	~LocalHurtBox() = default;

	LocalHurtBox(const LocalHurtBox& other) = default;
	LocalHurtBox(LocalHurtBox&& other) = default;
	LocalHurtBox& operator=(const LocalHurtBox& other) = default;
	LocalHurtBox& operator=(LocalHurtBox&& other) = default;

	//	Other special methods
	LocalHurtBox(const Rectf& localHurtBox);

	Rectf localHurtBox;
	std::vector<int> vGroupNumbers;
	Vector2f knockBackVelocity;
};

class HurtBox
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~HurtBox() = default;

	HurtBox(const HurtBox& other) = delete;
	HurtBox(HurtBox&& other) = delete;
	HurtBox& operator=(const HurtBox& other) = delete;
	HurtBox& operator=(HurtBox&& other) = delete;

	//	Other special methods


	//	Methods
	

	//	Setters


	//	Getters


protected:
	HurtBox(const Point2f& rootCenter, float cooldownSeconds = 0.12f);

	int AddLocalHurtBox(const Rectf& localHurtBox);
	int AddLocalHurtBox(float width = 0.0f, float height = 0.0f);
	int AddLocalHurtBox(const Point2f& localBottomLeft, float width, float height);
	int AddLocalHurtBox(float localLeft, float localBottom, float width, float height);

	void AddGroupNumber(const std::initializer_list<int>& groupNumbers, int localHurtBoxIndex = INT_MAX);
	void AddGroupNumber(int groupNumber, int localHurtBoxIndex = INT_MAX);

	void SetLocalHurtBox(const Rectf& localHurtBox, int localHurtBoxIndex = INT_MAX);
	void SetLocalHurtBox(const Point2f& localBottomLeft, float width, float height, int localHurtBoxIndex = INT_MAX);
	void SetLocalHurtBox(float localLeft, float localBottom, float width, float height, int localHurtBoxIndex = INT_MAX);

	void SetKnockBackVelocity(const Vector2f& knockBackVelocity, int localHurtBoxIndex = INT_MAX);
	void SetKnockBackVelocity(float knockBackVelocityX, float knockBackVelocityY, int localHurtBoxIndex = INT_MAX);

	const Rectf& GetLocalHurtBox(int localHurtBoxIndex) const;

	bool m_IsActive;


private:
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex);

	const Point2f* const m_pRootCenter;
	std::vector<LocalHurtBox> m_vLocalHurtBoxes;

	const float m_MaxCooldownSeconds;
	float m_AccumulatedCooldownSeconds;
	bool m_IsOnCooldown;
};