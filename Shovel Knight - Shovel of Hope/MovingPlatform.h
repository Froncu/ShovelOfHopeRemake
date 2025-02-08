#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"
#include "Rigidbody.h"
#include "SimpleSprite.h"

class MovingPlatform final : public GameObject, public KinematicCollider, public Rigidbody, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	~MovingPlatform() = default;

	MovingPlatform(const MovingPlatform& other) = delete;
	MovingPlatform(MovingPlatform&& other) = delete;
	MovingPlatform& operator=(const MovingPlatform& other) = delete;
	MovingPlatform& operator=(MovingPlatform&& other) = delete;

	//	Other special methods
	MovingPlatform(const Point2f& startCenter, const Point2f& localEndCenter, float startingFragment = 0.5f, float period = 3.0f);
	MovingPlatform(float startCenterX, float startCenterY, const Point2f& localEndCenter, float startingFragment = 0.5f, float period = 3.0f);
	MovingPlatform(const Point2f& startCenter, float localEndCenterX, float localEndCenterY, float startingFragment = 0.5f, float period = 3.0f);
	MovingPlatform(float startCenterX, float startCenterY, float localEndCenterX, float localEndCenterY, float startingFragment = 0.5f, float period = 3.0f);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	const Point2f m_StartCenter;
	const Point2f m_EndCenter;

	const bool m_SwapX, m_SwapY;
};