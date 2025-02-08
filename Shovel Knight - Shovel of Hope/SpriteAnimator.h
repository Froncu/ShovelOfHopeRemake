#pragma once

class SimpleSprite;
class SpriteAnimator
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~SpriteAnimator() = default;

	SpriteAnimator(const SpriteAnimator& other) = delete;
	SpriteAnimator(SpriteAnimator&& other) = delete;
	SpriteAnimator& operator=(const SpriteAnimator& other) = delete;
	SpriteAnimator& operator=(SpriteAnimator&& other) = delete;

	//	Other special methods


	//	Methods


	//	Setters
	

	//	Getters


protected:
	SpriteAnimator(int columns, int rows, float frameSeconds = 0.1f, int rowIndex = 0, int rowSize = 1);

	void SetCurrentRowIndex(int rowIndex, int rowSize, bool playNewCurrentRowOnce = false);
	void SetFrameSeconds(float frameSeconds);

private:
	virtual void OnColumnChange(int currentColumnIndex);

	const int m_Columns, m_Rows;

	int m_CurrentColumnIndex;

	int m_CurrentRowIndex, m_CurrentRowSize;
	int m_LastRowIndex, m_LastRowSize;

	bool m_ChangeRows, m_PlayCurrentRowOnce;

	float m_AccumulatedSeconds, m_FrameSeconds;
};