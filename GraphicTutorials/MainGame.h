#pragma once
#include <BadEngine/Game.h>
#include <BadEngine/SpriteBatch.h>

class MainGame : public BadEngine::Game
{
private:
    BadEngine::SpriteBatch m_SpriteBatch;

protected:
    void update() override;
    void draw() override;

public:
    MainGame();
    virtual ~MainGame() override;
};