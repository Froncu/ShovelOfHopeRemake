#pragma once

#include "GameObject.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class Background final : public GameObject, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	virtual ~Background() = default;

	Background(const Background& other) = default;
	Background(Background&& other) = default;
	Background& operator=(const Background& other) = default;;
	Background& operator=(Background&& other) = default;

	//	Other special methods
	Background(const Point2f& bottomLeft, const std::string& spritePath, int layer, int amountOfColumns = 1, int tileX = 1, int tileY = 1);
	Background(float positionBottom, float positionLeft, const std::string& spritePath, int layer, int amountOfColumns = 1, int tileX = 1, int tileY = 1);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:

};