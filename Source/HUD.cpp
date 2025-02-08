#include "pch.h"
#include "HUD.h"

#include "ShovelKnight.h"

#pragma region Constructors/Destructor
HUD::HUD(const Rectf& viewPort, const ShovelKnight* const pPlayer) :
	m_tBorder{ "HUD/Border.png" },
	m_tScore{ std::string("0"), std::string("HUD/Font.ttf"), 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f) }, m_tHealthPlayer{ "HUD/HealthPlayer.png" }, m_tHealthEnemy{ "HUD/HealthBoss.png" },

	m_ViewPort{ viewPort },
	m_Scalar{ m_ViewPort.width / m_tBorder.GetWidth() },

	m_pPlayer{ pPlayer },
	m_DisplayedScore{}
{
}
#pragma endregion Constructors/Destructor



#pragma region PublicMethods
void HUD::Update(float elapsedSeconds)
{
	if (m_DisplayedScore != m_pPlayer->m_Score)
	{
		m_tScore = Texture(std::to_string(m_pPlayer->m_Score), std::string("HUD/Font.ttf"), 32, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void HUD::Draw() const
{
	m_tBorder.Draw(Rectf(0.0f, m_ViewPort.height - m_Scalar * m_tBorder.GetHeight(), m_Scalar * m_tBorder.GetWidth(), m_Scalar * m_tBorder.GetHeight()));
	m_tScore.Draw(Rectf(40.0f, m_ViewPort.height - m_Scalar * m_tBorder.GetHeight(), 0.0f, 0.0f));

	
	

	for (int full{}; full < m_pPlayer->m_Health / 2; ++full)
	{
		const Rectf 
			destinationRectangle{ 496.0f + (full * 8.0f * m_Scalar) + full * (4.0f), m_ViewPort.height - m_Scalar * m_tBorder.GetHeight() + 4.0f, 8.0f * m_Scalar, 8.0f * m_Scalar},
			sourceRectangle{ 0.0f, 0.0f, 8.0f, 8.0f};

		m_tHealthPlayer.Draw(destinationRectangle, sourceRectangle);
	}
	for (int half{ m_pPlayer->m_Health / 2 }; half < m_pPlayer->m_Health / 2 + m_pPlayer->m_Health % 2; ++half)
	{
		const Rectf 
			destinationRectangle{ 496.0f + (half * 8.0f * m_Scalar) + half * (4.0f), m_ViewPort.height - m_Scalar * m_tBorder.GetHeight() + 4.0f, 8.0f * m_Scalar, 8.0f * m_Scalar},
			sourceRectangle{ 8.0f, 0.0f, 8.0f, 8.0f};

		m_tHealthPlayer.Draw(destinationRectangle, sourceRectangle);
	}
	for (int empty{ m_pPlayer->m_Health / 2 + m_pPlayer->m_Health % 2 }; empty < 4; ++empty)
	{
		const Rectf 
			destinationRectangle{ 496.0f + (empty * 8.0f * m_Scalar) + empty * (4.0f), m_ViewPort.height - m_Scalar * m_tBorder.GetHeight() + 4.0f, 8.0f * m_Scalar, 8.0f * m_Scalar},
			sourceRectangle{ 16.0f, 0.0f, 8.0f, 8.0f};

		m_tHealthPlayer.Draw(destinationRectangle, sourceRectangle);
	}
}
#pragma endregion PublicMethods