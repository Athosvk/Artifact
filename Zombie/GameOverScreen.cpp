#include "GameOverScreen.h"

#include <iostream>

GameOverScreen::GameOverScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame)
    : World(a_GameTime, a_CurrentGame)
{
    std::cout << "Game over!";
}
