#pragma once

#include "Texture.h"

class ShovelKnight;
class HUD final
{
public:
	//	Other


	//	Rule of 5
	~HUD() = default;

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) = delete;

	//	Other special methods
	HUD(const Rectf& viewPort, const ShovelKnight* const pPlayer);

	//	Methods
	void Update(float elapsedSeconds);
	void Draw() const;

	//	Setters
	

	//	Getters


protected:


private:
	const Texture m_tBorder;
	Texture m_tScore, m_tHealthPlayer, m_tHealthEnemy;
	const Rectf m_ViewPort;
	const float m_Scalar;

	const ShovelKnight* const m_pPlayer;
	int m_DisplayedScore;
};