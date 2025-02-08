#include "pch.h"
#include "HurtBox.h"

#pragma region Constructors/destructor
LocalHurtBox::LocalHurtBox(const Rectf& localHurtBox) :
	localHurtBox{ localHurtBox },
	vGroupNumbers{},
	knockBackVelocity{}
{
}

HurtBox::HurtBox(const Point2f& rootCenter, float cooldownSeconds) :
	m_IsActive{ true },

	m_pRootCenter{ &rootCenter },
	m_vLocalHurtBoxes{},

	m_MaxCooldownSeconds{ cooldownSeconds },
	m_AccumulatedCooldownSeconds{},
	m_IsOnCooldown{}
{
}
#pragma endregion Constructors/destructor



#pragma region ProtectedMethods
int HurtBox::AddLocalHurtBox(const Rectf& localHurtBox)
{
	const int addedHurtBoxIndex{ int(m_vLocalHurtBoxes.size()) };
	m_vLocalHurtBoxes.push_back(localHurtBox);
	return addedHurtBoxIndex;
}

int HurtBox::AddLocalHurtBox(float width, float height)
{
	return AddLocalHurtBox(Rectf(0.0f, 0.0f, width, height));
}

int HurtBox::AddLocalHurtBox(const Point2f& localBottomLeft, float width, float height)
{
	return AddLocalHurtBox(Rectf(localBottomLeft.x, localBottomLeft.y, width, height));
}

int HurtBox::AddLocalHurtBox(float localLeft, float localBottom, float width, float height)
{
	return AddLocalHurtBox(Rectf(localLeft, localBottom, width, height));
}

void HurtBox::AddGroupNumber(const std::initializer_list<int>& groupNumbers, int localHurtBoxIndex)
{
	if (localHurtBoxIndex != INT_MAX)
		for (int groupNumber : groupNumbers)
			m_vLocalHurtBoxes[localHurtBoxIndex].vGroupNumbers.push_back(groupNumber);
	else
		for (LocalHurtBox& localHurtBoxStruct : m_vLocalHurtBoxes)
			for (int groupNumber : groupNumbers)
				localHurtBoxStruct.vGroupNumbers.push_back(groupNumber);
}

void HurtBox::AddGroupNumber(int groupNumber, int localHurtBoxIndex)
{
	if (localHurtBoxIndex != INT_MAX)
		m_vLocalHurtBoxes[localHurtBoxIndex].vGroupNumbers.push_back(groupNumber);
	else
		for (LocalHurtBox& localHurtBoxStruct : m_vLocalHurtBoxes)
			localHurtBoxStruct.vGroupNumbers.push_back(groupNumber);
}

void HurtBox::SetLocalHurtBox(const Rectf& localHurtBox, int localHurtBoxIndex)
{
	if (localHurtBoxIndex != INT_MAX)
		m_vLocalHurtBoxes[localHurtBoxIndex].localHurtBox = localHurtBox;
	else
		for (LocalHurtBox& localHurtBoxStruct : m_vLocalHurtBoxes)
			localHurtBoxStruct.localHurtBox = localHurtBox;
}

void HurtBox::SetLocalHurtBox(const Point2f& localBottomLeft, float width, float height, int localHurtBoxIndex)
{
	SetLocalHurtBox(Rectf(localBottomLeft.x, localBottomLeft.y, width, height), localHurtBoxIndex);
}

void HurtBox::SetLocalHurtBox(float localLeft, float localBottom, float width, float height, int localHurtBoxIndex)
{
	SetLocalHurtBox(Rectf(localLeft, localBottom, width, height), localHurtBoxIndex);
}

void HurtBox::SetKnockBackVelocity(const Vector2f& knockBackVelocity, int localHurtBoxIndex)
{
	if (localHurtBoxIndex != INT_MAX)
		m_vLocalHurtBoxes[localHurtBoxIndex].knockBackVelocity = knockBackVelocity;
	else
		for (LocalHurtBox& localHurtBoxStruct : m_vLocalHurtBoxes)
			localHurtBoxStruct.knockBackVelocity = knockBackVelocity;
}

void HurtBox::SetKnockBackVelocity(float knockBackVelocityX, float knockBackVelocityY, int localHurtBoxIndex)
{
	SetKnockBackVelocity(Vector2f(knockBackVelocityX, knockBackVelocityY), localHurtBoxIndex);
}

const Rectf& HurtBox::GetLocalHurtBox(int localHurtBoxIndex) const
{
	localHurtBoxIndex %= m_vLocalHurtBoxes.size();
	return m_vLocalHurtBoxes[localHurtBoxIndex].localHurtBox;
}
#pragma endregion ProtectedMethods



#pragma region PrivateMethods
void HurtBox::OnHurt(const Vector2f& hurtNormals, int damage, int localHurtBoxIndex)
{

}
#pragma endregion PrivateMethods