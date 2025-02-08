#include "pch.h"
#include "SpriteAnimator.h"

class SimpleSprite;

#pragma region Constructors/Destructor
SpriteAnimator::SpriteAnimator(int columns, int rows, float frameSeconds, int rowIndex, int rowSize) :
	m_Columns{ columns }, m_Rows{ rows },

	m_CurrentColumnIndex{},

	m_CurrentRowIndex{ rowIndex }, m_CurrentRowSize{ rowSize < 1 ? 1 : rowSize },
	m_LastRowIndex{ m_CurrentRowIndex }, m_LastRowSize{ m_CurrentRowSize },
	m_ChangeRows{ true }, m_PlayCurrentRowOnce{},

	m_AccumulatedSeconds{}, m_FrameSeconds{ frameSeconds }
{
	if (m_Rows == 1)
	{
		m_CurrentRowSize = m_Columns;
	}
}
#pragma endregion Constructors/Destructor



#pragma region ProtectedMethods
void SpriteAnimator::SetCurrentRowIndex(int rowIndex, int rowSize, bool playNewCurrentRowOnce)
{
	if (rowIndex != m_CurrentRowIndex)
	{
		m_AccumulatedSeconds = 0;

		m_CurrentRowIndex = rowIndex;
		m_CurrentRowSize = rowSize < 1 ? 1 : rowSize;

		m_ChangeRows = true;
		m_PlayCurrentRowOnce = playNewCurrentRowOnce;
	}
}

void SpriteAnimator::SetFrameSeconds(float frameSeconds)
{
	if (m_FrameSeconds != frameSeconds)
	{
		m_FrameSeconds = frameSeconds >= 0.0f ? frameSeconds : 0.0f;
		m_AccumulatedSeconds = 0.0f;
	}
}
#pragma endregion ProtectedMethods



#pragma region PrivateMethods
void SpriteAnimator::OnColumnChange(int currentColumnIndex)
{

}
#pragma endregion PrivateMethods