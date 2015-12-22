#pragma once
#include <BadEngine/IO/ResourceManager.h>

#include "CharacterController.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"

class Player
{
private:
    BadEngine::ResourceManager& m_ResourceManager;
    CharacterController m_CharacterController;
    Transform m_Transform = Transform(glm::vec2(0, 0));
    SpriteRenderer m_Renderer;

public:
    Player(BadEngine::ResourceManager& a_ResourceManager);
    ~Player();

    void fixedUpdate();
    void update();
    void draw(BadEngine::SpriteBatch& a_SpriteBatch);
    Transform& getTransform();
};
