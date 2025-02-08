#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "RigidBody.h"
#include "HurtBox.h"
#include "SimpleSprite.h"
#include "Pickupable.h"

class Clod final : public GameObject, public DynamicCollider, public Rigidbody, public HurtBox, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	virtual ~Clod() = default;

	Clod(const Clod& other) = delete;
	Clod(Clod&& other) = delete;
	Clod& operator=(const Clod& other) = delete;
	Clod& operator=(Clod&& other) = delete;

	//	Other special methods
	Clod(const Point2f& center, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));
	Clod(float centerX, float centerY, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));

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

	void DropRandomly(Pickupable::Type type, int amount);
};