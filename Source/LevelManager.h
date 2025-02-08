#pragma once

#include <vector>

#include "SoundStream.h"

class HUD;
class ShovelKnight;
class CheckPoint;
class LevelManager final
{
public:
	//	Other


	//	Rule of 5
	~LevelManager() = delete;

	LevelManager(const LevelManager& other) = delete;
	LevelManager(LevelManager&& other) = delete;
	LevelManager& operator=(const LevelManager& other) = delete;
	LevelManager& operator=(LevelManager&& other) = delete;

	//	Other special methods
	LevelManager() = delete;

	//	Methods
	static void Load(const Rectf& viewPort);

	static void Update(float elapsedSeconds);
	static void Draw();

	static void Close();

	//	Setters
	

	//	Getters


protected:


private:
	enum class State
	{
		StartScreen,
		Playing,
		TransitionToPause,
		Pause,
		TransitionToPlay,
		Dead,
		RespawnTransitionIn,
		BlackScreen,
		RespawnTransitionOut
	};

	static Rectf m_VIEW_PORT;

	static State m_STATE;

	static ShovelKnight* m_pPLAYER;
	static const Point2f m_PLAYER_START_POSITION;

	static HUD* m_pHUD;

	static int m_LAST_PLAYER_SCORE;

	static int m_FURTHEST_CHECK_POINT_INDEX;
	static std::vector<CheckPoint*> m_vpCHECK_POINTS;

	static float m_ACCUMULATED_SECONDS;
	static const float m_MAX_AFTER_DEATH_SECONDS, m_TRANSITION_SECONDS, m_BLACK_SCREEN_SECONDS;

	static bool m_PRINTED_TO_CONSOLE;
};