#pragma once

#include "GameObject.h"
#include "HurtBox.h"
#include "SimpleSprite.h"

class Platter final : public GameObject, public HurtBox, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	~Platter() = default;

	Platter(const Platter& other) = delete;
	Platter(Platter&& other) = delete;
	Platter& operator=(const Platter& other) = delete;
	Platter& operator=(Platter&& other) = delete;

	//	Other special methods
	Platter(const Point2f& bottomLeft);
	Platter(float positionBottom, float positionLeft);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	HitBox component
	virtual void OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex) override;

	const float m_MaxAccumulatedTime;
	float m_AccumulatedTime;
};