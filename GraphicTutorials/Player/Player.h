#pragma once
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Input/Mouse.h>

#include "PlayerWeapon.h"
#include "CharacterController.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"

class Player
{
private:
    BadEngine::ResourceManager& m_ResourceManager;
    CharacterController m_CharacterController;
    PlayerWeapon m_Weapon;
    const BadEngine::Mouse& m_Mouse;
    Transform m_Transform = Transform(glm::vec2(0, 0));
    SpriteRenderer m_Renderer;

public:
    Player(const BadEngine::Mouse& a_Mouse, BadEngine::ResourceManager& a_ResourceManager);
    ~Player();

    void fixedUpdate();
    void update();
    void draw(BadEngine::SpriteBatch& a_SpriteBatch);
};
