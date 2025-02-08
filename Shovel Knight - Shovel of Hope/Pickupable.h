#pragma once

#include "GameObject.h"
#include "DynamicCollider.h"
#include "Rigidbody.h"
#include "SimpleSprite.h"
#include "SpriteAnimator.h"

#include <map>

class Pickupable final : public GameObject, public DynamicCollider, public Rigidbody, public SimpleSprite, public SpriteAnimator
{
public:
	//	Other
	friend class GameObjectManager;

	enum class Type
	{
		Empty = 0,
		GreyGem = 1,
		BlueGem = 5,
		GreenGem = 10,
		GoldGem = 20,
		RedGem = 50,
		MagentaGem = 200,
		Carrot = 4,
		Apple = 6,
		Chicken = 2
	};

	//	Rule of 5
	~Pickupable() = default;

	Pickupable(const Pickupable& other) = delete;
	Pickupable(Pickupable&& other) = delete;
	Pickupable& operator=(const Pickupable& other) = delete;
	Pickupable& operator=(Pickupable&& other) = delete;

	//	Other special methods
	Pickupable(const Point2f& center, Type type, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));
	Pickupable(float centerX, float centerY, Type type, const Vector2f& initialVelocity = Vector2f(0.0f, 0.0f));
	Pickupable(const Point2f& center, Type type, float initialVelocityX, float initialVelocityY);
	Pickupable(float centerX, float centerY, Type type, float initialVelocityX, float initialVelocityY);

	Pickupable(const Point2f& center, int value);
	Pickupable(float centerX, float centerY, int value);

	//	Methods


	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	//	DynamicCollider component
	virtual void OnCollision(const utils::HitInfo& hitInfo) override;

	void OnPickup();

	static std::map<Type, std::string> m_mTYPESPRITEPATH;

	Rectf m_LocalPickupArea;

	bool m_Despawns, m_CanBePickedUp;

	int m_Value;
	bool m_Heals;

	int m_AmountOfFX;

	const float m_MaxPickupableSeconds;
	float m_AccumulatedSeconds;

	bool m_WasAudioPlayed;

	Point2f m_DBagTarget;
};