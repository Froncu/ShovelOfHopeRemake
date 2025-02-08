#pragma once

#include "GameObject.h"
#include "HurtBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class DigClod final : public GameObject, public HurtBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	virtual ~DigClod() = default;

	DigClod(const DigClod& other) = delete;
	DigClod(DigClod&& other) = delete;
	DigClod& operator=(const DigClod& other) = delete;
	DigClod& operator=(DigClod&& other) = delete;

	//	Other special methods
	DigClod(const Point2f& bottomLeft, bool isFlipped = false);
	DigClod(float positionLeft, float positionBottom, bool isFlipped = false);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	const float m_MaxIdleSeconds, m_MaxDespawningSeconds;
	float m_AccumulatedSeconds;

	const bool m_IsFlipped;
};