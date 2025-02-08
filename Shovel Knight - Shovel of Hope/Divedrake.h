#pragma once

#include "GameObject.h"
#include "RigidBody.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class Divedrake final : public GameObject, public Rigidbody, public HurtBox, public HitBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	~Divedrake() = default;

	Divedrake(const Divedrake& other) = delete;
	Divedrake(Divedrake&& other) = delete;
	Divedrake& operator=(const Divedrake& other) = delete;
	Divedrake& operator=(Divedrake&& other) = delete;

	//	Other special methods
	Divedrake(const Point2f& pivotPoint, float horizontalAmplitude, float verticalAmplitude);
	Divedrake(float pivotPointX, float pivotPointY, float horizontalAmplitude, float verticalAmplitude);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	const Point2f m_PivotPoint;
	const float m_HorizontalAmplitude, m_VerticalAmplitude;

	const float m_Period;
	float m_AccumulatedSeconds;

	int m_Health;
};