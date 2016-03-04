#pragma once
#include <Artifact/Game.h>
#include <Artifact/Rendering/SpriteBatch.h>

class MainGame : public Artifact::Game
{
public:
    MainGame();
    virtual ~MainGame() override = default;
};