#include "pch.h"
#include "Destructive.h"

#include "DestructiveBlock.h"

#include "FX.h"
#include "Camera.h"

#include "utils.h"

#include "SoundManager.h"

#include <algorithm>

#pragma region Constructors/Destructor
Destructive::Destructive(const Point2f& bottomLeft, int width, int height, std::initializer_list<GameObject*> pGameObjectsToDrop, bool closeLeft, bool closeHigherTop, bool closeLowerTop, bool closeRight, bool closeBottom) :
	GameObject(bottomLeft.x + width * 16.0f / 2, bottomLeft.y + height * 16.0f / 2),

	m_vpGameObjectsToDrop{ pGameObjectsToDrop },

	m_CheckForHurt{ true },

	m_vpDestructiveBlocks{}, m_vpDestroyed{},
	m_spNextToDestroy{},

	m_DeltaDestroySeconds{ 0.1f },
	m_AccumulatedDestroySeconds{}
{
	if (height > 0 && width > 0)
	{
		if (closeHigherTop) closeLowerTop = true;

		for (int topBlocks{ 1 }; topBlocks < (width - 1); ++topBlocks)
		{
			AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + topBlocks * 16.0f, bottomLeft.y + (height - 1) * 16.0f, closeHigherTop ? 1 : closeLowerTop ? 4 : 7 });

			if (height > 1) AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + topBlocks * 16.0f, bottomLeft.y + (height - 2) * 16.0f, closeLowerTop && closeHigherTop ? 4 : 7 });

			for (int filler{ 1 }; filler < height - 2; ++filler)
				AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + topBlocks * 16.0f, bottomLeft.y + filler * 16.0f, 7 });

			if (height > 2) AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + topBlocks * 16.0f, bottomLeft.y, closeBottom ? 10 : 7 });
		}

		AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x, bottomLeft.y + (height - 1) * 16.0f, closeLeft ? closeHigherTop ? 0 : closeLowerTop ? 3 : 6 : closeHigherTop ? 1 : closeLowerTop ? 4 : 7 });
		AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + (width - 1) * 16.0f, bottomLeft.y + (height - 1) * 16.0f, closeRight ? closeHigherTop ? 2 : closeLowerTop ? 5 : 8 : closeHigherTop ? 1 : closeLowerTop ? 4 : 7 });

		if (height > 1)
		{
			AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x, bottomLeft.y + (height - 2) * 16.0f, closeLeft ? closeLowerTop && closeHigherTop ? 3 : 6 : closeLowerTop && closeHigherTop ? 4 : 7 });
			AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + (width - 1) * 16.0f, bottomLeft.y + (height - 2) * 16.0f, closeRight ? closeLowerTop && closeHigherTop ? 5 : 8 : closeLowerTop && closeHigherTop ? 4 : 7 });
		}

		for (int filler{ 1 }; filler < height - 2; ++filler)
		{
			AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x, bottomLeft.y + filler * 16.0f, closeLeft ? 6 : 7 });
			AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + (width - 1) * 16.0f, bottomLeft.y + filler * 16.0f, closeRight ? 8 : 7 });
		}

		if (height > 2)
		{
			AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x, bottomLeft.y, closeBottom ? closeLeft ? 9 : 10 : closeLeft ? 6 : 7 });
			AddDestructiveBlock(new DestructiveBlock{ bottomLeft.x + (width - 1) * 16.0f, bottomLeft.y, closeBottom ? closeRight ? 11 : 10 : closeRight ? 8 : 7 });
		}
	}
	else
	{
		std::cout << "Destructive at location " << m_RootCenter.x << ", " << m_RootCenter.y << " is too small";
		GameObject::Delete();
	}

	if (m_vpGameObjectsToDrop.size())
	{
		for (GameObject* const pGameObjectToDrop : m_vpGameObjectsToDrop)
		{
			GameObject::AddGameObject(pGameObjectToDrop);

			std::cout << "Destructive: object to drop outside of bounds" << std::endl;
		}
	}

	m_vpGameObjectsToDrop.clear();
}
Destructive::Destructive(float positionLeft, float positionBottom, int width, int height, std::initializer_list<GameObject*> pGameObjectsToDrop, bool closeLeft, bool closeHigherTop, bool closeLowerTop, bool closeRight, bool closeBottom)	:
	Destructive(Point2f(positionLeft, positionBottom), width, height, pGameObjectsToDrop, closeLeft, closeHigherTop, closeLowerTop, closeRight, closeBottom)
{
}
#pragma endregion Constructors/Destructor



#pragma region Components
void Destructive::Update(float elapsedSeconds)
{
	if (m_CheckForHurt)
	{
		std::vector<DestructiveBlock> vToDelete{};
		for (int index{}; index < m_vpDestructiveBlocks.size(); ++index)
		{
			DestructiveBlock* pDestructiveBlock{ m_vpDestructiveBlocks[index] };
			if (pDestructiveBlock->m_WasHurt)
			{
				pDestructiveBlock->GameObject::Delete();
				GameObject::AddGameObject(new FX{ pDestructiveBlock->m_RootCenter, "Resources/FX/MoneyPoofSmall.png", 7, 11 });

				m_spNextToDestroy.insert(pDestructiveBlock);

				m_CheckForHurt = false;
			}
		}

		if (!m_CheckForHurt)
		{
			SoundManager::PlayEffect("Resources/Audio/WallDestroy.wav", false);
			DestroyNext();
		}
	}
	else
	{
		m_AccumulatedDestroySeconds += elapsedSeconds;
	}

	if (m_AccumulatedDestroySeconds >= m_DeltaDestroySeconds)
	{
		m_AccumulatedDestroySeconds -= m_DeltaDestroySeconds;

		DestroyNext();
	}
}
#pragma endregion Components



#pragma region PriveateMethods
void Destructive::AddDestructiveBlock(DestructiveBlock* pDestructiveBlock)
{
	const Rectf destructiveBlock{ pDestructiveBlock->m_RootCenter.x - 8.0f, pDestructiveBlock->m_RootCenter.y - 8.0f, 16.0f, 16.0f };
	
	for (GameObject* const pTestGameObjectToDrop : m_vpGameObjectsToDrop)
	{
		if (pTestGameObjectToDrop && utils::IsPointInRect(pTestGameObjectToDrop->GetRootCenter(), destructiveBlock))
		{
			pDestructiveBlock->m_pGameObjectToDrop = pTestGameObjectToDrop;

			m_vpGameObjectsToDrop.erase(std::find(m_vpGameObjectsToDrop.begin(), m_vpGameObjectsToDrop.end(), pTestGameObjectToDrop));

			break;
		}
	}

	GameObject::AddGameObject(pDestructiveBlock);
	m_vpDestructiveBlocks.push_back(pDestructiveBlock);
}

void Destructive::DestroyNext()
{
	for (DestructiveBlock* pDestructiveBlock : m_spNextToDestroy)
	{
		pDestructiveBlock->GameObject::Delete();
		GameObject::AddGameObject(new FX{ pDestructiveBlock->m_RootCenter, "Resources/FX/MoneyPoofSmall.png", 7, 11 });

		if (pDestructiveBlock->m_pGameObjectToDrop)
		{
			GameObject::AddGameObject(pDestructiveBlock->m_pGameObjectToDrop);

			pDestructiveBlock->m_pGameObjectToDrop = nullptr;
		}

		m_vpDestroyed.push_back(pDestructiveBlock);

		m_vpDestructiveBlocks.erase(std::find(m_vpDestructiveBlocks.begin(), m_vpDestructiveBlocks.end(), pDestructiveBlock));
	}

	m_spNextToDestroy.clear();

	for (DestructiveBlock*& pDestructiveBlockDestroyed : m_vpDestroyed)
	{
		const Point2f& destroyedCenter{ pDestructiveBlockDestroyed->m_RootCenter };
		for (DestructiveBlock* pDestructiveBlockChecking : m_vpDestructiveBlocks)
		{
			const Point2f& checkingCenter{ pDestructiveBlockChecking->m_RootCenter };

			if (abs(checkingCenter.x - destroyedCenter.x) < 24.0f && abs(checkingCenter.y - destroyedCenter.y) < 24.0f)
			{
				m_spNextToDestroy.insert(pDestructiveBlockChecking);
			}
		}
	}

 	m_vpDestroyed.clear();

	if (!m_vpDestructiveBlocks.size())
	{
		Camera::SetShaking(false);
		GameObject::Delete();
	}
	else
	{
		Camera::SetShaking(true);
	}
}
#pragma endregion PriveateMethods