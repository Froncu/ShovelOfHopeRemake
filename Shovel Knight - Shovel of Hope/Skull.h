#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "Rigidbody.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "SimpleSprite.h"

class Skull final : public GameObject, public DynamicCollider, public Rigidbody, public HurtBox, public HitBox, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	~Skull() = default;

	Skull(const Skull& other) = delete;
	Skull(Skull&& other) = delete;
	Skull& operator=(const Skull& other) = delete;
	Skull& operator=(Skull&& other) = delete;

	//	Other special methods
	Skull(const Point2f& bottomLeft, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));
	Skull(float positionLeft, float positionBottom, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	//	HitBox component
	virtual void OnHit(const Vector2f& hitNormals, const Vector2f& knockbackVelocity, int localHitBoxIndex) override;

	//	DynamicCollider component
	virtual void OnCollision(const utils::HitInfo& hitInfo) override;

	Vector2f GetRandomInitialDropVelocity(bool dropLeft = false) const;

	bool m_HasBeenHit;
};