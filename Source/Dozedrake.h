#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "Rigidbody.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

#include "Pickupable.h"

class Dozedrake final : public GameObject, public DynamicCollider, public Rigidbody, public HurtBox, public HitBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	~Dozedrake() = default;

	Dozedrake(const Dozedrake& other) = delete;
	Dozedrake(Dozedrake&& other) = delete;
	Dozedrake& operator=(const Dozedrake& other) = delete;
	Dozedrake& operator=(Dozedrake&& other) = delete;

	//	Other special methods
	Dozedrake(const Point2f& bottomLeft);
	Dozedrake(float positionLeft, float positionBottom);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	enum class State
	{
		BlowingCooldown,
		Sleeping,
		OpeningMouth,
		Blowing,
		ClosingMouth,
		WalkingForward,
		WalkingBackward,
		Hurt,
		Dying
	};

	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	//	SpriteAnimator component
	virtual void OnColumnChange(int currentColumnIndex) override;

	void DropRandomly(Pickupable::Type type, int amount);

	State m_State;

	int m_Health;

	const float m_MaxDyingSeconds, m_MaxKnockingSeconds;
	float m_AccumulatedDyingSeconds;

	const float m_BlowingCooldownSeconds;
	float m_AccumulatedBlowingCooldownSeconds{};

	const float m_DeltaBlowSeconds;
	float m_AccumulatedBlowSeconds;
	const int m_AmountOfBubblesToBlow;
	int m_AmountOfBlownBubbles;

	int m_DropRandomlyCounter, FXCounter;
	const float m_FirstDropRandomlySeconds, m_SecondDropRandomlySeconds, m_DeltaFXSeconds;
};