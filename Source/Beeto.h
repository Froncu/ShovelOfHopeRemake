#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "Rigidbody.h"
#include "HitBox.h"
#include "HurtBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class Beeto final : public GameObject, public DynamicCollider, public Rigidbody, public HitBox, public HurtBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	virtual ~Beeto() = default;

	Beeto(const Beeto& other) = delete;
	Beeto(Beeto&& other) = delete;
	Beeto& operator=(const Beeto& other) = delete;
	Beeto& operator=(Beeto&& other) = delete;

	//	Other special methods
	Beeto(const Point2f& bottomLeft, bool isFacingLeft, float localLeftBorder = 0, float localRightBorder = 0);
	Beeto(float bottomLeftX, float bottomLeftY, bool isFacingLeft, float localLeftBorder = 0, float localRightBorder = 0);

	//	Methods


	//	Setters


	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	DynamicCollider component
	virtual void OnCollision(const utils::HitInfo& hitInfo) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	const float m_LeftBorder, m_RightBorder;
	bool m_HasBeenHurt, m_IsFacingLeft;
};