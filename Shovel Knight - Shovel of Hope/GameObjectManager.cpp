#include "pch.h"
#include "GameObjectManager.h"

#include "GameObject.h"

#include "Camera.h"

#include "SimpleSprite.h"
#include "SpriteAnimator.h"

#include "Pickupper.h"
#include "Pickupable.h"

#include "HitBox.h"
#include "HurtBox.h"

#include "Interactor.h"
#include "Interactable.h"

#include "Rigidbody.h"

#include "DynamicCollider.h"
#include "KinematicCollider.h"

#include "ShovelKnight.h"

//#define DEBUG

#pragma region StaticVariables
std::vector<GameObject*> GameObjectManager::m_vpGAME_OBJECTS{};
#pragma endregion StaticVariables



#pragma region PublicMethods
void GameObjectManager::Manage(float elapsedSeconds, bool onlyManageSprites)
{
	if (!onlyManageSprites) ManageGameOjects(elapsedSeconds);

	ManageSprites(elapsedSeconds);

	if (!onlyManageSprites)
	{
		ManagePickups(elapsedSeconds);

		ManageInteractions(elapsedSeconds);

		ManageRigidbodies(elapsedSeconds);

		ManageHits(elapsedSeconds);

		ManageCollisions(elapsedSeconds);
	}
}

void GameObjectManager::AddGameObject(GameObject* pGameObject)
{
	GameObject::m_vpDROPPED_GAME_OBJECTS.push_back(pGameObject);
}

void GameObjectManager::Draw(bool drawDebugLines)
{
	const Color4f
		whiteColor{ 1.0f, 1.0f, 1.0f, 1.0f },
		hitBoxColor{ 1.0f, 0.0f, 0.0f, 1.0f },
		hurtBoxColor{ 0.0f, 1.0f, 0.0f, 1.0f },
		dynamicCollisionBoxColor{ 0.0f, 0.0f, 1.0f, 1.0f },
		kinematicCollisionBoxColor{ 1.0f, 0.0f, 1.0f, 1.0f },
		interactorColor{ 1.0f, 1.0f, 0.0f, 1.0f },
		interactableColor{ whiteColor };

	std::vector<const SimpleSprite*> vpSpritesToDraw{};
	int highestLayer{};

	for (GameObject* const pSpriteGameObject : m_vpGAME_OBJECTS)
	{
		if (!pSpriteGameObject-> m_ShouldBeDeleted && IsInCameraView(pSpriteGameObject))
		{
			SimpleSprite* const pSprite{ dynamic_cast<SimpleSprite* const>(pSpriteGameObject) };
			if (pSprite)
			{
				vpSpritesToDraw.push_back(pSprite);
				if (highestLayer < pSprite->m_Layer)
				{
					highestLayer = pSprite->m_Layer;
				}
			}
		}
	}

	const float distanceLayer1{ 1.0f }, distanceLayer2{ 7.0f }, distanceLayer3{ 8.0f }, distanceLayer4{ 9.0f };

	for (int index{}; index <= highestLayer; ++index)
	{
		for (const SimpleSprite* const pSprite : vpSpritesToDraw)
		{
			if (pSprite->m_Layer == index)
			{
				glPushMatrix();

				glScalef(Camera::GetZoom(), Camera::GetZoom(), 1);

				switch (index)
				{
				case 0:
					glTranslatef(0, -Camera::GetShakeOffsets().y, 0);
					glTranslatef(-Camera::GetShakeOffsets().x, 0, 0);
					pSprite->Draw();
					break;

				case 1:
					glTranslatef(0, -(Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y), 0);
					glTranslatef(-(Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer1), 0, 0);
					pSprite->Draw();
					break;

				case 2:
					glTranslatef(0, -(Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y), 0);
					glTranslatef(-(Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer2), 0, 0);
					pSprite->Draw();
					break;

				case 3:
					glTranslatef(0, -(Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y), 0);
					glTranslatef(-(Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer3), 0, 0);
					pSprite->Draw();
					break;

				case 4:
					glTranslatef(0, -(Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y), 0);
					glTranslatef(-(Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer4), 0, 0);
					pSprite->Draw();
					break;

				default:
					glTranslatef(0, -(Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y), 0);
					glTranslatef(-(Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x), 0, 0);
					pSprite->Draw();

#undef DEBUG
#ifdef DEBUG
					for (const GameObject* const pGameObject : m_vpGAME_OBJECTS)
					{
						if (
							pGameObject->m_RootCenter.x > Camera::GetTransformedViewPort().left
							&&
							pGameObject->m_RootCenter.x < Camera::GetTransformedViewPort().left + Camera::GetTransformedViewPort().width
							&&
							pGameObject->m_RootCenter.y > Camera::GetTransformedViewPort().bottom
							&&
							pGameObject->m_RootCenter.y < Camera::GetTransformedViewPort().bottom + Camera::GetTransformedViewPort().height
							)
						{
							const HitBox* const pHitBoxGameObject{ dynamic_cast<const HitBox* const>(pGameObject) };
							if (pHitBoxGameObject)
							{
								utils::SetColor(hitBoxColor);

								const Point2f& rootCenter{ *pHitBoxGameObject->m_pRootCenter };

								for (const LocalHitBox& localHitBoxStruct : pHitBoxGameObject->m_vLocalHitBoxes)
								{
									if (localHitBoxStruct.isActive)
									{
										const Rectf& localHitBox{ localHitBoxStruct.localHitBox };
										const Rectf hitBox{ rootCenter.x + localHitBox.left - localHitBox.width / 2, rootCenter.y + localHitBox.bottom - localHitBox.height / 2, localHitBox.width, localHitBox.height };

										utils::DrawRect(hitBox, 2.0f);
									}
								}

								utils::SetColor(whiteColor);
							}

							const HurtBox* const pHurtBoxGameObject{ dynamic_cast<const HurtBox* const>(pGameObject) };
							if (pHurtBoxGameObject && pHurtBoxGameObject->m_IsActive)
							{
								utils::SetColor(hurtBoxColor);

								const Point2f& rootCenter{ *pHurtBoxGameObject->m_pRootCenter };
								for (const LocalHurtBox& localHurtBoxStruct : pHurtBoxGameObject->m_vLocalHurtBoxes)
								{
									const Rectf& localHurtBox{ localHurtBoxStruct.localHurtBox };
									const Rectf hurtBox{ rootCenter.x + localHurtBox.left - localHurtBox.width / 2, rootCenter.y + localHurtBox.bottom - localHurtBox.height / 2, localHurtBox.width, localHurtBox.height };

									utils::DrawRect(hurtBox.left + 2 / Camera::GetZoom(), hurtBox.bottom + 2 / Camera::GetZoom(), hurtBox.width - 4 / Camera::GetZoom(), hurtBox.height - 4 / Camera::GetZoom(), 2.0f);
								}

								utils::SetColor(whiteColor);
							}

							const DynamicCollider* const pDynamiColliderGameObject{ dynamic_cast<const DynamicCollider* const>(pGameObject) };
							if (pDynamiColliderGameObject)
							{
								const Point2f& rootCenter{ *pDynamiColliderGameObject->m_pRootCenter };
								const Rectf& localCollisionBox{ pDynamiColliderGameObject->m_LocalCollisionBox };
								const Rectf collisionBox{ rootCenter.x + localCollisionBox.left - localCollisionBox.width / 2, rootCenter.y + localCollisionBox.bottom - localCollisionBox.height / 2, localCollisionBox.width, localCollisionBox.height };

								utils::SetColor(dynamicCollisionBoxColor);
								utils::DrawRect(collisionBox.left + 4 / Camera::GetZoom(), collisionBox.bottom + 4 / Camera::GetZoom(), collisionBox.width - 8 / Camera::GetZoom(), collisionBox.height - 8 / Camera::GetZoom(), 2.0f);
								utils::SetColor(whiteColor);
							}

							const KinematicCollider* const pKinematicColliderGameObject{ dynamic_cast<const KinematicCollider* const>(pGameObject) };
							if (pKinematicColliderGameObject)
							{
								utils::SetColor(kinematicCollisionBoxColor);
								if (pKinematicColliderGameObject->m_pRootCenter)
								{
									const Point2f& rootCenter{ *pKinematicColliderGameObject->m_pRootCenter };
									const float& width{ pKinematicColliderGameObject->m_Width }, & height{ pKinematicColliderGameObject->m_Height };
									const Rectf collisionBox{ rootCenter.x - width / 2, rootCenter.y - height / 2, width, height };

									utils::DrawRect(collisionBox, 2.0f);
								}
								else
								{
									utils::DrawPolygon(*pKinematicColliderGameObject->m_pvVertices, true, 2.0f);
								}
								utils::SetColor(whiteColor);
							}

							const Interactor* const pInteractorGameObject{ dynamic_cast<const Interactor* const>(pGameObject) };
							if (pInteractorGameObject)
							{
								const Point2f& rootCenterInteractor{ *pInteractorGameObject->m_pRootCenter };
								const Rectf& interactorLocalInteractArea{ pInteractorGameObject->m_LocalInteractArea };
								const Rectf interactorWorldInteractArea{ rootCenterInteractor.x + interactorLocalInteractArea.left - interactorLocalInteractArea.width / 2, rootCenterInteractor.y + interactorLocalInteractArea.bottom - interactorLocalInteractArea.height / 2, interactorLocalInteractArea.width, interactorLocalInteractArea.height };

								utils::SetColor(interactorColor);
								utils::DrawRect(interactorWorldInteractArea, 2.0f);
								utils::SetColor(whiteColor);
							}

							const Interactable* const pInteractableGameObject{ dynamic_cast<const Interactable* const>(pGameObject) };
							if (pInteractableGameObject)
							{
								const Point2f& rootCenterInteractable{ *pInteractableGameObject->m_pRootCenter };
								const Rectf& interactableLocalLockArea{ pInteractableGameObject->m_LocalLockArea };
								const Rectf interactableWorldLockArea{ rootCenterInteractable.x + interactableLocalLockArea.left - interactableLocalLockArea.width / 2, rootCenterInteractable.y + interactableLocalLockArea.bottom - interactableLocalLockArea.height / 2, interactableLocalLockArea.width, interactableLocalLockArea.height };

								utils::SetColor(interactableColor);
								utils::DrawRect(interactableWorldLockArea, 2.0f);
								utils::SetColor(whiteColor);
							}
						}
					}
#endif DEBUG
#define DEBUG
				}

				glPopMatrix();
			}
		}
	}
}

void GameObjectManager::DeleteAllGameObjects()
{
	for (GameObject* pGameObject : m_vpGAME_OBJECTS)
	{
		delete pGameObject;
	}

	m_vpGAME_OBJECTS.clear();
}
#pragma endregion PublicMethods



#pragma region PrivateMethods
void GameObjectManager::ManageGameOjects(float elapsedSeconds)
{
	for (GameObject* const pDroppedGameObject : GameObject::m_vpDROPPED_GAME_OBJECTS)
	{
		m_vpGAME_OBJECTS.push_back(pDroppedGameObject);

		SetLargestOffsets(pDroppedGameObject);
	}

	GameObject::m_vpDROPPED_GAME_OBJECTS.clear();

	for (GameObject*& pGameObject : m_vpGAME_OBJECTS)
	{
		if (!pGameObject->m_ShouldBeDeleted && IsInCameraView(pGameObject))
			pGameObject->Update(elapsedSeconds);
		
		if (pGameObject->m_ShouldBeDeleted || !IsInAnyCameraZone(pGameObject))
		{
			ShovelKnight* pPlayer{ dynamic_cast<ShovelKnight*>(pGameObject) };
			if (!pPlayer)
			{
				delete pGameObject;
				pGameObject = nullptr;
			}
		}
	}

	std::vector<GameObject*>::iterator newEnd{ remove(m_vpGAME_OBJECTS.begin(), m_vpGAME_OBJECTS.end(), nullptr) };
	m_vpGAME_OBJECTS.assign(m_vpGAME_OBJECTS.begin(), newEnd);
}

void GameObjectManager::ManageSprites(float elapsedSeconds)
{
	for (GameObject*& pSpriteGameObject : m_vpGAME_OBJECTS)
	{
		if (!pSpriteGameObject-> m_ShouldBeDeleted && IsInCameraView(pSpriteGameObject))
		{
			SimpleSprite* const pSprite{ dynamic_cast<SimpleSprite* const>(pSpriteGameObject) };
			if (pSprite)
			{
				int& blinkAmount{ pSprite->m_BlinkAmount };
				bool& shouldBeDrawn{ pSprite->m_ShouldBeDrawn };

				if (blinkAmount)
				{
					float& accumulatedSeconds{ pSprite->m_BlinkAccumulatedSeconds };
					const float& frameSeconds{ pSprite->m_BlinkFrameSeconds };

					accumulatedSeconds += elapsedSeconds;

					if (accumulatedSeconds < 0.0f) accumulatedSeconds = 0.0f;

					if (accumulatedSeconds >= frameSeconds)
					{
						const int multiplier{ int(accumulatedSeconds / frameSeconds) };

						blinkAmount -= 1 * multiplier;

						accumulatedSeconds -= frameSeconds * multiplier;

						shouldBeDrawn = !shouldBeDrawn;

						if (blinkAmount <= 0)
						{
							blinkAmount = 0;
							shouldBeDrawn = true;
						}
					}
				}

				SpriteAnimator* const pSpriteAnimator{ dynamic_cast<SpriteAnimator* const>(pSprite) };
				if (pSpriteAnimator)
				{
					Rectf& sourceRectangle{ pSprite->m_SourceRectangle };
					const float& textureWidth{ pSprite->m_pTexture->GetWidth() }, & textureHeight{ pSprite->m_pTexture->GetHeight() };
					const int& columns{ pSpriteAnimator->m_Columns }, & rows{ pSpriteAnimator->m_Rows };

					float& accumulatedSeconds{ pSpriteAnimator->m_AccumulatedSeconds }, & frameSeconds{ pSpriteAnimator->m_FrameSeconds };

					int& currentRowIndex{ pSpriteAnimator->m_CurrentRowIndex }, & currentRowSize{ pSpriteAnimator->m_CurrentRowSize };
					int& lastRowIndex{ pSpriteAnimator->m_LastRowIndex }, & lastRowSize{ pSpriteAnimator->m_LastRowSize };
					bool& changeRows{ pSpriteAnimator->m_ChangeRows }, & playCurrentRowOnce{ pSpriteAnimator->m_PlayCurrentRowOnce };

					int& currentColumnIndex{ pSpriteAnimator->m_CurrentColumnIndex };


					sourceRectangle.width = textureWidth / columns;
					sourceRectangle.height = textureHeight / rows;

					accumulatedSeconds += elapsedSeconds;;

					if (accumulatedSeconds >= frameSeconds)
					{
						accumulatedSeconds -= frameSeconds;
						++currentColumnIndex;
						currentColumnIndex %= currentRowSize;

						sourceRectangle.left = currentColumnIndex * sourceRectangle.width;

						if (!currentColumnIndex)
						{
							if (playCurrentRowOnce)
							{
								currentRowIndex = lastRowIndex;
								currentRowSize = lastRowSize;
								changeRows = true;

								playCurrentRowOnce = false;
							}
						}

						pSpriteAnimator->OnColumnChange(currentColumnIndex);
					}

					if (changeRows)
					{
						sourceRectangle.bottom = (1 + currentRowIndex) * sourceRectangle.height;

						accumulatedSeconds = 0;
						currentColumnIndex = 0;
						sourceRectangle.left = currentColumnIndex * sourceRectangle.width;

						if (!playCurrentRowOnce)
						{
							lastRowIndex = currentRowIndex;
							lastRowSize = currentRowSize;
						}

						changeRows = false;
					}
				}
			}
		}
	}
}

void GameObjectManager::ManagePickups(float elapsedSeconds)
{
	for (GameObject* const pPickupperGameObject : m_vpGAME_OBJECTS)
	{
		if (!pPickupperGameObject-> m_ShouldBeDeleted && IsInCameraView(pPickupperGameObject))
		{
			Pickupper* const pPickupper{ dynamic_cast<Pickupper* const>(pPickupperGameObject) };
			if (pPickupper)
			{
				for (GameObject* const pPickupableGameObject : m_vpGAME_OBJECTS)
				{
					if (!pPickupableGameObject-> m_ShouldBeDeleted && IsInCameraView(pPickupableGameObject))
					{
						Pickupable* const pPickupable{ dynamic_cast<Pickupable* const>(pPickupableGameObject) };
						if (pPickupable)
						{
							if (pPickupable->m_CanBePickedUp)
							{
								const Point2f& pickupperRootCenter{ *pPickupper->m_pRootCenter };
								const Rectf& pickupperLocalPickupArea{ pPickupper->m_LocalPickupArea };
								const Rectf pickupperWorldPickupArea{ pickupperRootCenter.x + pickupperLocalPickupArea.left - pickupperLocalPickupArea.width / 2, pickupperRootCenter.y + pickupperLocalPickupArea.bottom - pickupperLocalPickupArea.height / 2, pickupperLocalPickupArea.width, pickupperLocalPickupArea.height };

								const Point2f& pickupableRootCenter{ pPickupable->m_RootCenter };
								const Rectf& pickupableLocalPickupArea{ pPickupable->m_LocalPickupArea };
								const Rectf pickupbleWorldPickupArea{ pickupableRootCenter.x + pickupableLocalPickupArea.left - pickupableLocalPickupArea.width / 2, pickupableRootCenter.y + pickupableLocalPickupArea.bottom - pickupableLocalPickupArea.height / 2, pickupableLocalPickupArea.width, pickupableLocalPickupArea.height };

								if (utils::IsOverlapping(pickupperWorldPickupArea, pickupbleWorldPickupArea))
								{
 									pPickupper->OnPickup(pPickupable->m_Value, pPickupable->m_Heals);
									pPickupable->OnPickup();
								}
							}
						}
					}
				}
			}
		}
	}
}

void GameObjectManager::ManageHits(float elapsedSeconds)
{
	static std::vector<HurtBox*> vpHURTBOXES_ON_COOLDOWN{};

	for (GameObject* const pHitBoxGameObject : m_vpGAME_OBJECTS)
	{
		if (!pHitBoxGameObject-> m_ShouldBeDeleted && IsInCameraView(pHitBoxGameObject))
		{
			HitBox* const pHitBox{ dynamic_cast<HitBox* const>(pHitBoxGameObject) };
			if (pHitBox)
			{
				bool onHitCalled{};
				const std::vector<LocalHitBox>& vLocalHitBoxes{ pHitBox->m_vLocalHitBoxes };

				for (int hitBoxIndex{}; hitBoxIndex < vLocalHitBoxes.size(); ++hitBoxIndex)
				{ 
					const LocalHitBox& localHitBoxStruct{ vLocalHitBoxes[hitBoxIndex] };

					if (localHitBoxStruct.isActive)
					{
						for (GameObject* const pHurtBoxGameObject : m_vpGAME_OBJECTS)
						{
							if (!pHurtBoxGameObject-> m_ShouldBeDeleted && pHitBoxGameObject != pHurtBoxGameObject && IsInCameraView(pHurtBoxGameObject))
							{
								HurtBox* const pHurtBox{ dynamic_cast<HurtBox* const>(pHurtBoxGameObject) };
								if (pHurtBox && ((pHurtBox->m_IsActive && !pHurtBox->m_IsOnCooldown) || localHitBoxStruct.damage == 999))
								{
									const std::vector<LocalHurtBox>& vLocalHurtBoxes{ pHurtBox->m_vLocalHurtBoxes };
									for (int hurtBoxIndex{}; hurtBoxIndex < vLocalHurtBoxes.size(); ++hurtBoxIndex)
									{
										const LocalHurtBox& localHurtBoxStruct{ vLocalHurtBoxes[hurtBoxIndex] };

										for (int hitBoxGroupNumber : localHitBoxStruct.vGroupNumbers)
										{
											for (int hurtBoxGroupNumber : localHurtBoxStruct.vGroupNumbers)
											{
												if (hitBoxGroupNumber == hurtBoxGroupNumber)
												{
													const Point2f& rootCenterHitBox{ *pHitBox->m_pRootCenter };
													const Rectf& localHitBox{ localHitBoxStruct.localHitBox };
													const Rectf worldHitBox{ rootCenterHitBox.x + localHitBox.left - localHitBox.width / 2, rootCenterHitBox.y + localHitBox.bottom - localHitBox.height / 2, localHitBox.width, localHitBox.height };

													const int& damage{ localHitBoxStruct.damage };

													const Point2f& rootCenterHurtBox{ *pHurtBox->m_pRootCenter };
													const Rectf& localHurtBox{ localHurtBoxStruct.localHurtBox };
													const Rectf worldHurtBox{ rootCenterHurtBox.x + localHurtBox.left - localHurtBox.width / 2, rootCenterHurtBox.y + localHurtBox.bottom - localHurtBox.height / 2, localHurtBox.width, localHurtBox.height };

													if (utils::IsOverlapping(worldHitBox, worldHurtBox))
													{
														Vector2f hitNormal{ -localHitBoxStruct.hitDirection };

														if (!hitNormal.x)
														{
															if (worldHitBox.left + worldHitBox.width / 2 < worldHurtBox.left + worldHurtBox.width / 2)
															{
																hitNormal.x = -1;
															}
															else
															{
																hitNormal.x = 1;
															}
														}

														const Vector2f& hurtBoxKnockBackVelocity{ localHurtBoxStruct.knockBackVelocity };

														if (!onHitCalled)
														{
															pHitBox->OnHit(hitNormal, hurtBoxKnockBackVelocity, hitBoxIndex);
														}

														pHurtBox->OnHurt(-hitNormal, damage, hurtBoxIndex);
														pHurtBox->m_IsOnCooldown = true;

														vpHURTBOXES_ON_COOLDOWN.push_back(pHurtBox);

														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	for (HurtBox* pHurtBoxOnCooldown : vpHURTBOXES_ON_COOLDOWN)
	{
		float& accumulatedCooldownSeconds{ pHurtBoxOnCooldown->m_AccumulatedCooldownSeconds };
		const float& maxCooldownSeconds{ pHurtBoxOnCooldown->m_MaxCooldownSeconds };
		bool& isOnCooldown{ pHurtBoxOnCooldown->m_IsOnCooldown };

		accumulatedCooldownSeconds += elapsedSeconds;
		if (accumulatedCooldownSeconds >= maxCooldownSeconds)
		{
			accumulatedCooldownSeconds = 0;

			isOnCooldown = false;

			std::vector<HurtBox*>::iterator newEnd{ remove(vpHURTBOXES_ON_COOLDOWN.begin(), vpHURTBOXES_ON_COOLDOWN.end(), pHurtBoxOnCooldown) };
			vpHURTBOXES_ON_COOLDOWN.assign(vpHURTBOXES_ON_COOLDOWN.begin(), newEnd);
		}
	}
}

void GameObjectManager::ManageInteractions(float elapsedSeconds)
{
	for (GameObject* const pInteractorGameObject : m_vpGAME_OBJECTS)
	{
		if (!pInteractorGameObject-> m_ShouldBeDeleted && IsInCameraView(pInteractorGameObject))
		{
			Interactor* const pInteractor{ dynamic_cast<Interactor* const>(pInteractorGameObject) };
			if (pInteractor)
			{
				for (GameObject* const pInteractableGameObject : m_vpGAME_OBJECTS)
				{
					if (!pInteractableGameObject-> m_ShouldBeDeleted && IsInCameraView(pInteractableGameObject))
					{
						Interactable* const pInteractable{ dynamic_cast<Interactable* const>(pInteractableGameObject) };
						if (pInteractable && pInteractable->m_IsActive)
						{
							const Point2f& rootCenterInteractor{ *pInteractor->m_pRootCenter };
							const Rectf& interactorLocalInteractArea{ pInteractor->m_LocalInteractArea };
							const Rectf interactorWorldInteractArea{ rootCenterInteractor.x + interactorLocalInteractArea.left - interactorLocalInteractArea.width / 2, rootCenterInteractor.y + interactorLocalInteractArea.bottom - interactorLocalInteractArea.height / 2, interactorLocalInteractArea.width, interactorLocalInteractArea.height };

							const Point2f& rootCenterInteractable{ *pInteractable->m_pRootCenter };
							const Rectf& interactableLocalLockArea{ pInteractable->m_LocalLockArea };
							const Rectf interactableWorldLockArea{ rootCenterInteractable.x + interactableLocalLockArea.left - interactableLocalLockArea.width / 2, rootCenterInteractable.y + interactableLocalLockArea.bottom - interactableLocalLockArea.height / 2, interactableLocalLockArea.width, interactableLocalLockArea.height };

							if (utils::IsOverlapping(interactorWorldInteractArea, Rectf(interactableWorldLockArea.left, interactableWorldLockArea.bottom, interactableWorldLockArea.width, interactableWorldLockArea.height)))
							{
								pInteractor->m_OnInteractEndOverlapCalled = false;
								pInteractor->OnInteractOverlap(interactableWorldLockArea);

								pInteractable->m_OnInteractEndOverlapCalled = false;
								pInteractable->OnInteractOverlap();
							}
							else
							{
								if (!pInteractable->m_OnInteractEndOverlapCalled)
								{
									pInteractable->m_OnInteractEndOverlapCalled = true;
									pInteractable->OnInteractEndOverlap();
									pInteractor->OnInteractEndOverlap();
								}
							}
						}
					}
				}
			}
		}
	}
}

void GameObjectManager::ManageRigidbodies(float elapsedSeconds)
{
	for (GameObject* const pRigidbodyGameObject : m_vpGAME_OBJECTS)
	{
		if (!pRigidbodyGameObject-> m_ShouldBeDeleted && IsInCameraView(pRigidbodyGameObject))
		{
			Rigidbody* const pRigidBody{ dynamic_cast<Rigidbody* const>(pRigidbodyGameObject) };
			if (pRigidBody)
			{
				const float& gravity{ Rigidbody::m_GRAVITY }, & gravityMultiplier{ pRigidBody->m_GravityMultiplier };
				Point2f& rootCenter{ *pRigidBody->m_pRootCenter };
				Vector2f& velocity{ pRigidBody->m_Velocity };
				const Vector2f& maxVelocity{ pRigidBody->m_MaxVelocity };

				if (abs(velocity.x) > maxVelocity.x)
				{
					velocity.x = maxVelocity.x * (velocity.x / abs(velocity.x));
				}

				if (velocity.y < -maxVelocity.y)
				{
					velocity.y = maxVelocity.y * (velocity.y / abs(velocity.y));
				}

				velocity.y += gravity * gravityMultiplier * elapsedSeconds;

				rootCenter.x += velocity.x * elapsedSeconds;
				rootCenter.y += velocity.y * elapsedSeconds;

				DynamicCollider* const pDynamicCollider{ dynamic_cast<DynamicCollider* const>(pRigidBody) };
				if (pDynamicCollider)
				{
					float& lastHitRigidbodyIntersectiontY{ pDynamicCollider->m_LastHitRigidbodyIntersectionY };
					float& dynamicColliderHeight{ pDynamicCollider->m_LocalCollisionBox.height };
					if (pDynamicCollider->m_LastHitRigidbodyIntersectionY != INFINITY)
					{
						rootCenter.y = pDynamicCollider->m_LastHitRigidbodyIntersectionY + dynamicColliderHeight / 2 - 1.0f;
					}
				}
			}
		}
	}
}

void GameObjectManager::ManageCollisions(float elapsedSeconds)
{
	for (GameObject* const pDynamicColliderGameObject : m_vpGAME_OBJECTS)
	{
		if (!pDynamicColliderGameObject-> m_ShouldBeDeleted && IsInCameraView(pDynamicColliderGameObject))
		{
			DynamicCollider* const pDynamicCollider{ dynamic_cast<DynamicCollider* const>(pDynamicColliderGameObject) };
			if (pDynamicCollider && pDynamicCollider->m_IsActive)
			{
				pDynamicCollider->m_LastHitRigidbodyIntersectionY = INFINITY;

				Point2f& dynamicRootCenter{ *pDynamicCollider->m_pRootCenter };
				const Rectf& dynamicLocalCollisionBox{ pDynamicCollider->m_LocalCollisionBox };

				std::vector<KinematicCollider*> vpKinematicColliders{};
				for (GameObject* const pKinematicColliderGameObject : m_vpGAME_OBJECTS)
				{
					if (!pKinematicColliderGameObject-> m_ShouldBeDeleted && IsInCameraView(pKinematicColliderGameObject))
					{
						KinematicCollider* const pKinematicCollider{ dynamic_cast<KinematicCollider* const>(pKinematicColliderGameObject) };
						if (pKinematicCollider && pKinematicCollider->m_IsActive)
						{
							const Rectf dynamicWorldCollisionBox{ dynamicRootCenter.x + dynamicLocalCollisionBox.left - dynamicLocalCollisionBox.width / 2, dynamicRootCenter.y + dynamicLocalCollisionBox.bottom - dynamicLocalCollisionBox.height / 2, dynamicLocalCollisionBox.width, dynamicLocalCollisionBox.height };

							Rectf kinematicWorldBoudingRectangle;

							if (pKinematicCollider->m_pRootCenter)
							{
								const Point2f& rootCenter{ *pKinematicCollider->m_pRootCenter };
								const float& width{ pKinematicCollider->m_Width }, & height{ pKinematicCollider->m_Height };

								kinematicWorldBoudingRectangle = Rectf(rootCenter.x - width / 2, rootCenter.y - height / 2, width, height);
							}
							else
							{
								const std::vector<Point2f>& vVertices{ *pKinematicCollider->m_pvVertices };

								Point2f bottomLeft{ INFINITY, INFINITY }, topRight{ -INFINITY, -INFINITY };
								for (const Point2f& vertex : vVertices)
								{
									if (vertex.x < bottomLeft.x) bottomLeft.x = vertex.x;
									if (vertex.y < bottomLeft.y) bottomLeft.y = vertex.y;

									if (vertex.x > topRight.x) topRight.x = vertex.x;
									if (vertex.y > topRight.y) topRight.y = vertex.y;
								}

								kinematicWorldBoudingRectangle = Rectf(bottomLeft.x, bottomLeft.y, topRight.x - bottomLeft.x, topRight.y - bottomLeft.y);
							}

							if (utils::IsOverlapping(kinematicWorldBoudingRectangle, dynamicWorldCollisionBox))
							{
								vpKinematicColliders.push_back(pKinematicCollider);
							}
						}
					}
				}

				utils::HitInfo testHitInfo{};
				bool checkHorizontal{ true }, checkVertical{ true };

				for (KinematicCollider* const pKinematicCollider : vpKinematicColliders)
				{
					//	By default use it's initialized vector of vertices
					std::vector<Point2f> vVertices{ pKinematicCollider->m_pvVertices ? *pKinematicCollider->m_pvVertices : std::vector<Point2f>{} };

					if (pKinematicCollider->m_pRootCenter)
					{
						const Point2f& rootCenter{ *pKinematicCollider->m_pRootCenter };
						const float& width{ pKinematicCollider->m_Width }, & height{ pKinematicCollider->m_Height };

						vVertices.push_back(Point2f(rootCenter.x - width / 2, rootCenter.y - height / 2));
						vVertices.push_back(Point2f(rootCenter.x - width / 2, rootCenter.y + height / 2));
						vVertices.push_back(Point2f(rootCenter.x + width / 2, rootCenter.y + height / 2));
						vVertices.push_back(Point2f(rootCenter.x + width / 2, rootCenter.y - height / 2));
					}

					//	Check for horizontal collision in the middle
					const int amountOfHorizontalLines{ int(dynamicLocalCollisionBox.height / KinematicCollider::m_SMALLESTSIZE) + 1 };

					for (int index{ 1 }; index <= amountOfHorizontalLines; ++index)
					{
						const float yOffset{ index * (dynamicLocalCollisionBox.height / (amountOfHorizontalLines + 1)) };

						const Point2f
							vertexLeft	{ dynamicRootCenter.x + dynamicLocalCollisionBox.left - dynamicLocalCollisionBox.width / 2, dynamicRootCenter.y + dynamicLocalCollisionBox.bottom - dynamicLocalCollisionBox.height / 2 + yOffset },
							vertexRight	{ dynamicRootCenter.x + dynamicLocalCollisionBox.left + dynamicLocalCollisionBox.width / 2, dynamicRootCenter.y + dynamicLocalCollisionBox.bottom - dynamicLocalCollisionBox.height / 2 + yOffset };

						if (utils::Raycast(vVertices, vertexLeft, vertexRight, testHitInfo))
						{
							CheckHitInfo(pDynamicCollider, pKinematicCollider, testHitInfo, elapsedSeconds);

							checkHorizontal = false;

							break;
						}
					}

					//	Check for vertical collision in the middle
					const int amountOfVerticalLines{ int(dynamicLocalCollisionBox.width / KinematicCollider::m_SMALLESTSIZE) + 1 };

					for (int index{ 1 }; index <= amountOfVerticalLines; ++index)
					{
						const float xOffset{ index * (dynamicLocalCollisionBox.width / (amountOfVerticalLines + 1)) };

						const Point2f
							vertexBottom{ dynamicRootCenter.x + dynamicLocalCollisionBox.left - dynamicLocalCollisionBox.width / 2 + xOffset, dynamicRootCenter.y + dynamicLocalCollisionBox.bottom - dynamicLocalCollisionBox.height / 2 },
							vertexTop	{ dynamicRootCenter.x + dynamicLocalCollisionBox.left - dynamicLocalCollisionBox.width / 2 + xOffset, dynamicRootCenter.y + dynamicLocalCollisionBox.bottom + dynamicLocalCollisionBox.height / 2 };

						if (utils::Raycast(vVertices, vertexBottom, vertexTop, testHitInfo))
						{
							CheckHitInfo(pDynamicCollider, pKinematicCollider, testHitInfo, elapsedSeconds);

							checkVertical = false;

							break;
						}
					}
				}

				//	If there was no vertical and no horizontal collision detected, check the corners
				if (checkHorizontal || checkVertical)
				{
					for (KinematicCollider* const pKinematicCollider : vpKinematicColliders)
					{
						//	By default use it's initialized vector of vertices
						std::vector<Point2f> vVertices{ pKinematicCollider->m_pvVertices ? *pKinematicCollider->m_pvVertices : std::vector<Point2f>{} };

						if (pKinematicCollider->m_pRootCenter)
						{
							const Point2f& rootCenter{ *pKinematicCollider->m_pRootCenter };
							const float& width{ pKinematicCollider->m_Width }, & height{ pKinematicCollider->m_Height };

							vVertices = std::vector<Point2f>
							{
								Point2f(rootCenter.x - width / 2, rootCenter.y - height / 2),
								Point2f(rootCenter.x - width / 2, rootCenter.y + height / 2),
								Point2f(rootCenter.x + width / 2, rootCenter.y + height / 2),
								Point2f(rootCenter.x + width / 2, rootCenter.y - height / 2)
							};
						}

						for (int index{ -1 }; index < 2; index += 2)
						{
							const float xOffset{ index * (dynamicLocalCollisionBox.width / 2) }, yOffset{ (dynamicLocalCollisionBox.height / 2) };

							const Point2f
								vertex1{ dynamicRootCenter.x + dynamicLocalCollisionBox.left - xOffset, dynamicRootCenter.y + dynamicLocalCollisionBox.bottom - yOffset },
								vertex2{ dynamicRootCenter.x + dynamicLocalCollisionBox.left + xOffset, dynamicRootCenter.y + dynamicLocalCollisionBox.bottom + yOffset };

							if (utils::Raycast(vVertices, vertex1, vertex2, testHitInfo))
							{
								if ((checkHorizontal && (testHitInfo.normal == HORIZONTALNORMAL || testHitInfo.normal == -HORIZONTALNORMAL))
									||
									(checkVertical && (testHitInfo.normal == VERTICALNORMAL || testHitInfo.normal == -VERTICALNORMAL)))
								{
									CheckHitInfo(pDynamicCollider, pKinematicCollider, testHitInfo, elapsedSeconds);
								}
							}
						}
					}
				}
			}
		}
	}
}

void GameObjectManager::CheckHitInfo(DynamicCollider* const pDynamicCollider, const KinematicCollider* const pKinematicCollider, const utils::HitInfo& hitInfo, float elapsedSeconds)
{
	Point2f& dynamicRootCenter{ *pDynamicCollider->m_pRootCenter };
	const Rectf& dynamicLocalCollisionBox{ pDynamicCollider->m_LocalCollisionBox };
	float& lastHitRigidbodyIntersectiontY{ pDynamicCollider->m_LastHitRigidbodyIntersectionY };

	Rigidbody* const pDynamicRigidBody{ dynamic_cast<Rigidbody* const>(pDynamicCollider) };

	if (hitInfo.normal == VERTICALNORMAL)
	{
		dynamicRootCenter.y = hitInfo.intersectPoint.y - dynamicLocalCollisionBox.bottom + dynamicLocalCollisionBox.height / 2;

		if (pDynamicRigidBody)
		{
			Vector2f& dynamicVelocity{ pDynamicRigidBody->m_Velocity };
			if (dynamicVelocity.y < 0.0f)
			{
				dynamicVelocity.y = 0.0f;

				pDynamicCollider->OnCollision(hitInfo);

				const Rigidbody* const pKinematicRigidBody{ dynamic_cast<const Rigidbody* const>(pKinematicCollider) };
				if (pKinematicRigidBody)
				{
					const Vector2f& kinematicVelocity{ pKinematicRigidBody->m_Velocity };
					if (kinematicVelocity.y)
					{
						lastHitRigidbodyIntersectiontY = hitInfo.intersectPoint.y - dynamicLocalCollisionBox.bottom;
					}

					dynamicRootCenter.x += kinematicVelocity.x * elapsedSeconds;
				}
			}
		}
		else
		{
			pDynamicCollider->OnCollision(hitInfo);
		}
	}
	else if (hitInfo.normal == -VERTICALNORMAL)
	{
		dynamicRootCenter.y = hitInfo.intersectPoint.y - dynamicLocalCollisionBox.bottom - dynamicLocalCollisionBox.height / 2;

		if (pDynamicRigidBody)
		{
			Vector2f& dynamicVelocity{ pDynamicRigidBody->m_Velocity };
			if (dynamicVelocity.y > 0.0f)
			{
				dynamicVelocity.y = 0.0f;
				pDynamicCollider->OnCollision(hitInfo);
			}
		}
		else
		{
			pDynamicCollider->OnCollision(hitInfo);
		}
	}
	else if (hitInfo.normal == HORIZONTALNORMAL)
	{
		dynamicRootCenter.x = hitInfo.intersectPoint.x - dynamicLocalCollisionBox.left + dynamicLocalCollisionBox.width / 2;

		if (pDynamicRigidBody)
		{
			pDynamicRigidBody->m_Velocity.x = 0.0f;
		}

		pDynamicCollider->OnCollision(hitInfo);
	}
	else if (hitInfo.normal == -HORIZONTALNORMAL)
	{
		dynamicRootCenter.x = hitInfo.intersectPoint.x - dynamicLocalCollisionBox.left - dynamicLocalCollisionBox.width / 2;

		if (pDynamicRigidBody)
		{
			pDynamicRigidBody->m_Velocity.x = 0.0f;
		}

		pDynamicCollider->OnCollision(hitInfo);
	}
}

void GameObjectManager::SetLargestOffsets(GameObject* const pGameObject)
{
	float rootOffsetX{}, rootOffsetY{};

	SimpleSprite* const pSimpleSprite{ dynamic_cast<SimpleSprite* const>(pGameObject) };
	if (pSimpleSprite)
	{
		float cameraZoom{ Camera::GetZoom() };

		SpriteAnimator* const pSpriteAnimator{ dynamic_cast<SpriteAnimator* const>(pGameObject) };
		if (pSpriteAnimator)
		{
			rootOffsetX = abs(pSimpleSprite->m_OffsetX) + cameraZoom * pSimpleSprite->GetSourceRectangle().width / pSpriteAnimator->m_Columns / 2;
			rootOffsetY = abs(pSimpleSprite->m_OffsetY) + cameraZoom * pSimpleSprite->GetSourceRectangle().height / pSpriteAnimator->m_Rows / 2;

			pSimpleSprite->m_SourceRectangle.width /= pSpriteAnimator->m_Columns;
			pSimpleSprite->m_SourceRectangle.height /= pSpriteAnimator->m_Rows;

			pSimpleSprite->m_SourceRectangle.left = pSpriteAnimator->m_CurrentColumnIndex * pSimpleSprite->m_SourceRectangle.width;
			pSimpleSprite->m_SourceRectangle.bottom = (1 + pSpriteAnimator->m_CurrentRowIndex) * pSimpleSprite->m_SourceRectangle.height;
		}
		else
		{
			rootOffsetX = abs(pSimpleSprite->m_OffsetX) + cameraZoom * pSimpleSprite->GetSourceRectangle().width / 2;
			rootOffsetY = abs(pSimpleSprite->m_OffsetY) + cameraZoom * pSimpleSprite->GetSourceRectangle().height / 2;
		}

		if (pGameObject->m_LargestRootXOffset < rootOffsetX)
		{
			pGameObject->m_LargestRootXOffset = rootOffsetX;
		}

		if (pGameObject->m_LargestRootYOffset < rootOffsetY)
		{
			pGameObject->m_LargestRootYOffset = rootOffsetY;
		}
	}

	Pickupable* const pPickupable{ dynamic_cast<Pickupable* const>(pGameObject) };
	if (pPickupable)
	{
		rootOffsetX = abs(pPickupable->m_LocalPickupArea.left) + pPickupable->m_LocalPickupArea.width / 2;
		rootOffsetY = abs(pPickupable->m_LocalPickupArea.bottom) + pPickupable->m_LocalPickupArea.height / 2;

		if (pGameObject->m_LargestRootXOffset < rootOffsetX)
		{
			pGameObject->m_LargestRootXOffset = rootOffsetX;
		}

		if (pGameObject->m_LargestRootYOffset < rootOffsetY)
		{
			pGameObject->m_LargestRootYOffset = rootOffsetY;
		}
	}	
	
	Pickupper* const pPickupper{ dynamic_cast<Pickupper* const>(pGameObject) };
	if (pPickupper)
	{
		rootOffsetX = abs(pPickupper->m_LocalPickupArea.left) + pPickupper->m_LocalPickupArea.width / 2;
		rootOffsetY = abs(pPickupper->m_LocalPickupArea.bottom) + pPickupper->m_LocalPickupArea.height / 2;

		if (pGameObject->m_LargestRootXOffset < rootOffsetX)
		{
			pGameObject->m_LargestRootXOffset = rootOffsetX;
		}

		if (pGameObject->m_LargestRootYOffset < rootOffsetY)
		{
			pGameObject->m_LargestRootYOffset = rootOffsetY;
		}
	}
	
	HitBox* const pHitBox{ dynamic_cast<HitBox* const>(pGameObject) };
	if (pHitBox)
	{
		for (const LocalHitBox& localHitBox : pHitBox->m_vLocalHitBoxes)
		{
			rootOffsetX = abs(localHitBox.localHitBox.left) + localHitBox.localHitBox.width / 2;
			rootOffsetY = abs(localHitBox.localHitBox.bottom) + localHitBox.localHitBox.height / 2;

			if (pGameObject->m_LargestRootXOffset < rootOffsetX)
			{
				pGameObject->m_LargestRootXOffset = rootOffsetX;
			}

			if (pGameObject->m_LargestRootYOffset < rootOffsetY)
			{
				pGameObject->m_LargestRootYOffset = rootOffsetY;
			}
		}
	}
	
	HurtBox* const pHurtBox{ dynamic_cast<HurtBox* const>(pGameObject) };
	if (pHurtBox)
	{
		for (const LocalHurtBox& localHurtBox : pHurtBox->m_vLocalHurtBoxes)
		{
			rootOffsetX = abs(localHurtBox.localHurtBox.left) + localHurtBox.localHurtBox.width / 2;
			rootOffsetY = abs(localHurtBox.localHurtBox.bottom) + localHurtBox.localHurtBox.height / 2;

			if (pGameObject->m_LargestRootXOffset < rootOffsetX)
			{
				pGameObject->m_LargestRootXOffset = rootOffsetX;
			}

			if (pGameObject->m_LargestRootYOffset < rootOffsetY)
			{
				pGameObject->m_LargestRootYOffset = rootOffsetY;
			}
		}
	}
	
	Interactable* const pInteractable{ dynamic_cast<Interactable* const>(pGameObject) };
	if (pInteractable)
	{
		rootOffsetX = abs(pInteractable->m_LocalLockArea.left) + pInteractable->m_LocalLockArea.width / 2;
		rootOffsetY = abs(pInteractable->m_LocalLockArea.bottom) + pInteractable->m_LocalLockArea.height / 2;

		if (pGameObject->m_LargestRootXOffset < rootOffsetX)
		{
			pGameObject->m_LargestRootXOffset = rootOffsetX;
		}

		if (pGameObject->m_LargestRootYOffset < rootOffsetY)
		{
			pGameObject->m_LargestRootYOffset = rootOffsetY;
		}
	}
	
	Interactor* const pInteractor{ dynamic_cast<Interactor* const>(pGameObject) };
	if (pInteractor)
	{
		rootOffsetX = abs(pInteractor->m_LocalInteractArea.left) + pInteractor->m_LocalInteractArea.width / 2;
		rootOffsetY = abs(pInteractor->m_LocalInteractArea.bottom) + pInteractor->m_LocalInteractArea.height / 2;

		if (pGameObject->m_LargestRootXOffset < rootOffsetX)
		{
			pGameObject->m_LargestRootXOffset = rootOffsetX;
		}

		if (pGameObject->m_LargestRootYOffset < rootOffsetY)
		{
			pGameObject->m_LargestRootYOffset = rootOffsetY;
		}
	}
	
	DynamicCollider* const pDynamicCollider{ dynamic_cast<DynamicCollider* const>(pGameObject) };
	if (pDynamicCollider)
	{
		rootOffsetX = abs(pDynamicCollider->m_LocalCollisionBox.left) + pDynamicCollider->m_LocalCollisionBox.width / 2;
		rootOffsetY = abs(pDynamicCollider->m_LocalCollisionBox.bottom) + pDynamicCollider->m_LocalCollisionBox.height / 2;

		if (pGameObject->m_LargestRootXOffset < rootOffsetX)
		{
			pGameObject->m_LargestRootXOffset = rootOffsetX;
		}

		if (pGameObject->m_LargestRootYOffset < rootOffsetY)
		{
			pGameObject->m_LargestRootYOffset = rootOffsetY;
		}
	}

	KinematicCollider* const pKinematicCollider{ dynamic_cast<KinematicCollider* const>(pGameObject) };
	if (pKinematicCollider)
	{
		if (pKinematicCollider->m_pRootCenter)
		{
			rootOffsetX = pKinematicCollider->m_Width / 2;
			rootOffsetY = pKinematicCollider->m_Height / 2;
		}
		else
		{
			rootOffsetX = INFINITY;
			rootOffsetY = INFINITY;
		}

		if (pGameObject->m_LargestRootXOffset < rootOffsetX)
		{
			pGameObject->m_LargestRootXOffset = rootOffsetX;
		}

		if (pGameObject->m_LargestRootYOffset < rootOffsetY)
		{
			pGameObject->m_LargestRootYOffset = rootOffsetY;
		}
	}
}

bool GameObjectManager::IsInCameraView(const GameObject* const pGameObject)
{
	if (pGameObject)
	{
		if (pGameObject->m_OnlyHandleInView)
		{
			if (!Camera::IsShifting())
				return utils::IsOverlapping(Camera::GetTransformedViewPort(), GetGameObjectBoundingRectangle(pGameObject));
			else
				return false;
		}

		return true;
	}

	return false;
}

bool GameObjectManager::IsInAnyCameraZone(const GameObject* const pGameObject)
{
	if (pGameObject)
		for (const Rectf& cameraZone : Camera::GetCameraZones())
			if (utils::IsOverlapping(cameraZone, GetGameObjectBoundingRectangle(pGameObject)))
				return true;
	
	return false;
}

Rectf GameObjectManager::GetGameObjectBoundingRectangle(const GameObject* const pGameObject)
{
	Rectf gameObjectBoundingRectangle{};

	if (pGameObject)
	{
		float cameraOffsetX{}, cameraOffsetY{};

		const SimpleSprite* const pSimpleSprite{ dynamic_cast<const SimpleSprite* const>(pGameObject) };
		if (pSimpleSprite)
		{
			const float distanceLayer1{ 1.0f }, distanceLayer2{ 7.0f }, distanceLayer3{ 8.0f }, distanceLayer4{ 9.0f };

			switch (pSimpleSprite->m_Layer)
			{
			case 0:
				cameraOffsetY = Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y;
				cameraOffsetX = (Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x);
				break;

			case 1:
				cameraOffsetY = Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y;
				cameraOffsetX = (Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer4);
				break;

			case 2:
				cameraOffsetY = Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y;
				cameraOffsetX = (Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer3);
				break;

			case 3:
				cameraOffsetY = Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y;
				cameraOffsetX = (Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer2);
				break;

			case 4:
				cameraOffsetY = Camera::GetTransformedViewPort().bottom + Camera::GetShakeOffsets().y;
				cameraOffsetX = (Camera::GetTransformedViewPort().left + Camera::GetShakeOffsets().x) / (10 / distanceLayer1);
				break;

			default:
				cameraOffsetY = Camera::GetShakeOffsets().y;
				cameraOffsetX = Camera::GetShakeOffsets().x;
				break;

				cameraOffsetY += Camera::GetTransformedViewPort().height / 2;
				cameraOffsetX += Camera::GetTransformedViewPort().width / 2;
			}
		}

		gameObjectBoundingRectangle = Rectf(pGameObject->m_RootCenter.x - pGameObject->m_LargestRootXOffset / 2, pGameObject->m_RootCenter.y - pGameObject->m_LargestRootYOffset / 2, 2 * pGameObject->m_LargestRootXOffset, 2 * pGameObject->m_LargestRootYOffset);
	}

	return gameObjectBoundingRectangle;
}
#pragma endregion PrivateMethods