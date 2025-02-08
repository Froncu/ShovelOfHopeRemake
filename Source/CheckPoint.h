#pragma once

#include "GameObject.h"
#include "HurtBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class CheckPoint final : public GameObject, public HurtBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other
	friend class LevelManager;

	//	Rule of 5
	~CheckPoint() = default;

	CheckPoint(const CheckPoint& other) = delete;
	CheckPoint(CheckPoint&& other) = delete;
	CheckPoint& operator=(const CheckPoint& other) = delete;
	CheckPoint& operator=(CheckPoint&& other) = delete;

	//	Other special methods
	CheckPoint(const Point2f& bottomLeft);
	CheckPoint(float positionLeft, float positionBottom);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HitBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	//	SpriteAnimator component
	virtual void OnColumnChange(int currentColumnIndex) override;

	const Point2f m_Center;
	bool m_IsActivated;

	bool m_Shake, m_IsOnLeft;
	float m_SpriteVelocity{};
	const float m_SpriteAcceleration{};
};