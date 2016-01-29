#pragma once
#include <BadEngine/Core/GameObject.h>

class Enemy : BadEngine::GameObject
{
public:
    Enemy(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem);
};

