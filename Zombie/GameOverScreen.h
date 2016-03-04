#pragma once
#include <Artifact/Core/World.h>

class GameOverScreen : public Artifact::World
{
public:
    GameOverScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame, unsigned a_Score);

    void handleInput();
};

