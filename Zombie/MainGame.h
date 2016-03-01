#pragma once
#include <Artifact/Game.h>
#include <Artifact/Rendering/SpriteBatch.h>

#include "Pool.h"

class MainGame : public Artifact::Game
{
public:
    MainGame();
    virtual ~MainGame() override = default;
};