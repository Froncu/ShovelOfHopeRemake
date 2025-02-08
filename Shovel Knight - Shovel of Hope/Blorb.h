#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "Rigidbody.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class Blorb final : public GameObject, public DynamicCollider, public Rigidbody, public HurtBox, public HitBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	~Blorb() = default;

	Blorb(const Blorb& other) = delete;
	Blorb(Blorb&& other) = delete;
	Blorb& operator=(const Blorb& other) = delete;
	Blorb& operator=(Blorb&& other) = delete;

	//	Other special methods
	Blorb(const GameObject* const pTarget, const Point2f& bottomLeft);
	Blorb(const GameObject* const pTarget, float positionleft, float positionBottom);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	enum class State
	{
		Idle,
		Hurt,
		Slow,
		Fast,
		Jump,
		Jumped,
		Attack,
		Attacked
	};

	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	//	HurtBox component
	virtual void OnCollision(const utils::HitInfo& hitInfo) override;

	const GameObject* const m_pTarget;

	State m_State;

	int m_Health;

	float m_AccumulatedSeconds, m_MaxSeconds;

	const float m_TriggerDistance, m_AttackDistance;
};