#include "pch.h"
#include "GameObject.h"

#include "utils.h"

#pragma region StaticDataMembers
std::vector<GameObject*> GameObject::m_vpDROPPED_GAME_OBJECTS{};
#pragma region StaticDataMembers



#pragma region Constructors/Destructor
GameObject::GameObject(const Point2f& rootCenter, bool onlyHandleInView) :
	m_RootCenter{ rootCenter },
	m_SpawnCenter{ m_RootCenter },

	m_ShouldBeDeleted{}, m_OnlyHandleInView{ onlyHandleInView },

	m_LargestRootXOffset{}, m_LargestRootYOffset{}
{
}

GameObject::GameObject(float rootCenterX, float rootCenterY, bool onlyHandleInView) :
	GameObject{ Point2f(rootCenterX, rootCenterY), onlyHandleInView }
{
}
#pragma endregion Constructors/Destructor



#pragma region PublicMethods
const Point2f& GameObject::GetRootCenter() const
{
	return m_RootCenter;
}
#pragma endregion PublicMethods



#pragma region ProtectedMethods
void GameObject::Update(float elapsedSeconds)
{

}

void GameObject::Delete(GameObject* const pRespawnGameObject)
{
	m_ShouldBeDeleted = true;
}

void GameObject::AddGameObject(GameObject* pGameObject)
{
	m_vpDROPPED_GAME_OBJECTS.push_back(pGameObject);
}
#pragma endregion ProtectedMethods