#pragma once
#include <string>
#include <vector>

#include <BadEngine/GLSLProgram.h>
#include <BadEngine/Sprite.h>
#include <BadEngine/GLTexture.h>
#include <BadEngine/Game.h>
#include <BadEngine/Camera2D.h>

class MainGame : public BadEngine::Game
{
private:
    std::vector<BadEngine::Sprite*> m_Sprites = std::vector<BadEngine::Sprite*>();

protected:
    void update() override;
    void draw() override;

public:
    MainGame();
    virtual ~MainGame() override;
};