#pragma once
#include <BadEngine/Core/GameObject.h>
#include <BadEngine/Rendering/SpriteRenderer.h>

class Player
{
private:
    BadEngine::GameObject m_PlayerEntity;

public:
    Player(BadEngine::EntitySystem& a_EntitySystem);
};

