#pragma once
#include <BadEngine/Game.h>
#include <BadEngine/Rendering/SpriteBatch.h>

#include "Bullet.h"
#include "Player\Player.h"
#include "Player/PlayerWeapon.h"

class MainGame : public BadEngine::Game
{
private:
    BadEngine::SpriteBatch m_SpriteBatch;
    Player m_Player;
    PlayerWeapon m_PlayerWeapon;

protected:
    void update() override;
    void fixedUpdate() override;
    void draw() override;

public:
    MainGame();
    virtual ~MainGame() override;
};