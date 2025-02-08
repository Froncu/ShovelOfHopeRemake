#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"
#include "HurtBox.h"
#include "HitBox.h"
#include "SimpleSprite.h"
#include "Pickupable.h"

class DirtBlockSmall final : public GameObject, public KinematicCollider, public HurtBox, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	virtual ~DirtBlockSmall() = default;

	DirtBlockSmall(const DirtBlockSmall& other) = delete;
	DirtBlockSmall(DirtBlockSmall&& other) = delete;
	DirtBlockSmall& operator=(const DirtBlockSmall& other) = delete;
	DirtBlockSmall& operator=(DirtBlockSmall&& other) = delete;

	//	Other special methods
	DirtBlockSmall(const Point2f& bottomLeft, Pickupable::Type pickupableToDrop = Pickupable::Type::Empty);
	DirtBlockSmall(float positionLeft, float positionBottom, Pickupable::Type pickupableToDrop = Pickupable::Type::Empty);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:
	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	const Pickupable::Type m_PickupableToDrop;
};