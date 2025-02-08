#pragma once

#include "GameObject.h"
#include "KinematicCollider.h"
#include "HurtBox.h"

#include <set>

class DestructiveBlock;
class Destructive final : public GameObject
{
public:
	//	Other


	//	Rule of 5
	~Destructive() = default;

	Destructive(const Destructive& other) = delete;
	Destructive(Destructive&& other) = delete;
	Destructive& operator=(const Destructive& other) = delete;
	Destructive& operator=(Destructive&& other) = delete;

	//	Other special methods
	Destructive(const Point2f& bottomLeft, int width, int height, std::initializer_list<GameObject*> pGameObjectsToDrop, bool closeLeft = true, bool closeHigherTop = true, bool closeLowerTop = true, bool closeRight = true, bool closeBottom = true);
	Destructive(float positionLeft, float positionBottom, int width, int height, std::initializer_list<GameObject*> pGameObjectsToDrop, bool closeLeft = true, bool closeHigherTop = true, bool closeLowerTop = true, bool closeRight = true, bool closeBottom = true);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:


private:
	//	GameObject component
	virtual void Update(float elapsedSeconds) override;

	void AddDestructiveBlock(DestructiveBlock* pDestructiveBlock);

	void DestroyNext();

	std::vector<GameObject*> m_vpGameObjectsToDrop;

	bool m_CheckForHurt;

	std::vector<DestructiveBlock*> m_vpDestructiveBlocks, m_vpDestroyed;
	std::set<DestructiveBlock*> m_spNextToDestroy;

	const float m_DeltaDestroySeconds;
	float m_AccumulatedDestroySeconds;
};