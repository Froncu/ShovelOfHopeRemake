#pragma once

#include "GameObject.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "Rigidbody.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class Bubble final : public GameObject, public HurtBox, public HitBox, public Rigidbody, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	~Bubble() = default;

	Bubble(const Bubble& other) = delete;
	Bubble(Bubble&& other) = delete;
	Bubble& operator=(const Bubble& other) = delete;
	Bubble& operator=(Bubble&& other) = delete;

	//	Other special methods
	Bubble(const Point2f& center, const Point2f& localTargetCenter, bool respawn = true);
	Bubble(float centerX, float centerY, const Point2f& localTargetCenter, bool respawn = true);
	Bubble(const Point2f& center, float localTargetPositionX, float localTargetPositionY, bool respawn = true);
	Bubble(float centerX, float centerY, float localTargetPositionX, float localTargetPositionY, bool respawn = true);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HitBox component
	virtual void OnHit(const Vector2f& hitNormals, const Vector2f& knockBackVelocity, int localHitBoxIndex) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	void Pop();

	const Point2f m_SpawnCenter, m_TargetCenter;

	const bool m_Respawn;

	const Vector2f m_Direction;
	const float m_HorizontalAmplitude;

	float m_AccumulatedSeconds, m_Period;
};