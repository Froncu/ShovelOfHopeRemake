#pragma once

class Rigidbody
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~Rigidbody() = default;

	Rigidbody(const Rigidbody& other) = delete;
	Rigidbody(Rigidbody&& other) = delete;
	Rigidbody& operator=(const Rigidbody& other) = delete;
	Rigidbody& operator=(Rigidbody&& other) = delete;

	//	Other special methods


	//	Methods
	

	//	Setters
	

	//	Getters


protected:
	Rigidbody(Point2f& rootCenter, float gravityMultiplier = 1.0f, const Vector2f& maxVelocity = Vector2f(100.0f, 360.0f));

	void SetGravityMultiplier(float gravityMultiplier);
	
	const Vector2f m_MaxVelocity;
	Vector2f m_Velocity;

private:
	static const float m_GRAVITY;

	Point2f* const m_pRootCenter;

	float m_GravityMultiplier;
};