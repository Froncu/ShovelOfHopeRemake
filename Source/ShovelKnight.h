#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "Rigidbody.h"
#include "HitBox.h"
#include "HurtBox.h"
#include "Pickupper.h"
#include "Interactor.h"
#include "Interactor.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class ShovelKnight final : public GameObject, public DynamicCollider, public Rigidbody, public HitBox, public HurtBox, public Pickupper, public Interactor, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other
	friend class LevelManager;
	friend class HUD;

	//	Rule of 5
	~ShovelKnight() = default;

	ShovelKnight(const ShovelKnight& other) = delete;
	ShovelKnight(ShovelKnight&& other) = delete;
	ShovelKnight& operator=(const ShovelKnight& other) = delete;
	ShovelKnight& operator=(ShovelKnight&& other) = delete;

	//	Other special methods
	ShovelKnight(const Point2f& bottomLeft, int startingHealth = 8, int startingScore = 0);
	ShovelKnight(float bottomLeftX, float bottomLeftY, int startingHealth = 8, int startingScore = 0);

	//	Methods
	void Reset(const Point2f& bottomLeft, int startingScore);
	void Reset(float bottomLeftX, float bottomLeftY, int startingScore);

	//	Setters


	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	DynamicCollider component
	virtual void OnCollision(const utils::HitInfo& hitInfo) override;

	//	HitBox component
	virtual void OnHit(const Vector2f& hitNormals, const Vector2f& knockbackVelocity, int localHitBoxIndex) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	//	Pickupper component
	virtual void OnPickup(int value, bool heals) override;

	//	Interactor component
	virtual void OnInteractOverlap(const Rectf& interactingArea) override;
	virtual void OnInteractEndOverlap() override;

	//	SpriteAnimator component
	virtual void OnColumnChange(int currentColumnIndex) override;

	void HandleInteractState(float elapsedSeconds);
	void HandleCombatState(float elapsedSeconds);
	void HandleSwingState(float elapsedSeconds);
	void HandleJumpChargeState(float elapsedSeconds);
	void HandleVerticalState(float elapsedSeconds);
	void HandleHorizontalState(float elapsedSeconds);
	void HandleSprite(float elapsedSeconds);

	const float m_MaxIdleTime;
	float m_AccumulatedIdleTime;

	enum class InteractState
	{
		None,
		Climbing,
		EndCLimbing,
		Looting,
		Cooldown
	}
	m_InteractState;

	enum class SwingingState
	{
		None,
		SwingingCooldown,
	}
	m_SwingingState;

	enum class CombatState
	{
		None,
		Swinging,
		Thrusting,
		Hurt,
		Dead
	}
	m_CombatState;
	const float m_MinAirSeconds;
	const float m_MaxHurtSeconds;
	float m_AccumulatedHurtSeconds;

	enum class JumpChargeState
	{
		None,
		Charging,
		ChargeCooldown
	}
	m_JumpChargeState;
	const float m_JumpVelocity, m_MaxJumpChargeSeconds;
	float m_AccumulatedJumpChargeSeconds;

	enum class VerticalState
	{
		Standing,
		Jumping,
		Crouching
	}
	m_VerticalState;
	float m_AccumulatedAirSeconds;

	enum class HorizontalState
	{
		Standing,
		LeftStepping,
		LeftRunning,
		LeftBreaking,
		RightStepping,
		RightRunning,
		RightBreaking
	}
	m_HorizontalState;
	const float m_Acceleration;

	const int m_MaxHealth;
	int m_Health;
	int m_Score;
};