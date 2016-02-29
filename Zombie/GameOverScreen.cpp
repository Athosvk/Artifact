#include "GameOverScreen.h"

#include <iostream>

GameOverScreen::GameOverScreen(BadEngine::GameTime& a_GameTime, BadEngine::Game* a_CurrentGame)
    : World(a_GameTime, a_CurrentGame)
{
    std::cout << "Game over!";
}
