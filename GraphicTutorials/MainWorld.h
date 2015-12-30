#pragma once
#include <BadEngine/Core/World.h>

#include "Player/Player.h"

class MainWorld : public BadEngine::World
{
private:
    Player m_Player;

public:
    MainWorld(const BadEngine::Window& a_Window);
};

