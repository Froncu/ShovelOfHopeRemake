#include "pch.h"
#include <ctime>
#include "Game.h"

int SDL_main(int argv, char** args)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Game* pGame{ new Game{ Window{ "Shovel Knight - Shovel of Hope (Fratczak, Jakub - 1DAE11)", 1280.0f , 720.0f } } };
    pGame->Run();
    delete pGame;

    return 0;
}