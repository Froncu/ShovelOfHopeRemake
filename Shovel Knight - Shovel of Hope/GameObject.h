#pragma once

#include <vector>

class GameObject
{
public:
	//	Other
	friend class GameObjectManager;
	friend class Camera;

	//	Rule of 5
	virtual ~GameObject() = default;

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	//	Other special methods


	//	Methods


	//	Setters
	

	//	Getters
	const Point2f& GetRootCenter() const;

protected:
	GameObject(const Point2f& rootCenter = Point2f(0.0f, 0.0f), bool onlyHandleInView = false);
	GameObject(float rootCenterX, float rootCenterY, bool onlyHandleInView = false);

	void Delete(GameObject* const pRespawnGameObject = nullptr);
	void AddGameObject(GameObject* pGameObject);

	Point2f m_RootCenter;
	const Point2f m_SpawnCenter;

private:
	virtual void Update(float elapsedSeconds);

	static std::vector<GameObject*> m_vpDROPPED_GAME_OBJECTS;

	bool m_ShouldBeDeleted, m_OnlyHandleInView;

	float m_LargestRootXOffset, m_LargestRootYOffset;
};