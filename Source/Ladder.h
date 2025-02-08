#pragma once

#include "GameObject.h"
#include "Interactable.h"
#include "SimpleSprite.h"

class Ladder final : public GameObject, public Interactable, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	virtual ~Ladder() = default;

	Ladder(const Ladder& other) = delete;
	Ladder(Ladder&& other) = delete;
	Ladder& operator=(const Ladder& other) = delete;
	Ladder& operator=(Ladder&& other) = delete;

	//	Other special methods
	Ladder(const Point2f& bottomLeft, int height);
	Ladder(float positionLeft, float positionBottom, int height);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:

};