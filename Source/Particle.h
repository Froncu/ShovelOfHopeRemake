#pragma once

#include "GameObject.h"
#include "Rigidbody.h"
#include "SimpleSprite.h"

class Particle final : public GameObject, public Rigidbody, public SimpleSprite
{
public:
	//	Other


	//	Rule of 5
	~Particle() = default;

	Particle(const Particle& other) = delete;
	Particle(Particle&& other) = delete;
	Particle& operator=(const Particle& other) = delete;
	Particle& operator=(Particle&& other) = delete;

	//	Other special methods
	Particle(const Point2f& center, const std::string& spritePath, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));
	Particle(float centerX, float centerY, const std::string& spritePath, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));
	Particle(const Point2f& center, const std::string& spritePath, float initialVelocityX, float initialVelocityY);
	Particle(float centerX, float centerY, const std::string& spritePath, float initialVelocityX, float initialVelocityY);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:

};