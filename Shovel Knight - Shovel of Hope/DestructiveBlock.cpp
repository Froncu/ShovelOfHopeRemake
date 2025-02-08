#include "pch.h"
#include "DestructiveBlock.h"

#pragma region Constructors/Destructor
DestructiveBlock::DestructiveBlock(const Point2f& bottomLeft, int row) :
	GameObject(bottomLeft.x + 8.0f, bottomLeft.y + 8.0f),
	KinematicCollider(m_RootCenter, 16.0f, 16.0f),
	HurtBox(m_RootCenter),
	SimpleSprite(m_RootCenter, 0.0f, 0.0f, "Environment/TileableDestructive.png", 10),
	SpriteAnimator(1, 13, INFINITY),

	m_WasHurt{},

	m_pGameObjectToDrop{}
{
	HurtBox::AddLocalHurtBox(0.0f, 0.0f, 16.0f, 16.0f);
	HurtBox::AddGroupNumber(0);
	HurtBox::SetKnockBackVelocity(0.0f, 360.0f);

	SpriteAnimator::SetCurrentRowIndex(row, 1);
}
DestructiveBlock::DestructiveBlock(float positionLeft, float positionBottom, int row) :
	DestructiveBlock(Point2f(positionLeft, positionBottom), row)
{
}

DestructiveBlock::~DestructiveBlock()
{
	if (m_pGameObjectToDrop) delete m_pGameObjectToDrop;
}
#pragma endregion Constructors/Destructor



#pragma region Components
void DestructiveBlock::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{
	m_WasHurt = true;
}
#pragma endregion Components