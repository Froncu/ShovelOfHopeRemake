#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "SimpleSprite.h"
#include "Pickupable.h"

class DirtBlock final : public GameObject, public KinematicCollider, public HurtBox, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	virtual ~DirtBlock() = default;

	DirtBlock(const DirtBlock& other) = delete;
	DirtBlock(DirtBlock&& other) = delete;
	DirtBlock& operator=(const DirtBlock& other) = delete;
	DirtBlock& operator=(DirtBlock&& other) = delete;

	//	Other special methods
	DirtBlock(const Point2f& bottomLeft, Pickupable::Type pickupableToDrop = Pickupable::Type::Empty);
	DirtBlock(float positionLeft, float positionBottom, Pickupable::Type pickupableToDrop = Pickupable::Type::Empty);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:
	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	const Pickupable::Type m_PickupableToDrop;
};