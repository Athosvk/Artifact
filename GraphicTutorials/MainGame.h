#pragma once
#include <BadEngine/Game.h>
#include <BadEngine/Rendering/SpriteBatch.h>

#include "Pool.h"

class MainGame : public BadEngine::Game
{
public:
    MainGame();
    virtual ~MainGame() override;
};