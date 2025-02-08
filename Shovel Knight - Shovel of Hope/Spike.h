#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"
#include "HitBox.h"
#include "SimpleSprite.h"

class Spike final : public GameObject, public KinematicCollider, public HitBox, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	~Spike() = default;

	Spike(const Spike& other) = delete;
	Spike(Spike&& other) = delete;
	Spike& operator=(const Spike& other) = delete;
	Spike& operator=(Spike&& other) = delete;

	//	Other special methods
	Spike(const Point2f& bottomLeft, int width);
	Spike(float positionLeft, float positionBottom, int width);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:

};