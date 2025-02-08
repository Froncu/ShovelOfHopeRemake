#pragma once

#include "Texture.h"
#include "GameObject.h"
#include <map>
#include <string>

class SimpleSprite 
{
public:
	//	Other
	friend class GameObjectManager;

	//	Rule of 5
	virtual ~SimpleSprite();

	SimpleSprite(const SimpleSprite& other) = delete;
	SimpleSprite(SimpleSprite&& other) = delete;
	SimpleSprite& operator=(const SimpleSprite& other) = delete;
	SimpleSprite& operator=(SimpleSprite&& other) = delete;

	//	Other special methods
	SimpleSprite(const Point2f& rootCenter, float offsetX, float offsetY, const std::string& spritePath, int layer = 5, int tilesX = 1, int tilesY = 1);

	//	Methods
	

	//	Setters
	

	//	Getters


protected:
	void Blink(int blinkAmount, float durationSeconds);

	const Rectf& GetSourceRectangle() const;

	bool m_IsFlipped;

	float m_OffsetX, m_OffsetY;

private:
	void Draw() const;

	static std::map<std::string, const Texture* const> m_mLOADEDTEXTURES;
	static std::map<const Texture* const, int> m_mAMOUNTINUSE;

	const Point2f* const m_pRootCenter;

	const std::string m_SpritePath;

	const int m_Layer;

	const int m_TilesX, m_TilesY;

	bool m_ShouldBeDrawn;
	int m_BlinkAmount;
	float m_BlinkFrameSeconds, m_BlinkAccumulatedSeconds;

	const Texture* m_pTexture;
	Rectf m_SourceRectangle;
};