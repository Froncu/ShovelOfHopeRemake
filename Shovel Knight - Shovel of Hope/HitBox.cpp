#include "pch.h"
#include "HitBox.h"

#pragma region Constructors/destructor
LocalHitBox::LocalHitBox(const Rectf& localHitBox) :
	localHitBox{ localHitBox },
	vGroupNumbers{},
	hitDirection{},
	damage{ 1 },
	isActive{ true }
{
}

HitBox::HitBox(const Point2f& rootCenter) :
	m_pRootCenter{ &rootCenter },
	m_vLocalHitBoxes{}
{
}
#pragma endregion Constructors/destructor



#pragma region ProtectedMethods
int HitBox::AddLocalHitBox(const Rectf& localHitBox)
{
	const int addedHitBoxIndex{ int(m_vLocalHitBoxes.size()) };
	m_vLocalHitBoxes.push_back(localHitBox);
	return addedHitBoxIndex;
}

int HitBox::AddLocalHitBox(float width, float height)
{
	return AddLocalHitBox(Rectf(0.0f, 0.0f, width, height));
}

int HitBox::AddLocalHitBox(const Point2f& localBottomLeft, float width, float height)
{
	return AddLocalHitBox(Rectf(localBottomLeft.x, localBottomLeft.y, width, height));
}

int HitBox::AddLocalHitBox(float localLeft, float localBottom, float width, float height)
{
	return AddLocalHitBox(Rectf(localLeft, localBottom, width, height));
}

void HitBox::AddGroupNumber(const std::initializer_list<int>& groupNumbers, int localHitBoxIndex)
{
	if (localHitBoxIndex != INT_MAX)
		for (int groupNumber : groupNumbers)
			m_vLocalHitBoxes[localHitBoxIndex].vGroupNumbers.push_back(groupNumber);
	else
		for (LocalHitBox& localHitBoxStruct : m_vLocalHitBoxes)
			for (int groupNumber : groupNumbers) 
				localHitBoxStruct.vGroupNumbers.push_back(groupNumber);
}

void HitBox::AddGroupNumber(int groupNumber, int localHitBoxIndex)
{
	if (localHitBoxIndex != INT_MAX)
		m_vLocalHitBoxes[localHitBoxIndex].vGroupNumbers.push_back(groupNumber);
	else
		for (LocalHitBox& localHitBoxStruct : m_vLocalHitBoxes)
			localHitBoxStruct.vGroupNumbers.push_back(groupNumber);
}

void HitBox::SetLocalHitBox(const Rectf& localHitBox, int localHitBoxIndex)
{
	if (localHitBoxIndex != INT_MAX)
		m_vLocalHitBoxes[localHitBoxIndex].localHitBox = localHitBox;
	else
		for (LocalHitBox& localHitBoxStruct : m_vLocalHitBoxes)
			localHitBoxStruct.localHitBox = localHitBox;
}

void HitBox::SetLocalHitBox(const Point2f& localBottomLeft, float width, float height, int localHitBoxIndex)
{
	SetLocalHitBox(Rectf(localBottomLeft.x, localBottomLeft.y, width, height), localHitBoxIndex);
}

void HitBox::SetLocalHitBox(float localLeft, float localBottom, float width, float height, int localHitBoxIndex)
{
	SetLocalHitBox(Rectf(localLeft, localBottom, width, height), localHitBoxIndex);
}

void HitBox::SetHitDirection(const Vector2f& hitDirection, int localHitBoxIndex)
{
	const Vector2f normalizedHitDirection{ hitDirection.x ? hitDirection.x / abs(hitDirection.x) : 0.0f, hitDirection.y ? hitDirection.y / abs(hitDirection.y) : 0.0f };

	if (localHitBoxIndex != INT_MAX)
		m_vLocalHitBoxes[localHitBoxIndex].hitDirection = normalizedHitDirection;
	else
		for (LocalHitBox& localHitBoxStruct : m_vLocalHitBoxes)
			localHitBoxStruct.hitDirection = normalizedHitDirection;
}

void HitBox::SetHitDirection(float horizontalHitDirection, float verticalHitDirection, int localHitBoxIndex)
{
	SetHitDirection(Vector2f(horizontalHitDirection, verticalHitDirection), localHitBoxIndex);
}

void HitBox::SetDamage(int damage, int localHitBoxIndex)
{
	damage = damage >= 0 ? damage : 0;

	if (localHitBoxIndex != INT_MAX)
		m_vLocalHitBoxes[localHitBoxIndex].damage = damage;
	else
		for (LocalHitBox& localHitBoxStruct : m_vLocalHitBoxes)
			localHitBoxStruct.damage = damage;
}

void HitBox::SetActive(bool isActive, int localHitBoxIndex)
{
	if (localHitBoxIndex != INT_MAX)
		m_vLocalHitBoxes[localHitBoxIndex].isActive = isActive;
	else
		for (LocalHitBox& localHitBoxStruct : m_vLocalHitBoxes)
			localHitBoxStruct.isActive = isActive;
}

const Rectf& HitBox::GetLocalHitBox(int localHitBoxIndex) const
{
	localHitBoxIndex %= m_vLocalHitBoxes.size();
	return m_vLocalHitBoxes[localHitBoxIndex].localHitBox;
}

bool HitBox::GetIsActive(int localHitBoxIndex) const
{
	localHitBoxIndex %= m_vLocalHitBoxes.size();
	return m_vLocalHitBoxes[localHitBoxIndex].isActive;
}
#pragma endregion ProtectedMethods



#pragma region PrivateMethods
void HitBox::OnHit(const Vector2f& hitNormals, const Vector2f& knockBackVelocity, int localHitBoxIndex)
{

}
#pragma endregion PrivateMethods