#include "pch.h"
#include "LevelManager.h"

#include "GameObjectManager.h"
#include "Camera.h"

#include "ShovelKnight.h"
#include "HUD.h"

#include "SVGMap.h"
#include "Background.h"
#include "SVGDeathZone.h"
#include "DigPile.h"
#include "Pickupable.h"
#include "DirtBlock.h"
#include "Bubble.h"
#include "Ladder.h"
#include "CheckPoint.h"
#include "MovingPlatform.h"
#include "DirtBlockSmall.h"
#include "Spike.h"
#include "Skull.h"
#include "Destructive.h"
#include "DigClod.h"

#include "Beeto.h"
#include "Dozedrake.h"
#include "Boneclang.h"
#include "Divedrake.h"
#include "Blorb.h"
#include "Platter.h"

#include "SoundManager.h"

#include "InputManager.h"

#pragma region StaticVariables
Rectf LevelManager::m_VIEW_PORT{};

LevelManager::State LevelManager::m_STATE{ State::Playing };

ShovelKnight* LevelManager::m_pPLAYER{};
const Point2f LevelManager::m_PLAYER_START_POSITION{ 112.0f, 448.0f };
//const Point2f LevelManager::m_PLAYER_START_POSITION{ 3024.0f, 480.0f };


HUD* LevelManager::m_pHUD{};

int LevelManager::m_LAST_PLAYER_SCORE{};

int LevelManager::m_FURTHEST_CHECK_POINT_INDEX{ -1 };
std::vector<CheckPoint*> LevelManager::m_vpCHECK_POINTS{};

float LevelManager::m_ACCUMULATED_SECONDS{};
const float LevelManager::m_MAX_AFTER_DEATH_SECONDS{ 1.5f }, LevelManager::m_TRANSITION_SECONDS{ 1.0f }, LevelManager::m_BLACK_SCREEN_SECONDS{ 0.25f };

bool LevelManager::m_PRINTED_TO_CONSOLE{};
#pragma endregion StaticVariables



#pragma region PublicMethods
void LevelManager::Load(const Rectf& viewPort)
{
	m_VIEW_PORT = viewPort;

	m_STATE = State::Playing;

	m_pPLAYER = new ShovelKnight{ m_PLAYER_START_POSITION };
	m_pHUD = new HUD{ m_VIEW_PORT, m_pPLAYER };

	SoundManager::PlayStream("Audio/LevelAudio.mp3", true);
	SoundManager::SetVolumeEffect(255);

	//	Other level related
	Camera::SetSVGPath("Level/SVG/CameraZones.svg");
	Camera::SetViewPort(m_VIEW_PORT);
	Camera::SetGameObjectToFollow(m_pPLAYER);

	GameObjectManager::AddGameObject(new Background{ 0.0f, 0.0f, "Level/Textures/Sky.png", 0 });
	GameObjectManager::AddGameObject(new Background{ 0.0f, 0.0f, "Level/Textures/Castle.png", 1 });
	GameObjectManager::AddGameObject(new Background{ 0.0f, 0.0f, "Level/Textures/Trees3.png", 2 });
	GameObjectManager::AddGameObject(new Background{ 0.0f, 0.0f, "Level/Textures/Trees2.png", 3 });
	GameObjectManager::AddGameObject(new Background{ 0.0f, 0.0f, "Level/Textures/Trees1.png", 4 });

	GameObjectManager::AddGameObject(new Background{ 2032.0f, 560.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 11, 3 });
	GameObjectManager::AddGameObject(new Background{ 2832.0f, 480.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 18, 8 });
	GameObjectManager::AddGameObject(new Background{ 2800.0f, 208.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 25, 13 });
	GameObjectManager::AddGameObject(new Background{ 3072.0f, 32.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 6, 11 });
	GameObjectManager::AddGameObject(new Background{ 2720.0f, 32.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 16, 8 });
	GameObjectManager::AddGameObject(new Background{ 2640.0f, 0.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 4, 8 });
	GameObjectManager::AddGameObject(new Background{ 2544.0f, 32.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 3, 6 });
	GameObjectManager::AddGameObject(new Background{ 2480.0f, 0.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 2, 8 });
	GameObjectManager::AddGameObject(new Background{ 3168.0f, 32.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 51, 9 });
	GameObjectManager::AddGameObject(new Background{ 3232.0f, 176.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 7 });
	GameObjectManager::AddGameObject(new Background{ 3408.0f, 176.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 1 });
	GameObjectManager::AddGameObject(new Background{ 3536.0f, 176.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 7 });
	GameObjectManager::AddGameObject(new Background{ 3696.0f, 176.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 1 });
	GameObjectManager::AddGameObject(new Background{ 3776.0f, 176.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 3 });
	GameObjectManager::AddGameObject(new Background{ 4000.0f, 16.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 16, 25 });
	GameObjectManager::AddGameObject(new Background{ 4272.0f, 32.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 6, 8 });
	GameObjectManager::AddGameObject(new Background{ 4272.0f, 160.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 6 });
	GameObjectManager::AddGameObject(new Background{ 4256.0f, 208.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 42, 9 });
	GameObjectManager::AddGameObject(new Background{ 4256.0f, 352.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 42 });
	GameObjectManager::AddGameObject(new Background{ 4000.0f, 416.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 3, 24 });
	GameObjectManager::AddGameObject(new Background{ 4000.0f, 800.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 3 });
	GameObjectManager::AddGameObject(new Background{ 4160.0f, 464.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 8, 8 });
	GameObjectManager::AddGameObject(new Background{ 4160.0f, 592.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 8 });
	GameObjectManager::AddGameObject(new Background{ 5680.0f, 624.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 3, 9 });
	GameObjectManager::AddGameObject(new Background{ 5680.0f, 768.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 3 });
	GameObjectManager::AddGameObject(new Background{ 5288.0f, 1040.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 6, 8 });
	GameObjectManager::AddGameObject(new Background{ 5288.0f, 1168.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 6 });
	GameObjectManager::AddGameObject(new Background{ 5464.0f, 1040.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 1, 8 });
	GameObjectManager::AddGameObject(new Background{ 5464.0f, 1168.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 1 });
	GameObjectManager::AddGameObject(new Background{ 5512.0f, 1040.0f, "Level/Textures/TileableWaterfall.png", 5, 3, 1, 8 });
	GameObjectManager::AddGameObject(new Background{ 5512.0f, 1168.0f, "Level/Textures/TileableWaterfallTop.png", 5, 3, 1 });

	GameObjectManager::AddGameObject(new Background{ 0.0f, 0.0f, "Level/Textures/Cave.png", 6 });
	GameObjectManager::AddGameObject(new Background{ 0.0f, 0.0f, "Level/Textures/Grass.png", 11 });

	GameObjectManager::AddGameObject(new SVGDeathZone{ "Level/SVG/DeathZone.svg" });

	GameObjectManager::AddGameObject(new SVGMap{ "Level/SVG/Ground.svg" });

	GameObjectManager::AddGameObject(m_pPLAYER);



	CheckPoint* pCheckPoint{};

	//	Zone 0
	GameObjectManager::AddGameObject(new Beeto{ 560.0f, 448.0f, true });
	GameObjectManager::AddGameObject(new Beeto{ 688.0f, 512.0f, true, -16, 32 });
	GameObjectManager::AddGameObject(new Beeto{ 784.0f, 448.0f, false });
	GameObjectManager::AddGameObject(new Beeto{ 960.0f, 448.0f, true });
	GameObjectManager::AddGameObject(new Beeto{ 1200.0f, 448.0f, true });
	GameObjectManager::AddGameObject(new Beeto{ 1312.0f, 480.0f, true, -32, 32 });

	GameObjectManager::AddGameObject(new DigPile{ 344.0f, 448.0f });
	GameObjectManager::AddGameObject(new DigPile{ 920.0f, 448.0f });

	GameObjectManager::AddGameObject(new DirtBlock{ 896.0f, 512.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlock{ 1168.0f, 528.0f, Pickupable::Type::GoldGem });
	GameObjectManager::AddGameObject(new DirtBlock{ 1535.0f, 480.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 1535.0f, 512.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 1535.0f, 544.0f });



	//	Zone 1
	GameObjectManager::AddGameObject(new Beeto{ 1888.0f, 448.0f, false });

	GameObjectManager::AddGameObject(new DigPile{ 1880.0f, 448.0f });

	GameObjectManager::AddGameObject(new DirtBlock{ 1696.0f, 480.0f, Pickupable::Type::GoldGem });
	GameObjectManager::AddGameObject(new DirtBlock{ 1792.0f, 480.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 1792.0f, 512.0f });



	//	Zone 2
	GameObjectManager::AddGameObject(new Bubble{ 2200.0f, 384.0f, 0.0f, 96.0f });

	GameObjectManager::AddGameObject(new Ladder{ 2288.0f, 528.0f, 8 });



	//	Zone 3
	pCheckPoint = new CheckPoint{ 2160.0f, 656.0f };
	m_vpCHECK_POINTS.push_back(pCheckPoint);
	GameObjectManager::AddGameObject(pCheckPoint);

	GameObjectManager::AddGameObject(new Ladder{ 2032.0f, 656.0f, 10 });

	GameObjectManager::AddGameObject(new MovingPlatform{ 2136.0f, 744.0f, 112.0f, 0.0f, 0.5f, 6.0f });

	GameObjectManager::AddGameObject(new Beeto{ 2320.0f, 752.0f, false, -16, 80 });

	GameObjectManager::AddGameObject(new Pickupable{ 2120.0f, 816.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new Pickupable{ 2184.0f, 816.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new Pickupable{ 2248.0f, 816.0f, Pickupable::Type::BlueGem });



	//	Zone 4
	GameObjectManager::AddGameObject(new DirtBlock{ 2448.0f, 656.0f, Pickupable::Type::RedGem });
	GameObjectManager::AddGameObject(new DirtBlock{ 2736.0f, 656.0f, Pickupable::Type::GreenGem });

	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2448.0f, 688.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2720.0f, 656.0f, Pickupable::Type::GreenGem });

	GameObjectManager::AddGameObject(new MovingPlatform{ 2552.0f, 648.0f, 112.0f, 0.0f, 0.5f, 4.0f });

	GameObjectManager::AddGameObject(new Spike{ 2512.0f, 624.0f, 11 });

	GameObjectManager::AddGameObject(new Pickupable{ 2600.0f, 724.0f, Pickupable::Type::GoldGem });



	//	Zone 5
	GameObjectManager::AddGameObject(new Ladder{ 3136.0f, 624.0f, 2 });

	GameObjectManager::AddGameObject(new Dozedrake{ 2992.0f, 656.0f });



	//	Zone 6
	GameObjectManager::AddGameObject(new Ladder{ 2880.0f, 368.0f, 4 });

	GameObjectManager::AddGameObject(new Boneclang{ m_pPLAYER, 2928.0f, 480.0f });
	GameObjectManager::AddGameObject(new Skull{ 3152.0f, 480.0f });
	GameObjectManager::AddGameObject(new Skull{ 3056.0f, 480.0f });
	GameObjectManager::AddGameObject(new Skull{ 2880.0f, 480.0f });

	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2832.0f, 464.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2832.0f, 448.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2832.0f, 432.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2848.0f, 464.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2848.0f, 448.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2848.0f, 432.0f });



	//	Zone 7
	GameObjectManager::AddGameObject(new DirtBlock{ 3136.0f, 288.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3136.0f, 256.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3136.0f, 224.0f });

	GameObjectManager::AddGameObject(new Ladder{ 3088.0f, 224.0f, 4 });
	GameObjectManager::AddGameObject(new Ladder{ 2960.0f, 288.0f, 4 });

	GameObjectManager::AddGameObject(new DigPile{ 2864.0f, 224.0f });

	GameObjectManager::AddGameObject(new Destructive{ 2928.0f, 224.0f, 10, 3,
		{
			new Pickupable{ 2968.0f, 232.0f, Pickupable::Type::GreenGem, 0.0f, 360.0f },
			new Pickupable{ 3000.0f, 232.0f, Pickupable::Type::BlueGem, 0.0f, 360.0f },
			new Pickupable{ 3032.0f, 232.0f, Pickupable::Type::GoldGem, 0.0f, 360.0f },
			new Pickupable{ 3064.0f, 232.0f, Pickupable::Type::GreenGem, 0.0f, 360.0f }
		}
		});

	GameObjectManager::AddGameObject(new Destructive{ 3008.0f, 352.0f, 8, 3,
		{
			new Blorb{m_pPLAYER, 3072.0f, 368.0f },
			new Blorb{m_pPLAYER, 3120.0f, 368.0f }
		}
		});



	//	Zone 8
	GameObjectManager::AddGameObject(new Spike{ 2992.0f, 16.0f, 3 });

	GameObjectManager::AddGameObject(new DirtBlockSmall{ 2928.0f, 32.0f });

	GameObjectManager::AddGameObject(new Destructive{ 2768.0f, 32.0f, 4, 3, {} });

	GameObjectManager::AddGameObject(new Beeto{ 3072.0f, 32.0f, false, -32.0f });

	GameObjectManager::AddGameObject(new Boneclang{ m_pPLAYER, 2864.0f, 32.0f });



	//	Zone 9
	GameObjectManager::AddGameObject(new DigClod{ 2752.0f, 80.0f, true });

	GameObjectManager::AddGameObject(new Skull{ 2704.0f, 32.0f });
	GameObjectManager::AddGameObject(new Skull{ 2544.0f, 32.0f });

	GameObjectManager::AddGameObject(new DigPile{ 2592.0f, 32.0f });

	GameObjectManager::AddGameObject(new Pickupable{ 2464.0f, 32.0f, Pickupable::Type::RedGem });
	GameObjectManager::AddGameObject(new Pickupable{ 2432.0f, 32.0f, Pickupable::Type::RedGem });



	//	Zone 10	
	GameObjectManager::AddGameObject(new DigClod{ 3440.0f, 128.0f, true });

	GameObjectManager::AddGameObject(new DirtBlock{ 3360.0f, 96.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3392.0f, 96.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3424.0f, 96.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3456.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3456.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3488.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3488.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3648.0f, 32.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlock{ 3680.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3728.0f, 80.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3744.0f, 32.0f, Pickupable::Type::GoldGem });
	GameObjectManager::AddGameObject(new DirtBlock{ 3776.0f, 96.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 3808.0f, 96.0f, Pickupable::Type::GreyGem });
	GameObjectManager::AddGameObject(new DirtBlock{ 3808.0f, 32.0f, Pickupable::Type::GoldGem });

	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3616.0f, 32.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3632.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3632.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3648.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3664.0f, 80.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3664.0f, 64.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3680.0f, 96.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3696.0f, 112.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3696.0f, 96.0f, Pickupable::Type::GreyGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3712.0f, 112.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3728.0f, 112.0f, Pickupable::Type::GreyGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3744.0f, 112.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3760.0f, 112.0f, Pickupable::Type::GreyGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3712.0f, 96.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3760.0f, 96.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3712.0f, 80.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3760.0f, 80.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3712.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3728.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3744.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3760.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3728.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3728.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3776.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3792.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3776.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3792.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3776.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3792.0f, 32.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3808.0f, 80.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3824.0f, 80.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3808.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3824.0f, 64.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3840.0f, 64.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3840.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3856.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3840.0f, 32.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3856.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 3872.0f, 32.0f });

	GameObjectManager::AddGameObject(new Destructive{ 3776.0f, 144.0f, 3, 3, {new Pickupable{ 3800.0f, 152.0f, Pickupable::Type::MagentaGem, 0.0f, 240.0f }}, true, false, false, false, false });

	GameObjectManager::AddGameObject(new Divedrake{ 3568.0f, 96.0f, 32.0f, 8.0f });

	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 3376.0f, 32.0f });
	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 3792.0f, 80.0f });
	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 3744.0f, 128.0f });

	GameObjectManager::AddGameObject(new Platter{ 3696.0f, 32.0f });

	GameObjectManager::AddGameObject(new Pickupable{ 3544.0f, 150.0f, Pickupable::Type::RedGem });



	//	Zone 11
	pCheckPoint = new CheckPoint{ 4048.0f, 32.0f };
	m_vpCHECK_POINTS.push_back(pCheckPoint);
	GameObjectManager::AddGameObject(pCheckPoint);

	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4224.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4224.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4240.0f, 32.0f, Pickupable::Type::GoldGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4240.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4256.0f, 32.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4256.0f, 48.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4272.0f, 32.0f, Pickupable::Type::GoldGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4272.0f, 48.0f });

	GameObjectManager::AddGameObject(new Bubble{ 4184.0f, -32.0f, 0.0f, 64.0f });

	GameObjectManager::AddGameObject(new Ladder{ 4352.0f, 96.0f, 8 });

	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 4336.0f, 64.0f });



	//	Zone 12
	GameObjectManager::AddGameObject(new MovingPlatform{ 4072.0f, 264.0f, 0.0f, 32.0f, 1.0f, 3.0f });
	GameObjectManager::AddGameObject(new MovingPlatform{ 4168.0f, 296.0f, 128.0f, 0.0f, 0.0f, 6.0f });

	GameObjectManager::AddGameObject(new Pickupable{ 4168.0f, 360.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4200.0f, 360.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4232.0f, 360.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4264.0f, 360.0f, Pickupable::Type::GreenGem });

	GameObjectManager::AddGameObject(new Pickupable{ 4352.0f, 304.0f, Pickupable::Type::GoldGem });

	GameObjectManager::AddGameObject(new Divedrake{ 4120.0f, 296.0f, 8.0f, 8.0f });

	GameObjectManager::AddGameObject(new Destructive{ 4368.0f, 304.0f, 4, 3, {} });

	GameObjectManager::AddGameObject(new Ladder{ 4000.0f, 336.0f, 8 });



	//	Zone 13
	GameObjectManager::AddGameObject(new Bubble{ 4504.0f, 176.0f, 0.0f, 64.0f });
	GameObjectManager::AddGameObject(new Bubble{ 4568.0f, 176.0f, 0.0f, 64.0f });
	GameObjectManager::AddGameObject(new Bubble{ 4776.0f, 176.0f, 0.0f, 96.0f });
	GameObjectManager::AddGameObject(new Bubble{ 4840.0f, 176.0f, 0.0f, 80.0f });

	GameObjectManager::AddGameObject(new DirtBlockSmall{ 4656.0f, 272.0f });

	GameObjectManager::AddGameObject(new DirtBlock{ 4672.0f, 272.0f, Pickupable::Type::GoldGem });

	GameObjectManager::AddGameObject(new Pickupable{ 4536.0f, 312.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4600.0f, 312.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4744.0f, 328.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4744.0f, 328.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4856.0f, 312.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4904.0f, 272.0f, Pickupable::Type::RedGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4936.0f, 272.0f, Pickupable::Type::RedGem });



	//	Zone 14	
	GameObjectManager::AddGameObject(new Ladder{ 4096.0f, 576.0f, 5 });
	GameObjectManager::AddGameObject(new Ladder{ 4272.0f, 592.0f, 3 });

	GameObjectManager::AddGameObject(new Destructive{ 4128.0f, 464.0f, 11, 3,
		{
			new Pickupable{ 4168.0f, 472.0f, Pickupable::Type::RedGem, 0.0f, 360.0f },
			new Pickupable{ 4216.0f, 472.0f, Pickupable::Type::RedGem, 0.0f, 360.0f },
			new Pickupable{ 4280.0f, 472.0f, Pickupable::Type::MagentaGem, 0.0f, 360.0f },
			new Boneclang{ m_pPLAYER, 4272.0f, 472.0f },
		} });

	GameObjectManager::AddGameObject(new Destructive{ 4160.0f, 528.0f, 9, 6,
		{
			new Boneclang{ m_pPLAYER, 4272.0f, 528.0f },
		},
		true, false, false, false, true });

	GameObjectManager::AddGameObject(new Divedrake{ 4072.0f, 520.0f, 0.0f, 40.0f });

	GameObjectManager::AddGameObject(new DigPile{ 4208.0f, 528.0f });



	//	Zone 15
	pCheckPoint = new CheckPoint{ 4288.0f, 720.0f };
	m_vpCHECK_POINTS.push_back(pCheckPoint);
	GameObjectManager::AddGameObject(pCheckPoint);



	//	Zone 16
	GameObjectManager::AddGameObject(new Pickupable{ 4568.0f, 672.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4760.0f, 704.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4824.0f, 704.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 4888.0f, 672.0f, Pickupable::Type::GreenGem });

	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 4688.0f, 688.0f });

	GameObjectManager::AddGameObject(new MovingPlatform{ 5016.0f, 648.0f, 0.0f, 112.0f, 0.5f, 6.0f });



	//	Zone 17
	GameObjectManager::AddGameObject(new DirtBlock{ 5248.0f, 720.0f });
	GameObjectManager::AddGameObject(new DirtBlock{ 5280.0f, 720.0f });

	GameObjectManager::AddGameObject(new Dozedrake{ 5408.0f, 640.0f });



	//	Zone 18
	GameObjectManager::AddGameObject(new Ladder{ 5968.0f, 688.0f, 18 });

	GameObjectManager::AddGameObject(new Boneclang{ m_pPLAYER, 5824.0f, 672.0f });

	GameObjectManager::AddGameObject(new Pickupable{ 5912.0f, 672.0f, Pickupable::Type::GreenGem });



	//	Zone 19
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5904.0f, 960.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5888.0f, 960.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5872.0f, 960.0f, Pickupable::Type::GoldGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5856.0f, 960.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5840.0f, 960.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5824.0f, 960.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5904.0f, 944.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5888.0f, 944.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5872.0f, 944.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5856.0f, 944.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5840.0f, 944.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5824.0f, 944.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5904.0f, 928.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5888.0f, 928.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5872.0f, 928.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5856.0f, 928.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5840.0f, 928.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5824.0f, 928.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5904.0f, 912.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5888.0f, 912.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5872.0f, 912.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5856.0f, 912.0f, Pickupable::Type::GoldGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5840.0f, 912.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5824.0f, 912.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5904.0f, 896.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5888.0f, 896.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5872.0f, 896.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5856.0f, 896.0f });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5840.0f, 896.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new DirtBlockSmall{ 5824.0f, 896.0f });

	GameObjectManager::AddGameObject(new DirtBlock{ 5792.0f, 944.0f });

	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 5888.0f, 848.0f });
	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 5808.0f, 848.0f });
	GameObjectManager::AddGameObject(new Blorb{ m_pPLAYER, 5728.0f, 848.0f });

	GameObjectManager::AddGameObject(new Destructive{ 5616.0f, 848.0f, 5, 3,
		{
			new Pickupable{ 5640.0f, 856.0f, Pickupable::Type::MagentaGem, 0.0f, 360.0f },
		},
		false, false, true, true, true });

	GameObjectManager::AddGameObject(new Pickupable{ 5784.0f, 944.0f, Pickupable::Type::RedGem });

	GameObjectManager::AddGameObject(new DigPile{ 5632.0f, 912.0f });

	GameObjectManager::AddGameObject(new Ladder{ 5728.0f, 992.0f, 10 });



	//	Zone 20
	GameObjectManager::AddGameObject(new Beeto{ 5840.0f, 1120.0f, false, 0.0f, 32.0f });
	GameObjectManager::AddGameObject(new Beeto{ 5904.0f, 1088.0f, true, 0.0f, 32.0f });

	GameObjectManager::AddGameObject(new Divedrake{ 5688.0f, 1136.0f, 0.0f, 48.0f });



	//	Zone 21
	GameObjectManager::AddGameObject(new Pickupable{ 5496.0f, 1136.0f, Pickupable::Type::BlueGem });
	GameObjectManager::AddGameObject(new Pickupable{ 5448.0f, 1104.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 5400.0f, 1104.0f, Pickupable::Type::GreenGem });
	GameObjectManager::AddGameObject(new Pickupable{ 5336.0f, 1136.0f, Pickupable::Type::BlueGem });

	GameObjectManager::AddGameObject(new Bubble{ 5336.0f, 1008.0f, 0.0f, 96.0f });



	//	Zone 22
	pCheckPoint = new CheckPoint{ 6192.0f, 1136.0f };
	m_vpCHECK_POINTS.push_back(pCheckPoint);
	GameObjectManager::AddGameObject(pCheckPoint);

	GameObjectManager::AddGameObject(new Destructive{ 6112.0f, 1072.0f, 3, 2,
		{
			new Platter{ 6128.0f, 1072.0f }
		},
		true, true, true, false, false });



	//	Zone 23
}

void LevelManager::Update(float elapsedSeconds)
{
	switch (m_STATE)
	{
	case LevelManager::State::Dead:
		m_ACCUMULATED_SECONDS += elapsedSeconds;

		if (m_ACCUMULATED_SECONDS >= m_MAX_AFTER_DEATH_SECONDS)
		{
			m_ACCUMULATED_SECONDS = 0.0f;

			m_STATE = State::RespawnTransitionIn;
		}

		GameObjectManager::Manage(elapsedSeconds, Camera::IsShifting());
		Camera::Update(elapsedSeconds);
		m_pHUD->Update(elapsedSeconds);

		//	Find furthest checkpoint
		for (int index{}; index < m_vpCHECK_POINTS.size(); ++index)
		{
			if (m_vpCHECK_POINTS[index]->m_IsActivated && index > m_FURTHEST_CHECK_POINT_INDEX)
			{
				m_FURTHEST_CHECK_POINT_INDEX = index;
			}
		}
		break;

	case LevelManager::State::Playing:
		if (m_pPLAYER->m_Health <= 0) m_STATE = State::Dead;

		GameObjectManager::Manage(elapsedSeconds, Camera::IsShifting());
		Camera::Update(elapsedSeconds);
		m_pHUD->Update(elapsedSeconds);

		//	Find furthest checkpoint
		for (int index{}; index < m_vpCHECK_POINTS.size(); ++index)
		{
			if (m_vpCHECK_POINTS[index]->m_IsActivated && index > m_FURTHEST_CHECK_POINT_INDEX)
			{
				m_FURTHEST_CHECK_POINT_INDEX = index;
			}
		}

		if (InputManager::GetState(SDLK_i))
		{
			m_STATE = State::TransitionToPause;

			SoundManager::PauseEffects();
			SoundManager::PauseStream();
		}

		if (m_pPLAYER->m_Health <= 0)
		{
			SoundManager::StopStream();
			m_STATE = State::Dead;
		}
		break;

	case LevelManager::State::TransitionToPause:

		m_ACCUMULATED_SECONDS += elapsedSeconds;
		if (m_ACCUMULATED_SECONDS >= m_TRANSITION_SECONDS / 4)
		{
			m_ACCUMULATED_SECONDS = 0.0f;

			m_STATE = State::Pause;
		}

		break;

	case LevelManager::State::Pause:
		if (InputManager::GetState(SDLK_i))
		{
			m_STATE = State::TransitionToPlay;
		}
		break;


	case LevelManager::State::TransitionToPlay:

		m_ACCUMULATED_SECONDS += elapsedSeconds;
		if (m_ACCUMULATED_SECONDS >= m_TRANSITION_SECONDS / 4)
		{
			m_ACCUMULATED_SECONDS = 0.0f;

			m_STATE = State::Playing;

			SoundManager::ResumeEffects();
			SoundManager::ResumeStream();
		}

		break;

	case LevelManager::State::RespawnTransitionIn:
		m_ACCUMULATED_SECONDS += elapsedSeconds;

		if (m_ACCUMULATED_SECONDS >= m_TRANSITION_SECONDS)
		{
			m_ACCUMULATED_SECONDS = 0.0f;

			m_STATE = State::BlackScreen;
		}
		break;

	case LevelManager::State::BlackScreen:
		m_ACCUMULATED_SECONDS += elapsedSeconds;

		if (m_ACCUMULATED_SECONDS >= m_BLACK_SCREEN_SECONDS)
		{
			m_ACCUMULATED_SECONDS = 0.0f;

			m_LAST_PLAYER_SCORE = m_pPLAYER->m_Score;

			const Point2f spawnCenter{ m_FURTHEST_CHECK_POINT_INDEX >= 0 ?
				Point2f(
					m_vpCHECK_POINTS[m_FURTHEST_CHECK_POINT_INDEX]->m_RootCenter.x,
					m_vpCHECK_POINTS[m_FURTHEST_CHECK_POINT_INDEX]->m_RootCenter.y - m_pPLAYER->m_LocalCollisionBox.height) :

					m_PLAYER_START_POSITION };

			m_pPLAYER->Reset(spawnCenter.x, spawnCenter.y, m_LAST_PLAYER_SCORE);
			Camera::SetGameObjectToFollow(m_pPLAYER);

			SoundManager::PlayStream("Audio/LevelAudio.mp3", true);

			m_STATE = State::RespawnTransitionOut;
		}
		break;

	case LevelManager::State::RespawnTransitionOut:
		m_ACCUMULATED_SECONDS += elapsedSeconds;

		GameObjectManager::Manage(elapsedSeconds, Camera::IsShifting());
		Camera::Update(elapsedSeconds);
		m_pHUD->Update(elapsedSeconds);

		//	Find furthest checkpoint
		for (int index{}; index < m_vpCHECK_POINTS.size(); ++index)
		{
			if (m_vpCHECK_POINTS[index]->m_IsActivated && index > m_FURTHEST_CHECK_POINT_INDEX)
			{
				m_FURTHEST_CHECK_POINT_INDEX = index;
			}
		}

		if (m_ACCUMULATED_SECONDS >= m_TRANSITION_SECONDS)
		{
			m_ACCUMULATED_SECONDS = 0.0f;

			m_STATE = State::Playing;
		}
		break;
	}
}

void LevelManager::Draw()
{
	GameObjectManager::Draw(0);
	m_pHUD->Draw();

	if (m_STATE == State::Pause)
	{
		Texture movement{ "A == left <> D == right <> SPACE (hold) == Jump (higher)", "HUD/Font.ttf", 14, Color4f(1.0f, 1.0f, 1.0f, 1.0f) };
		Texture ladder{ "W == Up/Grab (ladder) <> S == Down (ladder)", "HUD/Font.ttf", 16, Color4f(1.0f, 1.0f, 1.0f, 1.0f) };
		Texture attacks{ "L == Swing <> S (In-air) == Thrust", "HUD/Font.ttf", 18, Color4f(1.0f, 1.0f, 1.0f, 1.0f) };

		const float offsetX{ m_VIEW_PORT.width / 6 }, offsetY{ m_VIEW_PORT.height / 4 };
		const Rectf rectangle{ m_VIEW_PORT.left + offsetX, m_VIEW_PORT.bottom + offsetY, m_VIEW_PORT.width - 2 * offsetX, m_VIEW_PORT.height - 2 * offsetY };

		utils::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
		utils::FillRect(rectangle);
		utils::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		utils::DrawRect(rectangle);

		movement.Draw(Point2f(rectangle.left + rectangle.width / 2 - movement.GetWidth() / 2, rectangle.bottom + 0.8f * rectangle.height));
		ladder.Draw(Point2f(rectangle.left + rectangle.width / 2 - ladder.GetWidth() / 2, rectangle.bottom + 0.5f * rectangle.height));
		attacks.Draw(Point2f(rectangle.left + rectangle.width / 2 - attacks.GetWidth() / 2, rectangle.bottom + 0.2f * rectangle.height));

		if (!m_PRINTED_TO_CONSOLE)
		{
			std::cout << "Movement: " << std::endl;
			std::cout << "A == Left" << std::endl << "D == Right" << std::endl << "SPACE(hold) == Jump(higher)" << std::endl;
			std::cout << "---" << std::endl << std::endl;

			std::cout << "ladder: " << std::endl;
			std::cout << "" << std::endl << "W == Up/Grab (ladder)" << std::endl << "S == Down (ladder)" << std::endl;
			std::cout << "---" << std::endl << std::endl;

			std::cout << "Attacks: " << std::endl;
			std::cout << "L == Swing" << std::endl << "S (In-air) == Thrust" << std::endl;
			std::cout << "---" << std::endl << std::endl;

			m_PRINTED_TO_CONSOLE = true;
		}
	}
	else if (m_STATE == State::TransitionToPause)
	{
		const float percentage{ m_ACCUMULATED_SECONDS / (m_TRANSITION_SECONDS / 4) }, offsetX{ m_VIEW_PORT.width / 6 }, offsetY{ m_VIEW_PORT.height / 4 };
		const Rectf
			rectangle{ m_VIEW_PORT.left + offsetX, m_VIEW_PORT.bottom + offsetY, m_VIEW_PORT.width - 2 * offsetX, m_VIEW_PORT.height - 2 * offsetY },
			transformedRectangle{ rectangle.left, rectangle.bottom + rectangle.height / 2 - percentage * (rectangle.height / 2), rectangle.width, percentage * rectangle.height };

		utils::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
		utils::FillRect(transformedRectangle);
		utils::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		utils::DrawRect(transformedRectangle);
	}
	else if (m_STATE == State::TransitionToPlay)
	{
		m_PRINTED_TO_CONSOLE = false;

		const float percentage{ 1.0f - m_ACCUMULATED_SECONDS / (m_TRANSITION_SECONDS / 4) }, offsetX{ m_VIEW_PORT.width / 6 }, offsetY{ m_VIEW_PORT.height / 4 };
		const Rectf
			rectangle{ m_VIEW_PORT.left + offsetX, m_VIEW_PORT.bottom + offsetY, m_VIEW_PORT.width - 2 * offsetX, m_VIEW_PORT.height - 2 * offsetY },
			transformedRectangle{ rectangle.left, rectangle.bottom + rectangle.height / 2 - percentage * (rectangle.height / 2), rectangle.width, percentage * rectangle.height };

		utils::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
		utils::FillRect(transformedRectangle);
		utils::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		utils::DrawRect(transformedRectangle);
	}
	else if (m_STATE == State::RespawnTransitionIn)
	{
		const float percentage{ m_ACCUMULATED_SECONDS / (m_TRANSITION_SECONDS - 0.25f) };

		utils::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
		utils::FillRect(m_VIEW_PORT.left, m_VIEW_PORT.bottom, percentage * m_VIEW_PORT.width, m_VIEW_PORT.height);
		utils::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (m_STATE == State::BlackScreen)
	{
		utils::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
		utils::FillRect(m_VIEW_PORT);
		utils::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (m_STATE == State::RespawnTransitionOut)
	{
		const float percentage{ 1.0f - m_ACCUMULATED_SECONDS / (m_TRANSITION_SECONDS - 0.25f) };

		utils::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
		utils::FillRect(m_VIEW_PORT.left, m_VIEW_PORT.bottom, percentage * m_VIEW_PORT.width, m_VIEW_PORT.height);
		utils::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void LevelManager::Close()
{
	delete m_pHUD;
	m_pHUD = nullptr;

	m_pPLAYER = nullptr;

	m_LAST_PLAYER_SCORE = 0;

	m_FURTHEST_CHECK_POINT_INDEX = -1;

	GameObjectManager::DeleteAllGameObjects();

	m_vpCHECK_POINTS.clear();

	SoundManager::StopStream();
}
#pragma endregion PublicMethods