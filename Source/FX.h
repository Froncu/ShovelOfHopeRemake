#pragma once

#include "GameObject.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

class FX final : public GameObject, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other


	//	Rule of 5
	virtual ~FX() = default;

	FX(const FX& other) = delete;
	FX(FX&& other) = delete;
	FX& operator=(const FX& other) = delete;
	FX& operator=(FX&& other) = delete;

	//	Other special methods
	FX(const Point2f& center, const std::string& spritePath, int amountOfColumns, int layer, float frameTime = 0.05f, bool isFlipped = false);
	FX(float centerX, float centerY, const std::string& spritePath, int amountOfColumns, int layer, float frameTime = 0.05f, bool isFlipped = false);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:
	//	SpriteAnimator component
	virtual void OnColumnChange(int currentColumnIndex) override;
};