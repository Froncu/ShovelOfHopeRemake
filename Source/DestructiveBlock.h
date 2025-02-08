#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"
#include "HurtBox.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class DestructiveBlock final : public GameObject, public KinematicCollider, public HurtBox, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other
	friend class Destructive;

	//	Rule of 5
	~DestructiveBlock();

	DestructiveBlock(const DestructiveBlock& other) = delete;
	DestructiveBlock(DestructiveBlock&& other) = delete;
	DestructiveBlock& operator=(const DestructiveBlock& other) = delete;
	DestructiveBlock& operator=(DestructiveBlock&& other) = delete;

	//	Other special methods
	DestructiveBlock(const Point2f& bottomLeft, int row);
	DestructiveBlock(float positionLeft, float positionBottom, int row);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	//	HurtBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	bool m_WasHurt;

	GameObject* m_pGameObjectToDrop;
};