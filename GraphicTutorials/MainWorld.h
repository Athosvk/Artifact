#pragma once
#include <BadEngine/Core/World.h>

#include "Player/Player.h"

class MainWorld : public BadEngine::World
{
public:
    MainWorld(const BadEngine::Window& a_Window, BadEngine::GameTime& a_GameTime);
};

