#include "pch.h"
#include "SimpleSprite.h"

#pragma region StaticDataMembers
std::map<std::string, const Texture* const> SimpleSprite::m_mLOADEDTEXTURES{};
std::map<const Texture* const, int> SimpleSprite::m_mAMOUNTINUSE{};
#pragma endregion StaticDataMembers



#pragma region Constructors/Destructor
SimpleSprite::SimpleSprite(const Point2f& rootCenter, float offsetX, float offsetY, const std::string& spritePath, int layer, int tilesX, int tilesY) :
	m_pRootCenter{ &rootCenter },
	m_OffsetX{ offsetX }, m_OffsetY{ offsetY },

	m_SpritePath{ spritePath },

	m_Layer{ layer },

	m_TilesX{ tilesX < 0 ? 1 : tilesX }, m_TilesY{ tilesY < 0 ? 1 : tilesY },

	m_ShouldBeDrawn{ true },
	m_BlinkAmount{},
	m_BlinkFrameSeconds{}, m_BlinkAccumulatedSeconds{},

	m_IsFlipped{}
{
	std::map<std::string, const Texture* const>::iterator iterator{ m_mLOADEDTEXTURES.find(m_SpritePath) };
	if (iterator != m_mLOADEDTEXTURES.end())
	{
		m_pTexture = m_mLOADEDTEXTURES.at(m_SpritePath);
	}
	else
	{
		m_pTexture = new Texture(m_SpritePath);

		m_mLOADEDTEXTURES.insert(std::pair<std::string, const Texture*>(m_SpritePath, m_pTexture));

		m_mAMOUNTINUSE.insert(std::pair<const Texture*, int>(m_pTexture, 0));
	}

	++m_mAMOUNTINUSE.at(m_pTexture);

	m_SourceRectangle = Rectf(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight());
}

SimpleSprite::~SimpleSprite()
{
	--m_mAMOUNTINUSE.at(m_pTexture);

	if (!m_mAMOUNTINUSE.at(m_pTexture))
	{
		delete m_pTexture;
		m_mLOADEDTEXTURES.erase(m_SpritePath);
		m_mAMOUNTINUSE.erase(m_pTexture);
	}
}
#pragma endregion Constructors/Destructor



#pragma region ProtectedMethods
void SimpleSprite::Blink(int blinkAmount, float durationSeconds)
{
	if (!m_BlinkAmount && blinkAmount > 0)
	{
		m_BlinkAmount = 2 * blinkAmount;
		m_BlinkFrameSeconds = durationSeconds / m_BlinkAmount;

		m_ShouldBeDrawn = false;
	}
}

const Rectf& SimpleSprite::GetSourceRectangle() const
{
	return m_SourceRectangle;
}
#pragma endregion ProtectedMethods



#pragma region PrivateMethods
void SimpleSprite::Draw() const
{
	if (m_ShouldBeDrawn)
	{
		const bool isXOdd{ bool(m_TilesX % 2) };
		const int startingTileX{ -m_TilesX / 2 };

		const bool isYOdd{ bool(m_TilesY % 2) };
		const int startingTileY{ -m_TilesY / 2 };

		for (int tileX{ startingTileX + !isXOdd }; tileX < -startingTileX + 1; ++tileX)
		{
			const float centerOffsetX{ tileX * m_SourceRectangle.width - (!isXOdd ? m_SourceRectangle.width / 2 : 0) };

			for (int tileY{ startingTileY + !isYOdd }; tileY < -startingTileY + 1; ++tileY)
			{
				const float centerOffsetY{ tileY * m_SourceRectangle.height - (!isYOdd ? m_SourceRectangle.height / 2 : 0) };
				if (!m_IsFlipped)
				{
					m_pTexture->Draw(Point2f(m_pRootCenter->x + centerOffsetX - m_SourceRectangle.width / 2 + m_OffsetX, m_pRootCenter->y + centerOffsetY - m_SourceRectangle.height / 2 + m_OffsetY), m_SourceRectangle);
				}
				else
				{
					glPushMatrix();

					glTranslatef(m_pRootCenter->x + centerOffsetX + m_OffsetX, m_pRootCenter->y + centerOffsetY + m_OffsetY, 0);
					glScalef(-1, 1, 1);
					m_pTexture->Draw(Point2f(-m_SourceRectangle.width / 2, -m_SourceRectangle.height / 2), m_SourceRectangle);

					glPopMatrix();
				}
			}
		}
	}
}
#pragma endregion PrivateMethods