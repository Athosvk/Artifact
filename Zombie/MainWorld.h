#pragma once
#include <Artifact/Core/World.h>

#include "Player/Player.h"

class MainWorld : public Artifact::World
{
public:
    MainWorld(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame);

    void loadGameoverScreen(unsigned a_Score) const;
private:
    void placeBarriers();
};

