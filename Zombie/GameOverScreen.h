#pragma once
#include <BadEngine/Core/World.h>

class GameOverScreen : public BadEngine::World
{
public:
    GameOverScreen(BadEngine::GameTime& a_GameTime, BadEngine::Game* a_CurrentGame);
};

