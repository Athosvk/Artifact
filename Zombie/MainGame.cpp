#include "MainGame.h"
#include "Menu/StartScreen.h"

MainGame::MainGame() : Game(1024, 768, 0, "Arise!")
{
    SDL_ShowCursor(SDL_DISABLE);
    loadWorld<StartScreen>();
}
