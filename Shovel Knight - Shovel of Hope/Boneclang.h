#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "Rigidbody.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class Boneclang final : public GameObject, public DynamicCollider, public Rigidbody, public HurtBox, public HitBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	~Boneclang() = default;

	Boneclang(const Boneclang& other) = delete;
	Boneclang(Boneclang&& other) = delete;
	Boneclang& operator=(const Boneclang& other) = delete;
	Boneclang& operator=(Boneclang&& other) = delete;

	//	Other special methods
	Boneclang(const GameObject* const pTarget, const Point2f& bottomLeft);
	Boneclang(const GameObject* const pTarget, float positionLeft, float positionBottom);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	enum class State
	{
		Idle,
		MovingAway,
		MovingTowards,
		MovingForAttack,
		Attack,
		Hurt
	};

	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	//	SpriteAnimator component
	virtual void OnColumnChange(int currentColumnIndex) override;

	Vector2f GetRandomInitialDropVelocity() const;

	const GameObject* const m_pTarget;

	State m_State;

	int m_Health;

	float m_AccumulatedHitBoxCooldownSeconds;
	const float m_MaxHitBoxCooldownSeconds;

	float m_AccumulatedMoveSeconds, m_MaxMoveSeconds;

	const float m_TriggerDistance;
};