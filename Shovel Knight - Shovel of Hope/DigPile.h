#pragma once

#include "GameObject.h"
#include "HurtBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"
#include "Pickupable.h"

class DigPile final : public GameObject, public HurtBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	virtual ~DigPile() = default;

	DigPile(const DigPile& other) = delete;
	DigPile(DigPile&& other) = delete;
	DigPile& operator=(const DigPile& other) = delete;
	DigPile& operator=(DigPile&& other) = delete;

	//	Other special methods
	DigPile(const Point2f& bottomLeft);
	DigPile(float positionLeft, float positionBottom);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	void DropRandomly(Pickupable::Type type, int amount, const Vector2f& hurtNormals);
	void DropRandomlyToFit(Pickupable::Type type, const Vector2f& hurtNormals);

	const float m_MaxIdleSeconds;
	float m_AccumulatedIdleSeconds;

	int m_CurrentRowIndex, m_AmountOfGreyGems, m_ValueLeftToDropRandomly;
};