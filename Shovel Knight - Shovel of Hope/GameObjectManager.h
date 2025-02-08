#pragma once

#include <vector>

#include "utils.h"

class GameObject;
class DynamicCollider;
class KinematicCollider;
class GameObjectManager final
{
public:
	//	Rule of 5
	~GameObjectManager() = delete;

	GameObjectManager(const GameObjectManager& other) = delete;
	GameObjectManager(GameObjectManager&& other) = delete;
	GameObjectManager& operator=(const GameObjectManager& other) = delete;
	GameObjectManager& operator=(GameObjectManager&& other) = delete;

	//	Other special methods
	GameObjectManager() = delete;

	//	Methods
	static void Manage(float elapsedSeconds, bool onlyManageSprites = false);
	static void Draw(bool drawDebugLines = false);

	static void AddGameObject(GameObject* pGameObject);

	static void DeleteAllGameObjects();

	//	Setters


	//	Getters


protected:


private:
	static void ManageGameOjects(float elapsedSeconds);

	static void ManageSprites(float elapsedSeconds);

	static void ManagePickups(float elapsedSeconds);

	static void ManageHits(float elapsedSeconds);

	static void ManageInteractions(float elapsedSeconds);

	static void ManageRigidbodies(float elapsedSeconds);

	static void ManageCollisions(float elapsedSeconds);
	static void CheckHitInfo(DynamicCollider* const pDynamicCollider, const KinematicCollider* const pKinematicCollider, const utils::HitInfo& hitInfo, float elapsedSeconds);

	static void SetLargestOffsets(GameObject* const pGameObject);

	static bool IsInCameraView(const GameObject* const pGameObject);
	static bool IsInAnyCameraZone(const GameObject* const pGameObject);
	static Rectf GetGameObjectBoundingRectangle(const GameObject* const pGameObject);

	static std::vector<GameObject*> m_vpGAME_OBJECTS;
};