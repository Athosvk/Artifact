#include <Artifact/StopWatch.h>
#include <iostream>

#include "MainGame.h"
#include "Menu/StartScreen.h"

MainGame::MainGame() : Game(1024, 768, 0, "GameEngine")
{
    loadWorld<StartScreen>();
}
