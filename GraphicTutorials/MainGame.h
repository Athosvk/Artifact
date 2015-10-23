#pragma once
#include <vector>

#include <BadEngine/Sprite.h>
#include <BadEngine/Game.h>
#include <BadEngine/SpriteBatch.h>

class MainGame : public BadEngine::Game
{
private:
    std::vector<BadEngine::Sprite*> m_Sprites = std::vector<BadEngine::Sprite*>();
    BadEngine::SpriteBatch m_SpriteBatch;

protected:
    void update() override;
    void draw() override;

public:
    MainGame();
    virtual ~MainGame() override;
};