#pragma once
#include <BadEngine/Core/GameObject.h>
#include <BadEngine/Rendering/SpriteRenderer.h>

class Player : BadEngine::GameObject
{
public:
    Player(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem);
};
